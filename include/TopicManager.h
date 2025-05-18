//
// Created by Ronak on 18/05/25.
//

#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <mutex>
#include <queue>

using namespace std;

class TopicManager {

private:
    unordered_map<string, vector<string> > subscribers;  // topicId -> subscriberId
    unordered_map<string, queue<string> > messageQueue; // subscriberId -> Messages
    mutex mtx;

public:
    void publish(string topicId, string message);
    void subscribe(string topicId, string subscriberId);
    vector<string> getMessage(string subscriberId);
};
