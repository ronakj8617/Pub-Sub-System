//
// Created by Ronak on 17/05/25.
//

#define CROW_MAIN
#include <crow.h>
#include "nlohmann/json.hpp"
#include "./../include/TopicManager.h"

using json = nlohmann::json;
mutex mtx2;

void fetchMsg(string subscriberId, TopicManager &manager, mutex &mtx2) {
    while (true)
        {
        lock_guard<mutex> lock(mtx2);
        auto messages = manager.getMessage(subscriberId);

        for (auto &msg: messages)
            cout << msg << endl;

        cout << "-------------------------------" << endl;
        this_thread::sleep_for(chrono::seconds(3));
    }
}

int main() {
    crow::SimpleApp app;
    TopicManager manager;
    thread t1(fetchMsg, "123", ref(manager), ref(mtx2));

    CROW_ROUTE(app, "/ping")
    ([] {
        return crow::response(200, json({{"message", "pong"}, {"status", "ok"}}).dump());
    });

    CROW_ROUTE(app, "/subscribe").methods(crow::HTTPMethod::POST)
    ([&manager](const crow::request &req) {
        try {
            auto body = json::parse(req.body);
            std::string topicId = body["topicId"];
            std::string subscriberId = body["subscriberId"];
            manager.subscribe(topicId, subscriberId);
            return crow::response(200, json({{"message", "Subscribed successfully"}}).dump());
        } catch (const std::exception &e) {
            return crow::response(400, json({{"error", e.what()}}).dump());
        }
    });

    CROW_ROUTE(app, "/publish").methods(crow::HTTPMethod::POST)
    ([&manager](const crow::request &req) {
        try {
            auto body = json::parse(req.body);
            std::string topicId = body["topicId"];
            std::string message = body["message"];
            manager.publish(topicId, message);
            return crow::response(200, json({{"message", "Message published"}}).dump());
        } catch (const std::exception &e) {
            return crow::response(400, json({{"error", e.what()}}).dump());
        }
    });

    CROW_ROUTE(app, "/messages/<string>")
    ([&manager](const std::string &subscriberId) {
        auto messages = manager.getMessage(subscriberId);
        return crow::response(200, json(messages).dump());
    });

    std::cout << "🚀 Pub-Sub Server running at http://localhost:8080\n";
    std::cout << "✅ Endpoints:\n";
    std::cout << "   - GET    /ping\n";
    std::cout << "   - POST   /subscribe  {topicId, subscriberId}\n";
    std::cout << "   - POST   /publish    {topicId, message}\n";
    std::cout << "   - GET    /messages/{subscriberId}\n\n";
    t1.detach();
    app.port(8080).multithreaded().run();

    return 0;
}
