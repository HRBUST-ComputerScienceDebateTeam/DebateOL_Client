#include "./thrift_json_config.h"
#include <QString>
#include <stdlib.h>
#include <QDebug>

//通过生成代码产生冗余来解决反射问题
template<typename VAL_TYPE>
inline std::string gen_jsontoken(int id, std::string type_name , VAL_TYPE val){
    string ret;
    ret += "\"" + QString().setNum(id).toStdString() + "\":";
    ret += "{\"" + type_name +"\":";
    ret +=  QString().setNum(val).toStdString() ;
    ret += "}";
    return ret;
}

inline std::string gen_jsontoken(int id, std::string type_name , char val){
    string ret;
    ret += "\"" + QString().setNum(id).toStdString() + "\":";
    ret += "{\"" + type_name +"\":";
    ret += "\'" + QString(val).toStdString() +"\'";
    ret += "}";
    return ret;
}

inline std::string gen_jsontoken(int id, std::string type_name , string val){
    string ret;
    ret += "\"" + QString().setNum(id).toStdString() + "\":";
    ret += "{\"" + type_name +"\":";
    ret += "\"" + val +"\"";
    ret += "}";
    return ret;
}

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

    string base =string(ss.substr(aimpos+2 , r - aimpos -3 ));
    qDebug().noquote() << aimpos+1 <<" " <<  r <<" " << base;
    typeval= base;
}


JSON_Base Make_Json_Echo_SendInfo(){
    JSON_Base ret;
    ret.mp1["id"] = 1;ret.mp2[1] = "id";ret.mp3[1] = "i32";
    ret.mp1["info"] = 2;ret.mp2[2] = "info";ret.mp3[2] = "string";
    return ret;
};
JSON_Base Echo_SendInfo::json_base_ = Make_Json_Echo_SendInfo();


JSON_Base Make_Json_Echo_RecvInfo(){
    JSON_Base ret;
    ret.mp1["id"] = 1;ret.mp2[1] = "id";ret.mp3[1] = "i32";
    ret.mp1["info"] = 2;ret.mp2[2] = "info";ret.mp3[2] = "string";
    ret.mp1["time"] = 3;ret.mp2[3] = "time";ret.mp3[3] = "string";
    return ret;
};
JSON_Base Echo_RecvInfo::json_base_ = Make_Json_Echo_RecvInfo();




//序列化 {"1":{"i32":1},"2":{"str":"hihao"}};
std::string Echo_SendInfo::Serialization(const Echo_SendInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.id);
    ret += ",";	ret += gen_jsontoken(2,"string",pkg.info);
    ret += "}";
    return ret;
}
std::string Echo_RecvInfo::Serialization(const Echo_RecvInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.id);
    ret += ",";	ret += gen_jsontoken(2,"string",pkg.info);
    ret += ",";	ret += gen_jsontoken(3,"string",pkg.time);
    ret += "}";
    return ret;
}



//{"1":{"i32":1},"2":{"str":"hi"}}
//"1":{"i32":1}
// 反序列化
Echo_SendInfo Echo_SendInfo::Deserialization(const std::string& s){
    Echo_SendInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.id);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.info);
    return ret;
}
Echo_RecvInfo Echo_RecvInfo::Deserialization(const std::string& s){
    Echo_RecvInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.id);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.info);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.time);
    return ret;
}


