#include "./thrift_json_config.h"
#include <QString>
#include <stdlib.h>

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



// 反序列化
static Echo_SendInfo Deserialization(const std::string&){
    Echo_SendInfo ret;
    //遍历每一个元素
}


