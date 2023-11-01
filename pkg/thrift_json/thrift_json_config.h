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




// 每个结构体 - Echo
class Echo_SendInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Echo_SendInfo &);
    static Echo_SendInfo Deserialization(const std::string&);
public:
    uint32_t id;
    string info;
};


class Echo_RecvInfo{
public:
    static JSON_Base json_base_;
public:
    static std::string Serialization(const Echo_RecvInfo &);
    static Echo_RecvInfo Deserialization(const std::string&);
public:
    uint32_t id;
    string info;
    string time;
};


