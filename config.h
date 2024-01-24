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
const QString AUDIO_POST_PORT = "7100";
const QString PUBLIC_PORT = "7100";

//各个地址
const QString ECHO_POST_PATH = "/echo";
const QString VIDEO_UPLOAD_POST_PATH = "/videoupload";
const QString VIDEO_CLEAN_POST_PATH = "/videoclean";
const QString VIDEO_DOWNLOAD_POST_PATH = "/videodownload";
const QString AUDIO_UPLOAD_POST_PATH = "/audioupload";
const QString AUDIO_CLEAN_POST_PATH = "/audioclean";
const QString AUDIO_DOWNLOAD_POST_PATH = "/audiodownload";

const QString USER_LOGINTEL_PATH = "/usertellogin";
const QString USER_REG_PATH = "/userreg";
const QString USER_LOGINNUM_PATH= "/usernumlogin";
const QString User_GetBaseInfo_PATH= "/usergetbaseinfo";
const QString User_GetSocialInfo_PATH= "/usergetsocialinfo";
const QString User_GetExInfo_PATH= "/usergetexinfo";
const QString User_logoff_PATH= "/userlogoff";
const QString User_refresh_jwt1_PATH= "/userrefreshjwt1";
const QString User_refresh_jwt2_PATH= "/userrefreshjwt2";
const QString User_ModifyBaseInfo_PATH= "/usermodifybaseinfo";
const QString User_ModifySocialInfo_PATH= "/usermodifysocialinfo";
const QString User_ModifyExInfo_PATH= "/usermodifyexinfo";
const QString User_follow_PATH= "/userfollow";
const QString User_followed_PATH= "/userfollowed";
const QString User_friend_PATH= "/userfriend";

const QString Room_ChangeDebatePos_PATH ="/roomchangedebatepos";
const QString Room_ChangeExtraInfo_PATH ="/roomchangeextrainfo";
const QString Room_ChangePasswd_PATH ="/roomchangepasswd";
const QString Room_Exitroom_PATH ="/exitroom";
const QString Room_Joinroom_PATH ="/joinroom";
const QString Room_Create_PATH ="/creatroom";
const QString Room_GetURrelation_PATH ="/roomgeturrelation";
const QString Room_GetExInfo_PATH ="/roomgetexinfo";
const QString Room_GetBaseInfo_PATH ="/roomgetbaseinfo";







//URL
const QString TEST_GET_URL  =   "http://" + PUBLIC_IP + ":" + TSET_GET_PORT;
const QString TEST_POST_URL =   "http://" + PUBLIC_IP + ":" + TEST_POST_PORT;
const QString ECHO_POST_URL =   "http://" + PUBLIC_IP + ":" + ECHO_POST_PORT +  ECHO_POST_PATH;
const QString VIDEO_UPLOAD_POST_URL =   "http://" + PUBLIC_IP + ":" + VIDEO_POST_PORT +  VIDEO_UPLOAD_POST_PATH;
const QString VIDEO_CLEAN_POST_URL =   "http://" + PUBLIC_IP + ":" + VIDEO_POST_PORT +  VIDEO_CLEAN_POST_PATH;
const QString VIDEO_DOWNLOAD_POST_URL =   "http://" + PUBLIC_IP + ":" + VIDEO_POST_PORT +  VIDEO_DOWNLOAD_POST_PATH;

const QString AUDIO_UPLOAD_POST_URL =   "http://" + PUBLIC_IP + ":" + AUDIO_POST_PORT +  AUDIO_UPLOAD_POST_PATH;
const QString AUDIO_CLEAN_POST_URL =   "http://" + PUBLIC_IP + ":" + AUDIO_POST_PORT +  AUDIO_CLEAN_POST_PATH;
const QString AUDIO_DOWNLOAD_POST_URL =   "http://" + PUBLIC_IP + ":" + AUDIO_POST_PORT +  AUDIO_DOWNLOAD_POST_PATH;

const QString USER_LOGINTEL_URL =   "http://" + PUBLIC_IP + ":" + PUBLIC_PORT +  USER_LOGINTEL_PATH;
const QString USER_REG_URL =   "http://" + PUBLIC_IP + ":" + PUBLIC_PORT +  USER_REG_PATH;

