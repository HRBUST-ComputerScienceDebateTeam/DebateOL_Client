#pragma once

#ifndef GLOBAL_CONFIG
#define GLOBAL_CONFIG
#include <QString>
//重传次数
const int RETRY_TIMES = 3;

//公网ip
//const QString PUBLIC_IP ="43.138.161.192";
const QString PUBLIC_IP ="110.42.98.27";

//各个服务端口
const QString TSET_GET_PORT  = "7100";
const QString TEST_POST_PORT = "7100";
const QString ECHO_POST_PORT = "7100";
const QString VIDEO_POST_PORT = "7100";

//各个地址
const QString ECHO_POST_PATH = "/echo";
const QString VIDEO_UPLOAD_POST_PATH = "/videoupload";
const QString VIDEO_CLEAN_POST_PATH = "/videoclean";
const QString VIDEO_DOWNLOAD_GET_PATH = "/videodownload/";

//URL
const QString TEST_GET_URL  =   "http://" + PUBLIC_IP + ":" + TSET_GET_PORT;
const QString TEST_POST_URL =   "http://" + PUBLIC_IP + ":" + TEST_POST_PORT;
const QString ECHO_POST_URL =   "http://" + PUBLIC_IP + ":" + ECHO_POST_PORT +  ECHO_POST_PATH;
const QString VIDEO_UPLOAD_POST_URL =   "http://" + PUBLIC_IP + ":" + VIDEO_POST_PORT +  VIDEO_UPLOAD_POST_PATH;
const QString VIDEO_CLEAN_POST_URL =   "http://" + PUBLIC_IP + ":" + VIDEO_POST_PORT +  VIDEO_CLEAN_POST_PATH;
const QString VIDEO_DOWNLOAD_GET_URL =   "http://" + PUBLIC_IP + ":" + VIDEO_POST_PORT +  VIDEO_DOWNLOAD_GET_PATH;

//net 事件注册表大小
const int MAX_EVENTNUM = 3600000 + 10;


//typeid

const int Video_Upload_SendInfo_TypeId = 101;
const int Video_Upload_RecvInfo_TypeId = 102;
const int Video_Download_SendInfo_TypeId = 103;
const int Video_Download_RecvInfo_TypeId = 104;
const int Video_Clean_SendInfo_TypeId = 105;

const int Audio_Upload_SendInfo_TypeId = 201;
const int Audio_Upload_RecvInfo_TypeId = 202;
const int Audio_Download_SendInfo_TypeId = 203;
const int Audio_Download_RecvInfo_TypeId = 204;
const int Audio_Clean_SendInfo_TypeId = 205;
#endif
