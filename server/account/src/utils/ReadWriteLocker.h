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
    std::mutex rwLocker; // 读写锁，count增减时线程安全
    std::condition_variable_any condition; // 状态变量，用于等待和唤醒线程
    int readerCount = 0; // 读取用户数
    int writerCount = 0; // 写入用户数

public:
    /**
     * 锁类型定义，用于Holder创建
     */
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

    /**
     * 开始读，在读操作之前调用
     */
    void startRead();

    /**
     * 结束读，在读操作完成后调用
     */
    void endRead();

    /**
     * 开始写，在写操作之前调用
     */
    void startWrite();

    /**
     * 结束写，在写操作完成后调用
     */
    void endWrite();
};