const QString USER_LOGINNUM_URL=   "http://" + PUBLIC_IP +":" + PUBLIC_PORT +  USER_LOGINNUM_PATH;
const QString User_GetBaseInfo_URL=   "http://" + PUBLIC_IP +":" + PUBLIC_PORT +  User_GetBaseInfo_PATH;
const QString User_GetSocialInfo_URL=   "http://" + PUBLIC_IP +":" + PUBLIC_PORT +  User_GetSocialInfo_PATH;
const QString User_GetExInfo_URL=   "http://" + PUBLIC_IP +":" + PUBLIC_PORT +  User_GetExInfo_PATH;
const QString User_logoff_URL=   "http://" + PUBLIC_IP +":" + PUBLIC_PORT +  User_logoff_PATH;
const QString User_refresh_jwt1_URL=   "http://" + PUBLIC_IP +":" + PUBLIC_PORT +  User_refresh_jwt1_PATH;
const QString User_refresh_jwt2_URL=   "http://" + PUBLIC_IP +":" + PUBLIC_PORT +  User_refresh_jwt2_PATH;
const QString User_ModifyBaseInfo_URL=   "http://" + PUBLIC_IP +":" + PUBLIC_PORT +  User_ModifyBaseInfo_PATH;
const QString User_ModifySocialInfo_URL=   "http://" + PUBLIC_IP +":" + PUBLIC_PORT +  User_ModifySocialInfo_PATH;
const QString User_ModifyExInfo_URL=   "http://" + PUBLIC_IP +":" + PUBLIC_PORT +  User_ModifyExInfo_PATH;
const QString User_follow_URL=   "http://" + PUBLIC_IP +":" + PUBLIC_PORT +  User_follow_PATH;
const QString User_followed_URL=   "http://" + PUBLIC_IP +":" + PUBLIC_PORT +  User_followed_PATH;
const QString User_friend_URL=   "http://" + PUBLIC_IP +":" + PUBLIC_PORT +  User_friend_PATH;

const QString Room_ChangeDebatePos_URL = "http://" + PUBLIC_IP + ":" + PUBLIC_PORT + Room_ChangeDebatePos_PATH ;
const QString Room_ChangeExtraInfo_URL = "http://" + PUBLIC_IP + ":" + PUBLIC_PORT + Room_ChangeExtraInfo_PATH ;
const QString Room_ChangePasswd_URL = "http://" + PUBLIC_IP + ":" + PUBLIC_PORT + Room_ChangePasswd_PATH ;
const QString Room_Exitroom_URL = "http://" + PUBLIC_IP + ":" + PUBLIC_PORT + Room_Exitroom_PATH ;
const QString Room_Joinroom_URL = "http://" + PUBLIC_IP + ":" + PUBLIC_PORT + Room_Joinroom_PATH ;
const QString Room_Create_URL = "http://" + PUBLIC_IP + ":" + PUBLIC_PORT + Room_Create_PATH ;
const QString Room_GetURrelation_URL = "http://" + PUBLIC_IP + ":" + PUBLIC_PORT + Room_GetURrelation_PATH ;
const QString Room_GetExInfo_URL = "http://" + PUBLIC_IP + ":" + PUBLIC_PORT + Room_GetExInfo_PATH ;
const QString Room_GetBaseInfo_URL = "http://" + PUBLIC_IP + ":" + PUBLIC_PORT + Room_GetBaseInfo_PATH ;


//net 事件注册表大小
const int MAX_EVENTNUM = 3600000 + 10;

#define VIDEO_OK 200
#define VIDEO_NO_PNG 300
#define VIDEO_WRONG_DOWNLOAD_TYPE 400

#define AUDIO_OK 200
#define AUDIO_NO_INFO 300
#define AUDIO_WRONG_DOWNLOAD_TYPE 400

#define USER_ACTION_OK           200
#define USER_WRONG_DOWNLOAD_TYPE 400
#define USER_LOWACLevel          403
#define USER_TIMEOUT_JWT         405
#define USER_ERR_REQINFO         406
#define USER_LOGIN_ERRINFO       408
#define User_Reg_Havethisnum     409
#define User_Reg_Havethistel     410
#define User_Logoff_notonline    415
#define User_JWT_NOTOUTTIME      420
#define User_REJWT_NOTOUTTIME    421
#define User_REJWT_HAVEOUTTIME   422

#define USER_DAL_ERR             502

