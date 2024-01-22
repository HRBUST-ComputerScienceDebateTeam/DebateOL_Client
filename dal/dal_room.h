#include <bits/stdc++.h>
#include "dal_config.h"
using namespace std;




//DB中Room base的结构体 - 记录房间本身的基本信息 id 密码 创建时间
typedef class DAL_Room_Base{
    public:
        int     Roomid;                //Roomid
        string  Roomnum;               //Roomnum
        string  Passwd;                //Room密码
        string  RoomCreatetime;        //Room注册时间
        string  Salt;                  //盐 sha256
    public:
        map<string , string> toMap();
        static DAL_Room_Base ToClass(map<string , string> );
}DAL_Room_Base;

//DB中Room Extra的结构体 - 对外展示的部分
typedef class DAL_Room_Extra{
    public:
        int     Roomid;             //Roomid
        string  Roomnum;            //Roomnum
        string  Roomname;           //Room名
        string  Signature;          //Room简介
        int     Islocking;          //是否上锁
        int     Debate_posbitmap;   //位图的方式记录辩位情况
        string  Debate_name;        //辩题名称
    public:
        map<string , string> toMap();
        static DAL_Room_Extra ToClass(map<string , string> );
}DAL_Room_Extra;

//DB中user - Room关系的结构体
typedef class DAL_UR_relation{
    public:
        int     Userid;              //用户id
        int     Roomid;              //Roomid
        int     Debate_pos;          //辩位
        int     Permissions;         //权限等级 0 1
    public:
        map<string , string> toMap();
        static DAL_UR_relation ToClass(map<string , string> );
}DAL_UR_relation;

