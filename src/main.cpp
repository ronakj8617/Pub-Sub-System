//
// Created by Ronak on 17/05/25.
//

//
// Created by Ronak on 17/05/25.
//

#include <iostream>
#include "crow.h"
#include "nlohmann/json.hpp"
#include "../include/TopicManager.h"

using json = nlohmann::json;

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/ping")([] {
        json res = {{"message", "pong"}, {"status", "ok"}};
        crow::response r{res.dump()};
        r.set_header("Content-Type", "application/json");
        return r;
    });

    // Optional root endpoint
    CROW_ROUTE(app, "/")([] {
        return "Pub-Sub Server is running!";
    });

    app.port(8080).multithreaded().run();

    return 0;
}
