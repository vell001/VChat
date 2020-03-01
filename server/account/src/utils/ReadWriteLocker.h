//
// Created by vellhe on 2020/2/28.
//

#pragma once

#include<condition_variable>
#include<thread>

/**
 * 读写锁，允许并行读，但只能串行写，写时不能读，可使用内部Holder类对象进行自动加解锁，如: ReadWriteLocker::Holder lock(ReadWriteLocker::WRITE, locker);
 */
class ReadWriteLocker {
private:
    std::mutex rwLocker; // 读写锁
    std::condition_variable_any condition; // 状态变量，用于等待和唤醒线程
    int readerCount = 0;
    int writerCount = 0;

public:
    enum LockerType {
        READ,
        WRITE
    };

    /**
     * Holder对象的利用构造和析构函数进行自动加锁和解锁
     */
    class Holder {
        LockerType lockerType;
        ReadWriteLocker &locker;
    public:
        Holder(LockerType lockerType, ReadWriteLocker &locker);
        virtual ~Holder();
    };

    void startRead();

    void endRead();

    void startWrite();

    void endWrite();
};



