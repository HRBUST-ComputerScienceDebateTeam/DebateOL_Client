#pragma once
#include <bits/stdc++.h>
#include <QString>

using namespace std;


//json转换所用的基类
class JSON_Base{
public:
    std::map<std::string , int> mp1;//对应的是名称 - id
    std::map<int , std::string> mp2;//id - 名称
    std::map<int , std::string> mp3;//id - 类型
};

//通过生成代码产生冗余来解决反射问题
template<typename VAL_TYPE>
std::string gen_jsontoken(int id, std::string type_name , VAL_TYPE val){
    string ret;
    ret += "\"" + QString().setNum(id).toStdString() + "\":";
    ret += "{\"" + type_name +"\":";
    ret +=  QString().setNum(val).toStdString() ;
    ret += "}";
    return ret;
}


std::string gen_jsontoken(int id, std::string type_name , char val);

std::string gen_jsontoken(int id, std::string type_name , string val);

std::string gen_jsontokenWithBase64(int id, std::string type_name , string val);

template<typename VAL_TYPE>
void get_tokenval(const string &s , int l , int r , VAL_TYPE & typeval ){
    //"2":{"str":"hi"}
    int aimpos = 0;
    for(int i = l;i<=r;i++){
        if(s[i] == ':' && s[i+1] != '{'){
            aimpos = i;
            break;
        }
    }
    string_view ss = s;

    string base =string(ss.substr(aimpos+1 , r - aimpos -1 ));
    //qDebug().noquote() << aimpos+1 <<" " <<  r <<" " << base;
    typeval = VAL_TYPE(atoi(string(base).c_str()));
}
void get_tokenval(const string &s , int l , int r , char & typeval );

void get_tokenval(const string &s , int l , int r , string & typeval );
void get_tokenvalWithBase64(const string &s , int l , int r , string & typeval );
int get_typeid(const string & s);

//在下方操作



// 每个结构体 - Echo
class Echo_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Echo_SendInfo &);
    static Echo_SendInfo Deserialization(const std::string&);
public:
    int32_t id;
    string info;
    int32_t sendtime;
};
class Echo_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Echo_RecvInfo &);
    static Echo_RecvInfo Deserialization(const std::string&);
public:
    int32_t id;
    string info;
    string time;
    int32_t sendtime;
};


//video
class Video_Upload_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Video_Upload_SendInfo &);
    static Video_Upload_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t userId;
    int32_t roomId;
    int32_t min;
    int32_t sec;
    int32_t msec;
    string info;
    int32_t sendtime;
};
class Video_Upload_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Video_Upload_RecvInfo &);
    static Video_Upload_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t userId;
    int32_t roomId;
    int32_t min;
    int32_t sec;
    int32_t msec;
    int32_t status;
    int32_t sendtime;
};
class Video_Download_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Video_Download_SendInfo &);
    static Video_Download_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t userId;
    int32_t roomId;
    int32_t min;
    int32_t sec;
    int32_t msec;
    int32_t sendtime;
};
class Video_Download_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Video_Download_RecvInfo &);
    static Video_Download_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t userId;
    int32_t roomId;
    int32_t min;
    int32_t sec;
    int32_t msec;
    int32_t status;
    string info;
    int32_t sendtime;
};
class Video_Clean_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Video_Clean_SendInfo &);
    static Video_Clean_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t userId;
    int32_t roomId;
    int32_t sendtime;
};



//audio
class Audio_Upload_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Audio_Upload_SendInfo &);
    static Audio_Upload_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t userId;
    int32_t roomId;
    int32_t min;
    int32_t sec;
    int32_t msec;
    string info;
    int32_t sendtime;
};
class Audio_Upload_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Audio_Upload_RecvInfo &);
    static Audio_Upload_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t userId;
    int32_t roomId;
    int32_t min;
    int32_t sec;
    int32_t msec;
    int32_t status;
    int32_t sendtime;
};
class Audio_Download_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Audio_Download_SendInfo &);
    static Audio_Download_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t userId;
    int32_t roomId;
    int32_t min;
    int32_t sec;
    int32_t msec;
    int32_t sendtime;
};
class Audio_Download_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Audio_Download_RecvInfo &);
    static Audio_Download_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t userId;
    int32_t roomId;
    int32_t min;
    int32_t sec;
    int32_t msec;
    int32_t status;
    string info;
    int32_t sendtime;
};
class Audio_Clean_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Audio_Clean_SendInfo &);
    static Audio_Clean_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t userId;
    int32_t roomId;
    int32_t sendtime;
};



