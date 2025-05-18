//
// Created by Ronak on 18/05/25.
//

#include<iostream>
#include "./../include/TopicManager.h"


using namespace std;

void TopicManager::publish(string &topicId, string &message) {
    lock_guard<mutex> lock(mtx);

    for (const auto &subscriber: subscribers[topicId]) {
        messageQueue[subscriber].push(message);
    }
}

void TopicManager::subscribe(string &topicId, string &subscriberId) {
    lock_guard<mutex> lock(mtx);
    subscribers[topicId].push_back(subscriberId);
}

vector<string> TopicManager::getMessage(string &subscriberId) {
    lock_guard<mutex> lock(mtx);

    vector<string> messages;
    auto &queue = messageQueue[subscriberId];
    while (!queue.empty()) {
        messages.push_back(queue.front());
        queue.pop();
    }
    return messages;
}
