#ifndef TOPIC_MANAGER_H
#define TOPIC_MANAGER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <condition_variable>

class TopicManager {
public:

    /**
     * @brief Subscribes a callback to a topic.
     *
     * @param topic The topic name.
     * @param callback A function that handles incoming messages.
     */
    void subscribe(const std::string &topicId, const std::string &subscriberId);

    /**
    * @brief Publishes a message to a specific topic.
     *
     * @param topic The topic name.
     * @param message The message to be sent.
    */
    void publish(const std::string &topicId, const std::string &message);

    std::vector<std::string> getMessage(const std::string &subscriberId);

    void waitForMessages(const std::string &subscriberId, std::vector<std::string> &out);

    int getSubscriberCount(const std::string &topicId);

private:
    std::unordered_map<std::string, std::vector<std::string> > subscribers;
    std::unordered_map<std::string, std::vector<std::string> > messages;

    std::unordered_map<std::string, std::condition_variable> conds;
    std::mutex mtx;
};

#endif // TOPIC_MANAGER_H
