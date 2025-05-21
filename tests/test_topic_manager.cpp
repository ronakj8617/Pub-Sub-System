//
// Created by Ronak on 21/05/25.
//

#include <catch2/catch_test_macros.hpp>
#include "./../src/TopicManager.cpp"


TEST_CASE("TopicManager handles subscriptions and messages", "[topic]") {
    TopicManager tm;

    SECTION("Subscribe to topic") {
        tm.subscribe("topic123", "u123");
        REQUIRE(tm.getMessage("u123").empty());
    }

    SECTION("Publish message and fetch") {
        tm.subscribe("topic123", "u124");
        tm.publish("topic123", "Hello!");
        auto messages = tm.getMessage("u124");

        REQUIRE(messages.size() >= 1);
        REQUIRE(messages[0] == "Hello!");
    }

    SECTION("Unsubscribed clients get nothing") {
        tm.publish("topic123", "Update");
        REQUIRE(tm.getMessage("u123").empty());
    }
}
