//
// Created by Ronak on 17/05/25.
//

#define CROW_MAIN
#include "crow.h"
#include "nlohmann/json.hpp"
#include "./../include/TopicManager.h"

using json = nlohmann::json;

int main() {
    crow::SimpleApp app;
    TopicManager topicManager;

    // Health check
    CROW_ROUTE(app, "/ping")([] {
        json res = {{"message", "pong"}, {"status", "ok"}};
        return crow::response{res.dump()};
    });

    // Publish message: POST /publish
    // JSON payload: { "topicId": "topic1", "message": "Hello" }
    CROW_ROUTE(app, "/publish").methods(crow::HTTPMethod::Post)([&topicManager](const crow::request& req) {
        auto body = json::parse(req.body);
        if (!body.contains("topicId") || !body.contains("message")) {
            return crow::response(400, "Missing topicId or message");
        }
        std::string topicId = body["topicId"];
        std::string message = body["message"];

        topicManager.publish(topicId, message);
        return crow::response(200, "Message published");
    });

    // Subscribe: POST /subscribe
    // JSON payload: { "topicId": "topic1", "subscriberId": "user123" }
    CROW_ROUTE(app, "/subscribe").methods(crow::HTTPMethod::Post)([&topicManager](const crow::request& req) {
        auto body = json::parse(req.body);
        if (!body.contains("topicId") || !body.contains("subscriberId")) {
            return crow::response(400, "Missing topicId or subscriberId");
        }
        std::string topicId = body["topicId"];
        std::string subscriberId = body["subscriberId"];

        topicManager.subscribe(topicId, subscriberId);
        return crow::response(200, "Subscribed successfully");
    });

    // Get messages for subscriber: GET /messages/<subscriberId>
    CROW_ROUTE(app, "/messages/<string>")([&topicManager](const std::string& subscriberId) {
        auto messages = topicManager.getMessage(subscriberId);
        json res = json::array();
        for (const auto& msg : messages) {
            res.push_back(msg);
        }
        return crow::response{res.dump()};
    });

    app.port(8080).multithreaded().run();

    return 0;
}
