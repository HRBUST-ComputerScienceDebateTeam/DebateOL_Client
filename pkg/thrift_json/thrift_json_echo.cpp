#include "./thrift_json_config.h"
#include <QString>
#include <stdlib.h>
#include <QDebug>



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


