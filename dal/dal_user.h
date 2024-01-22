#include <bits/stdc++.h>
#include "dal_config.h"
using namespace std;





//DB中用户base的结构体
typedef class DAL_User_Base{
public:
    int     Userid;             //用户id
    string  Usernum;            //用户注册号码
    string  Passwd;             //用户密码
    string  Tel;                //用户电话号
    string  UserRegtime;        //用户注册时间
    string  UserLasttime;       //用户最近登陆时间 - 0 现在在线
    string  Salt;               //盐 sha256
public:
    map<string , string> toMap();
    static DAL_User_Base ToClass(map<string , string> );
}DAL_User_Base;

//DB中用户social的结构体
typedef class DAL_User_Social{
public:
    int     Userid;             //用户id
    string  Username;           //用户名 - 唯一
    string  Headshot;           //用户头像
    int     Sex;                //用户性别
    string  Signature;          //用户个性签名
    string  Contact;            //用户联系方式
public:
    map<string , string> toMap();
    static DAL_User_Social ToClass(map<string , string> );
}DAL_User_Social;


//DB中用户extra的结构体
typedef class DAL_User_Extra{
public:
    int     Userid;             // 用户id
    int     IntentionToArgue;   // 意向辩位
    string  MatcheNum;          // 比赛次数
    string  BestPlayerNum;      // 最佳辩手次数
    int     VectoryNum;         // 胜利次数
    int     OnePosNum;          // 各个辩位场次
    int     TwoPosNum;
    int     ThreePosNum;
    int     FourPosNum;
public:
    map<string , string> toMap();
    static DAL_User_Extra ToClass(map<string , string> );
}DAL_User_Extra;

//DB中用户关系的结构体
typedef class DAL_UU_relation{
public:
    int     UseridA;             //用户idA
    int     UseridB;             //用户idB
    int     UULevel;             //用户AB 之间的关系
public:
    map<string , string> toMap();
    static DAL_UU_relation ToClass(map<string , string> );
}DAL_UU_relation;


//关系说明
//两人公用一个关系连接 a<b
//无记录 - 陌生人
//1 1 1 1
//8：a关注b
//4：b关注a
//2：a拉黑b
//1: b拉黑a
