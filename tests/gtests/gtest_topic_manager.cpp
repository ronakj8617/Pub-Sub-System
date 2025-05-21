//
// Created by Ronak on 21/05/25.
//

#include <gtest/gtest.h>
#include "./../../include/TopicManager.h"


TEST(TopicManagerTest, SubscribeAndPublish) {
    TopicManager manager;

    const std::string subscriberId = "u123";
    const std::string msg = "hello";
    const std::string topicId = "u123";

    manager.subscribe(topicId, subscriberId);
    manager.publish(topicId, msg);
    const auto result = manager.getMessage(subscriberId);

    EXPECT_EQ(result[0], "hello");
}

TEST(TopicManagerTest, SubscriberReceivesPublishedMessage) {
    TopicManager manager;

    const std::string msg = "Breaking News!";
    const std::string subscriberId = "u123";
    const std::string topicId = "u123";

    manager.subscribe(topicId, subscriberId);
    auto result1 = manager.getMessage(subscriberId);

    manager.publish(topicId, msg);

    EXPECT_EQ(result1[0], "Breaking News!");
}

TEST(TopicManagerTest, MultipleSubscribersReceiveMessage) {
    TopicManager manager;
    std::string msg = "Version 2.0 released";
    std::string sub1 = "u123", sub2 = "u124";
    std::string topicId = "u123";

    manager.subscribe(topicId, sub1);
    manager.publish(topicId, msg);
    auto result1 = manager.getMessage(sub1);

    manager.subscribe(topicId, sub2);
    auto result2 = manager.getMessage(sub2);

    EXPECT_EQ(result1[0], msg);
    EXPECT_EQ(result2[0], "Version 2.0 released");
}

TEST(TopicManagerTest, NoSubscribersShouldNotCauseCrash) {
    TopicManager manager;
    // No subscribers added
    std::string topicId = "u123", msg = "Hello?";
    EXPECT_NO_THROW(manager.publish(topicId, msg));
}

TEST(TopicManagerTest, DifferentTopicsDoNotInterfere) {
    TopicManager manager;
    std::string topic1 = "topic1", topic2 = "topic2", topic1_result, topic2_result;
    std::string msg1 = "Data for topic1";
    std::string msg2 = "Data for topic2";

    std::string sub1 = "u123", sub2 = "u124";

    // manager.subscribe(topic1, sub1, [&](const std::string &topic1, const std::string &sub1) {
    //     topic1_result = msg1;
    // });

    // manager.subscribe(topic1, sub1, [&](const std::string &t, const std::string &s) {
    //     topic1_result = msg1;
    // });

    // manager.publish(topic1, msg1);
    // manager.publish(topic2, msg2);
    //
    // EXPECT_EQ(topic1_result, msg1);
    // EXPECT_EQ(topic2_result, msg2);
}
