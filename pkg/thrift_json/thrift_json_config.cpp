#include "./thrift_json_config.h"
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
    ret += "\"" + QString(QByteArray(val.c_str() , val.length()).toBase64()).toStdString() +"\"";
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
    QString tmp = QByteArray::fromBase64(QByteArray::fromStdString(base));
    typeval= tmp.toStdString();
}


