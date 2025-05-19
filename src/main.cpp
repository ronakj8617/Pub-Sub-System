#define CROW_MAIN
#include <crow.h>
#include "nlohmann/json.hpp"
#include "./../include/TopicManager.h"
#include "./../include/cors.h"
#include "crow/app.h"


using json = nlohmann::json;

int main() {
    crow::App<CORS> app; // CORS middleware added
    TopicManager manager;

    CROW_ROUTE(app, "/ping").methods("GET"_method, "OPTIONS"_method)
    ([](const crow::request& req) {
        if (req.method == "OPTIONS"_method)
            return crow::response(204); // Preflight
        return crow::response(200, json({{"message", "pong"}}).dump());
    });

    CROW_ROUTE(app, "/subscribe").methods("POST"_method, "OPTIONS"_method)
    ([&manager](const crow::request &req) {
        if (req.method == "OPTIONS"_method)
            return crow::response(204); // Preflight

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

    CROW_ROUTE(app, "/publish").methods("POST"_method, "OPTIONS"_method)
    ([&manager](const crow::request &req) {
        if (req.method == "OPTIONS"_method)
            return crow::response(204); // Preflight

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

    CROW_ROUTE(app, "/messages/<string>").methods("GET"_method, "OPTIONS"_method)
    ([&manager](const crow::request& req, const std::string &subscriberId) {
        if (req.method == "OPTIONS"_method)
            return crow::response(204); // Preflight

        auto messages = manager.getMessage(subscriberId);
        return crow::response(200, json(messages).dump());
    });

    std::cout << "✅ Pub-Sub Server running on http://localhost:8080\n";
    app.port(8080).multithreaded().run();
}
