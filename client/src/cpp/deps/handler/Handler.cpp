//
// Created by vell on 19-2-20.
//

#include <chrono>
#include <algorithm>
#include <iostream>
#include "Handler.h"
#include "Message.h"

Handler::Handler() : stop(false), stopWhenEmpty(false) {
    looper = std::thread(
            [this]() {
                for (;;) {

                    if (this->stopWhenEmpty && this->msg_Q.empty()) {
                        break;
                    }

                    if (stop) {
                        msg_Q.clear();
                        break;
                    }

                    Message msg;
                    { // 必须加大括号，unique_lock在这个括号内有效，括号外会被析构
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        if (this->msg_Q.empty()) {
                            this->condition.wait(lock, [this] {
                                return this->stop || this->stopWhenEmpty || !this->msg_Q.empty();
                            });
                            continue;
                        }

                        // 等待到消息执行时
                        auto t = this->msg_Q.back().when - std::chrono::system_clock::now();
                        if (t > std::chrono::milliseconds(0)) {
                            this->condition.wait_for(lock, t, [this] {
//                            return (this->msg_Q.back().when > std::chrono::system_clock::now())
//                                   || this->stop || this->stopWhenEmpty || !this->msg_Q.empty();
                                return true;
                            });
                            continue;
                        }

                        msg = msg_Q.back();
                        msg_Q.pop_back();
                    }
                    this->dispatchMessage(msg);
                }
            });
}

Handler::~Handler() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    looper.join();
    msg_Q.clear();

}

void Handler::handleMessage(Message &msg) {
}

bool Handler::sendMessageAtTime(Message &msg, long uptimeMillis) {
    msg.setWhen(uptimeMillis);

    std::unique_lock<std::mutex> lock(queue_mutex);
    auto i = std::find(msg_Q.begin(), msg_Q.end(), msg);
    msg_Q.erase(i);

    msg_Q.push_back(msg);
    std::sort(msg_Q.begin(), msg_Q.end(), std::greater<Message>());
    condition.notify_one();
    return true;
}

bool Handler::sendMessage(Message &msg) {
    std::unique_lock<std::mutex> lock(queue_mutex);
    auto i = find(msg_Q.begin(), msg_Q.end(), msg);
    if (i != msg_Q.end())
        msg_Q.erase(i);

    msg_Q.push_back(msg);
    std::sort(msg_Q.begin(), msg_Q.end(), std::greater<Message>());
    condition.notify_one();
    return true;
}

bool Handler::sendEmptyMessage(int what) {
    return sendEmptyMessage(what, 0);
}

bool Handler::sendEmptyMessage(int what, long uptimeMillis) {

    if (what < 0)
        return false;

    Message msg(what);
    msg.setWhen(uptimeMillis);

    std::unique_lock<std::mutex> lock(queue_mutex);

    auto i = find(msg_Q.begin(), msg_Q.end(), msg);
    if (i != msg_Q.end()) {
        msg_Q.erase(i);
    }

    msg_Q.push_back(msg);
//	std::sort(msg_Q.begin(), msg_Q.end(),ValComp<Message>());
    // 跟进时间进行降序排列
    std::sort(msg_Q.begin(), msg_Q.end(), std::greater<Message>());

    condition.notify_one();
    return true;
}

bool Handler::post(Message::Function f) {
    return postAtTime(f, 0);
}

bool Handler::postAtTime(Message::Function f, long uptimeMillis) {

    if (f == nullptr) {
        return false;
    }

    std::unique_lock<std::mutex> lock(queue_mutex);
    Message msg;
    msg.setWhen(uptimeMillis);
    msg.setFunction(f);
    msg_Q.push_back(msg);
    std::sort(msg_Q.begin(), msg_Q.end(), std::greater<Message>());
    condition.notify_one();
    return true;
}

void Handler::removeMessages(int what) {
    if (what < 0)
        return;

    std::unique_lock<std::mutex> lock(queue_mutex);

    auto i = find(msg_Q.begin(), msg_Q.end(), what);
    if (i != msg_Q.end()) {
        msg_Q.erase(i);
    }

    condition.notify_one();
}

void Handler::removeCallbackAndMessages() {
    std::unique_lock<std::mutex> lock(queue_mutex);
    msg_Q.clear();
}

void Handler::stopSafty(bool stopSafty) {
    std::unique_lock<std::mutex> lock(queue_mutex);
    if (stopSafty) {
        stopWhenEmpty = true;
    } else {
        stop = true;
    }
}


bool Handler::isQuiting() {
    std::unique_lock<std::mutex> lock(queue_mutex);
    return stop || stopWhenEmpty;
}

void Handler::dispatchMessage(Message &msg) {
    if (msg.task != nullptr) {
        msg.task();
    } else {
        if (msg.m_what < 0)
            return;
        handleMessage(msg);
    }
}
