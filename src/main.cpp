#define CROW_MAIN
#include "crow.h"
#include "nlohmann/json.hpp"
#include "cors.h"
#include "TopicManager.h"

using json = nlohmann::json;

int main() {
    crow::App<CORS> app;
    TopicManager manager;

    auto allow_cors = []() {
        crow::response res;
        res.code = 204;
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        return res;
    };

    CROW_ROUTE(app, "/ping")
    .methods("GET"_method, "OPTIONS"_method)
    ([&](const crow::request& req){
        if (req.method == "OPTIONS"_method) return allow_cors();
        return crow::response(200, json({{"message","pong"}}).dump());
    });

    CROW_ROUTE(app, "/subscribe")
    .methods("POST"_method, "OPTIONS"_method)
    ([&](const crow::request& req){
        if (req.method == "OPTIONS"_method) return allow_cors();
        auto body = json::parse(req.body);
        manager.subscribe(body["topicId"], body["subscriberId"]);
        auto res = crow::response(200, json({{"message","Subscribed"}}).dump());
        res.add_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    CROW_ROUTE(app, "/publish")
    .methods("POST"_method, "OPTIONS"_method)
    ([&](const crow::request& req){
        if (req.method == "OPTIONS"_method) return allow_cors();
        auto body = json::parse(req.body);
        manager.publish(body["topicId"], body["message"]);
        auto res = crow::response(200, json({{"message","Published"}}).dump());
        res.add_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    CROW_ROUTE(app, "/messages/<string>")
    .methods("GET"_method, "OPTIONS"_method)
    ([&](const crow::request& req, const std::string& subId){
        if (req.method == "OPTIONS"_method) return allow_cors();
        auto msgs = manager.getMessage(subId);
        auto res = crow::response(200, json(msgs).dump());
        res.add_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    // fallback CORS handler for any OPTIONS
    CROW_ROUTE(app, "/messages")
    .methods("GET"_method, "OPTIONS"_method)
    ([&manager](const crow::request& req) {
        // Extract subscriberId from query params, e.g. ?subId=xyz
        auto urlParams = crow::query_string(req.url);
        std::string subId = urlParams.get("subId") ? urlParams.get("subId") : "";
        auto msgs = manager.getMessage(subId);
        return crow::response(200, json(msgs).dump());
    });

    std::cout << "✅ Server running on http://localhost:8080\n";
    app.port(8080).multithreaded().run();
}
