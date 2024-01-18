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
