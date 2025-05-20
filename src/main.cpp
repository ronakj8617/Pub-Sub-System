#define CROW_MAIN
#include "crow.h"
#include "nlohmann/json.hpp"
#include "cors.h"
#include "TopicManager.h"

using json = nlohmann::json;

int main() {
    crow::App<CORS> app;
    TopicManager manager;

    CROW_ROUTE(app, "/ping").methods("GET"_method)([] {
        return crow::response(200, json({{"message", "pong"}}).dump());
    });

    CROW_ROUTE(app, "/subscribe").methods("POST"_method)
    ([&manager](const crow::request &req) {
        auto body = json::parse(req.body);
        std::string topicId = body["topicId"];
        std::string subscriberId = body["subscriberId"];
        manager.subscribe(topicId, subscriberId);
        return crow::response(200, "Subscribed");
    });

    CROW_ROUTE(app, "/publish").methods("POST"_method)
    ([&manager](const crow::request &req) {
        auto body = json::parse(req.body);
        std::string topicId = body["topicId"];
        std::string message = body["message"];
        manager.publish(topicId, message);
        return crow::response(200, "Published");
    });

    CROW_ROUTE(app, "/messages/<string>").methods("GET"_method)
    ([&manager](const std::string &subscriberId) {
        auto messages = manager.getMessage(subscriberId);
        return crow::response(200, json(messages).dump());
    });

    std::cout << "✅ Server running on http://localhost:8080\n";
    app.port(8080).multithreaded().run();
}
