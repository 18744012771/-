﻿#include "msgcenter.h"

#include "util/global.h"
#include "util/common.h"
#include "usermsgprocessor.h"
#include "publisher/agvpositionpublisher.h"


MsgCenter::MsgCenter(QObject *parent) : QObject(parent),
    positionPublisher(NULL),
    statusPublisher(NULL),
    taskPublisher(NULL)
{

}

void MsgCenter::init()
{
//    //启动8个线程，同时处理来自client的消息。
//    for(int i=0;i<8;++i){
//        UserMsgProcessor *workerThread = new UserMsgProcessor(this);
//        workerThread->start();
//    }
    //启动订阅 小车状态信息的线程
    if(statusPublisher){
        delete statusPublisher;
        statusPublisher=NULL;
    }
    statusPublisher = new AgvStatusPublisher(this);
    statusPublisher->start();

    //启动订阅 小车位置信息的线程
    if(positionPublisher){
        delete positionPublisher;
        positionPublisher=NULL;
    }
    positionPublisher = new AgvPositionPublisher(this);
    positionPublisher->start();

    if(taskPublisher){
        delete taskPublisher;
        taskPublisher = NULL;
    }
    taskPublisher = new AgvTaskPublisher(this);
    taskPublisher->start();
}

MsgCenter::~MsgCenter()
{
    if(positionPublisher)delete positionPublisher;
    if(statusPublisher)delete statusPublisher;
    if(taskPublisher)delete taskPublisher;
}