//user
class User_GetBaseInfo_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_GetBaseInfo_SendInfo &);
    static User_GetBaseInfo_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    string jwt_token;
    int32_t sendtime;
    string Aim_usernum;
    string info;
};
class User_GetBaseInfo_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_GetBaseInfo_RecvInfo &);
    static User_GetBaseInfo_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
    string info;
};
class User_GetSocialInfo_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_GetSocialInfo_SendInfo &);
    static User_GetSocialInfo_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    string jwt_token;
    int32_t sendtime;
    string Aim_usernum;
    string info;
};
class User_GetSocialInfo_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_GetSocialInfo_RecvInfo &);
    static User_GetSocialInfo_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
    string info;
};
class User_GetExInfo_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_GetExInfo_SendInfo &);
    static User_GetExInfo_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    string jwt_token;
    int32_t sendtime;
    string Aim_usernum;
    string info;
};
class User_GetExInfo_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_GetExInfo_RecvInfo &);
    static User_GetExInfo_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
    string info;
};
class User_reg_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_reg_SendInfo &);
    static User_reg_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    string tel;
    string usernum;
    string passwd;
};
class User_reg_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_reg_RecvInfo &);
    static User_reg_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
};
class User_login_Tel_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_login_Tel_SendInfo &);
    static User_login_Tel_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    string tel;
    string passwd;
};
class User_login_num_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_login_num_SendInfo &);
    static User_login_num_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    string usernum;
    string passwd;
};
class User_login_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_login_RecvInfo &);
    static User_login_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
    string jwt_token;
    string refresh_jwt_token;
};
class User_logoff_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_logoff_SendInfo &);
    static User_logoff_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    string jwt_token;
    int32_t sendtime;
};
class User_logoff_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_logoff_RecvInfo &);
    static User_logoff_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
};
class User_refresh_jwt1_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_refresh_jwt1_SendInfo &);
    static User_refresh_jwt1_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    string jwt_token;
    string refresh_jwt_token;
};
class User_refresh_jwt1_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_refresh_jwt1_RecvInfo &);
    static User_refresh_jwt1_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
    string jwt_token;
};
class User_refresh_jwt2_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_refresh_jwt2_SendInfo &);
    static User_refresh_jwt2_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    string jwt_token;
    string refresh_jwt_token;
};
class User_refresh_jwt2_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_refresh_jwt2_RecvInfo &);
    static User_refresh_jwt2_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
    string jwt_token;
    string refresh_jwt_token;
};
class User_friend_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_friend_SendInfo &);
    static User_friend_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    string jwt_token;
    int32_t sendtime;
};
class User_friend_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_friend_RecvInfo &);
    static User_friend_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
    string info;
};
class User_follow_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_follow_SendInfo &);
    static User_follow_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    string jwt_token;
    int32_t sendtime;
};
class User_follow_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_follow_RecvInfo &);
    static User_follow_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
    string info;
};
class User_followed_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_followed_SendInfo &);
    static User_followed_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    string jwt_token;
    int32_t sendtime;
};
class User_followed_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_followed_RecvInfo &);
    static User_followed_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
    string info;
};
class User_ModifyBaseInfo_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_ModifyBaseInfo_SendInfo &);
    static User_ModifyBaseInfo_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    string jwt_token;
    int32_t sendtime;
    string modifyinfo;
};
class User_ModifyBaseInfo_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_ModifyBaseInfo_RecvInfo &);
    static User_ModifyBaseInfo_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
};
class User_ModifySocialInfo_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_ModifySocialInfo_SendInfo &);
    static User_ModifySocialInfo_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    string jwt_token;
    int32_t sendtime;
    string modifyinfo;
};
class User_ModifySocialInfo_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_ModifySocialInfo_RecvInfo &);
    static User_ModifySocialInfo_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
};
class User_ModifyExInfo_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_ModifyExInfo_SendInfo &);
    static User_ModifyExInfo_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    string jwt_token;
    int32_t sendtime;
    string modifyinfo;
};
class User_ModifyExInfo_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const User_ModifyExInfo_RecvInfo &);
    static User_ModifyExInfo_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
};



