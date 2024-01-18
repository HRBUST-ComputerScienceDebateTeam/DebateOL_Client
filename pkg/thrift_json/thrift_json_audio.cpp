#include <vector>
#include "./thrift_json_config.h"
#include <QString>
#include <stdlib.h>
#include <QDebug>


JSON_Base Make_Json_Audio_Upload_SendInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["userId"] = 2;ret.mp2[2] = "userId";ret.mp3[2] = "i32";
    ret.mp1["roomId"] = 3;ret.mp2[3] = "roomId";ret.mp3[3] = "i32";
    ret.mp1["min"] = 4;ret.mp2[4] = "min";ret.mp3[4] = "i32";
    ret.mp1["sec"] = 5;ret.mp2[5] = "sec";ret.mp3[5] = "i32";
    ret.mp1["msec"] = 6;ret.mp2[6] = "msec";ret.mp3[6] = "i32";
    ret.mp1["info"] = 7;ret.mp2[7] = "info";ret.mp3[7] = "string";
    ret.mp1["sendtime"] = 8;ret.mp2[8] = "sendtime";ret.mp3[8] = "i32";
    return ret;
};
JSON_Base Audio_Upload_SendInfo::json_base_ = Make_Json_Audio_Upload_SendInfo();
std::string Audio_Upload_SendInfo::Serialization(const Audio_Upload_SendInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.userId);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.roomId);
    ret += ",";	ret += gen_jsontoken(4,"i32",pkg.min);
    ret += ",";	ret += gen_jsontoken(5,"i32",pkg.sec);
    ret += ",";	ret += gen_jsontoken(6,"i32",pkg.msec);
    ret += ",";	ret += gen_jsontoken(7,"string",pkg.info);
    ret += ",";	ret += gen_jsontoken(8,"i32",pkg.sendtime);
    ret += "}";
    return ret;
}
Audio_Upload_SendInfo Audio_Upload_SendInfo::Deserialization(const std::string& s){
    Audio_Upload_SendInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.userId);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.roomId);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.min);
    get_tokenval(s , v[4]+1 , v[5]-1 ,ret.sec);
    get_tokenval(s , v[5]+1 , v[6]-1 ,ret.msec);
    get_tokenval(s , v[6]+1 , v[7]-1 ,ret.info);
    get_tokenval(s , v[7]+1 , v[8]-1 ,ret.sendtime);
    return ret;
}

JSON_Base Make_Json_Audio_Upload_RecvInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["userId"] = 2;ret.mp2[2] = "userId";ret.mp3[2] = "i32";
    ret.mp1["roomId"] = 3;ret.mp2[3] = "roomId";ret.mp3[3] = "i32";
    ret.mp1["min"] = 4;ret.mp2[4] = "min";ret.mp3[4] = "i32";
    ret.mp1["sec"] = 5;ret.mp2[5] = "sec";ret.mp3[5] = "i32";
    ret.mp1["msec"] = 6;ret.mp2[6] = "msec";ret.mp3[6] = "i32";
    ret.mp1["status"] = 7;ret.mp2[7] = "status";ret.mp3[7] = "i32";
    ret.mp1["sendtime"] = 8;ret.mp2[8] = "sendtime";ret.mp3[8] = "i32";
    return ret;
};
JSON_Base Audio_Upload_RecvInfo::json_base_ = Make_Json_Audio_Upload_RecvInfo();
std::string Audio_Upload_RecvInfo::Serialization(const Audio_Upload_RecvInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.userId);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.roomId);
    ret += ",";	ret += gen_jsontoken(4,"i32",pkg.min);
    ret += ",";	ret += gen_jsontoken(5,"i32",pkg.sec);
    ret += ",";	ret += gen_jsontoken(6,"i32",pkg.msec);
    ret += ",";	ret += gen_jsontoken(7,"i32",pkg.status);
    ret += ",";	ret += gen_jsontoken(8,"i32",pkg.sendtime);
    ret += "}";
    return ret;
}
Audio_Upload_RecvInfo Audio_Upload_RecvInfo::Deserialization(const std::string& s){
    Audio_Upload_RecvInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.userId);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.roomId);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.min);
    get_tokenval(s , v[4]+1 , v[5]-1 ,ret.sec);
    get_tokenval(s , v[5]+1 , v[6]-1 ,ret.msec);
    get_tokenval(s , v[6]+1 , v[7]-1 ,ret.status);
    get_tokenval(s , v[7]+1 , v[8]-1 ,ret.sendtime);
    return ret;
}

