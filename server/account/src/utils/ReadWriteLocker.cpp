//
// Created by vellhe on 2020/2/28.
//

#include "ReadWriteLocker.h"

void ReadWriteLocker::startRead() {
    std::unique_lock<std::mutex> lock(rwLocker);
    while (writerCount > 0) {
        // 有人在写入，等待写入完成
        condition.wait(rwLocker);
    }
    readerCount++;
}

void ReadWriteLocker::endRead() {
    std::unique_lock<std::mutex> lock(rwLocker);
    readerCount--;
    condition.notify_all();
}

void ReadWriteLocker::startWrite() {
    std::unique_lock<std::mutex> lock(rwLocker);
    while (readerCount > 0 || writerCount > 0) {
        // 有人在读写，等待读写完成
        condition.wait(rwLocker);
    }
    writerCount++;
}

void ReadWriteLocker::endWrite() {
    std::unique_lock<std::mutex> lock(rwLocker);
    writerCount--;
    condition.notify_all();
}

ReadWriteLocker::Holder::Holder(ReadWriteLocker::LockerType lockerType, ReadWriteLocker &locker) : lockerType(
        lockerType),
                                                                                                   locker(locker) {
    if (lockerType == LockerType::READ) {
        locker.startRead();
    } else if (lockerType == LockerType::WRITE) {
        locker.startWrite();
    }
}

ReadWriteLocker::Holder::~Holder() {
    if (lockerType == LockerType::READ) {
        locker.endRead();
    } else if (lockerType == LockerType::WRITE) {
        locker.endWrite();
    }
}