//room
class Room_GetBaseInfo_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Room_GetBaseInfo_SendInfo &);
    static Room_GetBaseInfo_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    string jwt_token;
    int32_t sendtime;
    string Aim_Roomnum;
    string info;
};
class Room_GetBaseInfo_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Room_GetBaseInfo_RecvInfo &);
    static Room_GetBaseInfo_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
    string info;
};
class Room_GetExInfo_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Room_GetExInfo_SendInfo &);
    static Room_GetExInfo_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    string jwt_token;
    int32_t sendtime;
    string Aim_Roomnum;
    string info;
};
class Room_GetExInfo_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Room_GetExInfo_RecvInfo &);
    static Room_GetExInfo_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
    string info;
};
class Room_GetURrelation_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Room_GetURrelation_SendInfo &);
    static Room_GetURrelation_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    string jwt_token;
    int32_t sendtime;
    string Aim_Roomnum;
    string info;
};
class Room_GetURrelation_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Room_GetURrelation_RecvInfo &);
    static Room_GetURrelation_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
    string info_UR_pos;
    string info_UR_per;
};
class Room_Create_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Room_Create_SendInfo &);
    static Room_Create_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    string jwt_token;
    int32_t sendtime;
    string Roomnum;
    int32_t Islocking;
    string Roomname;
    string passwd;
    int32_t Debate_pos;
};
class Room_Create_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Room_Create_RecvInfo &);
    static Room_Create_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
};
class Room_Joinroom_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Room_Joinroom_SendInfo &);
    static Room_Joinroom_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    string jwt_token;
    int32_t sendtime;
    string roomnum;
    int32_t Debate_pos;
    string passwd;
};
class Room_Joinroom_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Room_Joinroom_RecvInfo &);
    static Room_Joinroom_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
};
class Room_Exitroom_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Room_Exitroom_SendInfo &);
    static Room_Exitroom_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    string jwt_token;
    int32_t sendtime;
    string roomnum;
};
class Room_Exitroom_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Room_Exitroom_RecvInfo &);
    static Room_Exitroom_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
};
class Room_ChangePasswd_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Room_ChangePasswd_SendInfo &);
    static Room_ChangePasswd_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    string jwt_token;
    int32_t sendtime;
    string roomnum;
    string Opasswd;
    string Npasswd;
};
class Room_ChangePasswd_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Room_ChangePasswd_RecvInfo &);
    static Room_ChangePasswd_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
};
class Room_ChangeExtraInfo_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Room_ChangeExtraInfo_SendInfo &);
    static Room_ChangeExtraInfo_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    string jwt_token;
    int32_t sendtime;
    string roomnum;
    string info;
};
class Room_ChangeExtraInfo_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Room_ChangeExtraInfo_RecvInfo &);
    static Room_ChangeExtraInfo_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
};
class Room_ChangeDebatePos_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Room_ChangeDebatePos_SendInfo &);
    static Room_ChangeDebatePos_SendInfo Deserialization(const std::string&);
public:
    int32_t type;
    string jwt_token;
    int32_t sendtime;
    int32_t Debate_pos;
};
class Room_ChangeDebatePos_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Room_ChangeDebatePos_RecvInfo &);
    static Room_ChangeDebatePos_RecvInfo Deserialization(const std::string&);
public:
    int32_t type;
    int32_t sendtime;
    int32_t status;
};