JSON_Base Make_Json_Audio_Download_SendInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["userId"] = 2;ret.mp2[2] = "userId";ret.mp3[2] = "i32";
    ret.mp1["roomId"] = 3;ret.mp2[3] = "roomId";ret.mp3[3] = "i32";
    ret.mp1["min"] = 4;ret.mp2[4] = "min";ret.mp3[4] = "i32";
    ret.mp1["sec"] = 5;ret.mp2[5] = "sec";ret.mp3[5] = "i32";
    ret.mp1["msec"] = 6;ret.mp2[6] = "msec";ret.mp3[6] = "i32";
    ret.mp1["sendtime"] = 7;ret.mp2[7] = "sendtime";ret.mp3[7] = "i32";
    return ret;
};
JSON_Base Audio_Download_SendInfo::json_base_ = Make_Json_Audio_Download_SendInfo();
std::string Audio_Download_SendInfo::Serialization(const Audio_Download_SendInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.userId);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.roomId);
    ret += ",";	ret += gen_jsontoken(4,"i32",pkg.min);
    ret += ",";	ret += gen_jsontoken(5,"i32",pkg.sec);
    ret += ",";	ret += gen_jsontoken(6,"i32",pkg.msec);
    ret += ",";	ret += gen_jsontoken(7,"i32",pkg.sendtime);
    ret += "}";
    return ret;
}
Audio_Download_SendInfo Audio_Download_SendInfo::Deserialization(const std::string& s){
    Audio_Download_SendInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.userId);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.roomId);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.min);
    get_tokenval(s , v[4]+1 , v[5]-1 ,ret.sec);
    get_tokenval(s , v[5]+1 , v[6]-1 ,ret.msec);
    get_tokenval(s , v[6]+1 , v[7]-1 ,ret.sendtime);
    return ret;
}

JSON_Base Make_Json_Audio_Download_RecvInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["userId"] = 2;ret.mp2[2] = "userId";ret.mp3[2] = "i32";
    ret.mp1["roomId"] = 3;ret.mp2[3] = "roomId";ret.mp3[3] = "i32";
    ret.mp1["min"] = 4;ret.mp2[4] = "min";ret.mp3[4] = "i32";
    ret.mp1["sec"] = 5;ret.mp2[5] = "sec";ret.mp3[5] = "i32";
    ret.mp1["msec"] = 6;ret.mp2[6] = "msec";ret.mp3[6] = "i32";
    ret.mp1["status"] = 7;ret.mp2[7] = "status";ret.mp3[7] = "i32";
    ret.mp1["info"] = 8;ret.mp2[8] = "info";ret.mp3[8] = "string";
    ret.mp1["sendtime"] = 9;ret.mp2[9] = "sendtime";ret.mp3[9] = "i32";
    return ret;
};
JSON_Base Audio_Download_RecvInfo::json_base_ = Make_Json_Audio_Download_RecvInfo();
std::string Audio_Download_RecvInfo::Serialization(const Audio_Download_RecvInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.userId);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.roomId);
    ret += ",";	ret += gen_jsontoken(4,"i32",pkg.min);
    ret += ",";	ret += gen_jsontoken(5,"i32",pkg.sec);
    ret += ",";	ret += gen_jsontoken(6,"i32",pkg.msec);
    ret += ",";	ret += gen_jsontoken(7,"i32",pkg.status);
    ret += ",";	ret += gen_jsontoken(8,"string",pkg.info);
    ret += ",";	ret += gen_jsontoken(9,"i32",pkg.sendtime);
    ret += "}";
    return ret;
}
Audio_Download_RecvInfo Audio_Download_RecvInfo::Deserialization(const std::string& s){
    Audio_Download_RecvInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.userId);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.roomId);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.min);
    get_tokenval(s , v[4]+1 , v[5]-1 ,ret.sec);
    get_tokenval(s , v[5]+1 , v[6]-1 ,ret.msec);
    get_tokenval(s , v[6]+1 , v[7]-1 ,ret.status);
    get_tokenval(s , v[7]+1 , v[8]-1 ,ret.info);
    get_tokenval(s , v[8]+1 , v[9]-1 ,ret.sendtime);
    return ret;
}

JSON_Base Make_Json_Audio_Clean_SendInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["userId"] = 2;ret.mp2[2] = "userId";ret.mp3[2] = "i32";
    ret.mp1["roomId"] = 3;ret.mp2[3] = "roomId";ret.mp3[3] = "i32";
    ret.mp1["sendtime"] = 4;ret.mp2[4] = "sendtime";ret.mp3[4] = "i32";
    return ret;
};
JSON_Base Audio_Clean_SendInfo::json_base_ = Make_Json_Audio_Clean_SendInfo();
std::string Audio_Clean_SendInfo::Serialization(const Audio_Clean_SendInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.userId);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.roomId);
    ret += ",";	ret += gen_jsontoken(4,"i32",pkg.sendtime);
    ret += "}";
    return ret;
}
Audio_Clean_SendInfo Audio_Clean_SendInfo::Deserialization(const std::string& s){
    Audio_Clean_SendInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.userId);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.roomId);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.sendtime);
    return ret;
}