#define ROOM_ACTION_OK           200
#define ROOM_LOWACLevel          403
#define ROOM_TIMEOUT_JWT         405
#define ROOM_ERR_REQINFO         406
#define ROOM_NoSuchRoomInfo      407
#define ROOM_Create_Havethisnum  409
#define ROOM_JOINROOM_ERRPASSWD  410
#define ROOM_PlayerInotherRoom   411
#define ROOM_Changepos_Havepeo   412
#define ROOM_DAL_ERR             502



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

const int User_GetBaseInfo_SendInfo_TypeId   = 301;
const int User_GetBaseInfo_RecvInfo_TypeId   = 302;
const int User_GetSocialInfo_SendInfo_TypeId = 303;
const int User_GetSocialInfo_RecvInfo_TypeId = 304;
const int User_GetExtraInfo_SendInfo_TypeId  = 305;
const int User_GetExInfo_RecvInfo_TypeId  = 306;

const int User_loginNum_SendInfo_TypeId = 310;
const int User_loginTel_SendInfo_TypeId = 311;
const int User_login_RecvInfo_TypeId    = 312;
const int User_reg_SendInfo_TypeId      = 313;
const int User_reg_RecvInfo_TypeId      = 314;

const int User_logoff_SendInfo_TypeId          = 321;
const int User_logoff_RecvInfo_TypeId          = 322;
const int User_refresh_jwt1_SendInfo_TypeId    = 323;
const int User_refresh_jwt1_RecvInfo_TypeId    = 324;
const int User_refresh_jwt2_SendInfo_TypeId    = 325;
const int User_refresh_jwt2_RecvInfo_TypeId    = 326;
const int User_friend_SendInfo_TypeId          = 331;
const int User_friend_RecvInfo_TypeId          = 332;
const int User_follow_SendInfo_TypeId          = 333;
const int User_follow_RecvInfo_TypeId          = 334;
const int User_followed_SendInfo_TypeId        = 335;
const int User_followed_RecvInfo_TypeId        = 336;
const int User_ModifyBaseInfo_SendInf_TypeId   = 341;
const int User_ModifyBaseInfo_RecvInfo_TypeId  = 342;
const int User_ModifySocialInfo_SendInfo_TypeId= 343;
const int User_ModifySocialInfo_RecvInfo_TypeId= 344;
const int User_ModifyExInfo_SendInfo_TypeId    = 345;
const int User_ModifyExInfo_RecvInfo_TypeId    = 346;


const int Room_GetBaseInfo_RecvInfo_TypeId      = 401;
const int Room_GetBaseInfo_SendInfo_TypeId      = 402;
const int Room_GetExInfo_RecvInfo_TypeId        = 403;
const int Room_GetExInfo_SendInfo_TypeId        = 404;
const int Room_GetURrelation_RecvInfo_TypeId    = 405;
const int Room_GetURrelation_SendInfo_TypeId    = 406;
const int Room_Create_RecvInfo_TypeId           = 407;
const int Room_Create_SendInfo_TypeId           = 408;
const int Room_Joinroom_RecvInfo_TypeId         = 409;
const int Room_Joinroom_SendInfo_TypeId         = 410;
const int Room_Exitroom_RecvInfo_TypeId         = 411;
const int Room_Exitroom_SendInfo_TypeId         = 412;
const int Room_ChangePasswd_RecvInfo_TypeId     = 413;
const int Room_ChangePasswd_SendInfo_TypeId     = 414;
const int Room_ChangeExtraInfo_RecvInfo_TypeId  = 415;
const int Room_ChangeExtraInfo_SendInfo_TypeId  = 416;
const int Room_ChangeDebatePos_RecvInfo_TypeId  = 417;
const int Room_ChangeDebatePos_SendInfo_TypeId  = 418;











//时间
const int time_hour   = 60*60;
const int time_minute = 60   ;
const int time_second = 1    ;
const int jwt_time         = 10*time_minute;
const int refresh_jwt_time =  2*time_hour  ;

//密码加密：
// 1. 登陆申请提交的是 base64 + sha256 又base64 的passwd
// 2. 盐是            base64 + sha256 的存入数据库
// 3. 数据库中的密码 是上述两个相加 之后 sha256 存入数据库
//数据库

const int INT_DEFAULT = -1;
const std::string STR_DEFAULT = "";


#endif
















