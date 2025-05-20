//
// Created by Ronak on 18/05/25.
//
#include "./../include/TopicManager.h"

void TopicManager::subscribe(const std::string& topicId, const std::string& subscriberId) {
    std::lock_guard<std::mutex> lock(mtx);
    subscribers[topicId].push_back(subscriberId);
}

void TopicManager::publish(const std::string& topicId, const std::string& message) {
    std::lock_guard<std::mutex> lock(mtx);
    for (const auto& sub : subscribers[topicId]) {
        messages[sub].push_back(message);
        conds[sub].notify_all();
    }
}

std::vector<std::string> TopicManager::getMessage(const std::string& subscriberId) {
    std::lock_guard<std::mutex> lock(mtx);
    auto msgs = messages[subscriberId];
    messages[subscriberId].clear();
    return msgs;
}

void TopicManager::waitForMessages(const std::string& subscriberId, std::vector<std::string>& out) {
    std::unique_lock<std::mutex> lock(mtx);
    conds[subscriberId].wait(lock, [&] {
        return !messages[subscriberId].empty();
    });
    out = std::move(messages[subscriberId]);
    messages[subscriberId].clear();
}
