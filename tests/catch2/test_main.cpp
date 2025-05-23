//
// Created by Ronak on 21/05/25.
//

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "../../include/TopicManager.h"

TEST_CASE("TopicManager addSubscriber works", "[topic]") {
    TopicManager tm;
    tm.subscribe("topic123", "u123");
    REQUIRE(tm.getSubscriberCount("topic123") >= 1);
}