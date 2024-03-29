﻿#include "./thrift_json_config.h"
#include <QString>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <QDebug>

//通过生成代码产生冗余来解决反射问题
//template<typename VAL_TYPE>
//inline std::string gen_jsontoken(int id, std::string type_name , VAL_TYPE val){
//    string ret;
//    ret += "\"" + QString().setNum(id).toStdString() + "\":";
//    ret += "{\"" + type_name +"\":";
//    ret +=  QString().setNum(val).toStdString() ;
//    ret += "}";
//    return ret;
//}

std::string gen_jsontoken(int id, std::string type_name , char val){
    string ret;
    ret += "\"" + QString().setNum(id).toStdString() + "\":";
    ret += "{\"" + type_name +"\":";
    ret += "\'" + QString(val).toStdString() +"\'";
    ret += "}";
    return ret;
}

std::string gen_jsontoken(int id, std::string type_name , string val){
    string ret;

    ret += "\"" + QString().setNum(id).toStdString() + "\":";
    ret += "{\"" + type_name +"\":";
    //qDebug()<< QString(QByteArray(val.c_str() , val.length()).toBase64()).toStdString();

    ret += "\"" + QString::fromLatin1(QByteArray(val.c_str() , val.length()).toBase64()).toLatin1().toStdString() +"\"";
    ret += "}";
    return ret;
}
//template<typename VAL_TYPE>
//void get_tokenval(const string &s , int l , int r , VAL_TYPE & typeval ){
//    //"2":{"str":"hi"}
//    int aimpos = 0;
//    for(int i = l;i<=r;i++){
//        if(s[i] == ':' && s[i+1] != '{'){
//            aimpos = i;
//            break;
//        }
//    }
//    string_view ss = s;

//    string base =string(ss.substr(aimpos+1 , r - aimpos -1 ));
//    //qDebug().noquote() << aimpos+1 <<" " <<  r <<" " << base;
//    typeval = VAL_TYPE(atoi(string(base).c_str()));
//}

void get_tokenval(const string &s , int l , int r , char & typeval ){
    //"2":{"str":"hi"}
    int aimpos = 0;
    for(int i = l;i<=r;i++){
        if(s[i] == ':' && s[i+1] != '{'){
            aimpos = i;
            break;
        }
    }
    char ch = s[aimpos+2];
    typeval= char(ch);
}

void get_tokenval(const string &s , int l , int r , string & typeval ){
    //"2":{"str":"hi"}
    int aimpos = 0;
    for(int i = l;i<=r;i++){
        if(s[i] == ':' && s[i+1] != '{'){
            aimpos = i;
            break;
        }
    }
    string_view ss = s;
    string base =  string(ss.substr(aimpos+2 , r - aimpos -3 ));
    //qDebug().noquote() << aimpos+1 <<" " <<  r <<" " << base;
    QString tmp = QString::fromLatin1(QByteArray::fromBase64(QByteArray::fromStdString(base)));
    typeval= tmp.toLatin1().toStdString();
}

int get_typeid(const string & s){
    int32_t _ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
            break;
        }
    }
    get_tokenval(s , v[0]+1 , v[1]-1,_ret);
   //转为int 返回
    return _ret;
}
