#include "./thrift_json_config.h"
JSON_Base Make_Json_User_GetBaseInfo_SendInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["jwt_token"] = 2;ret.mp2[2] = "jwt_token";ret.mp3[2] = "string";
    ret.mp1["sendtime"] = 3;ret.mp2[3] = "sendtime";ret.mp3[3] = "i32";
    ret.mp1["Aim_usernum"] = 4;ret.mp2[4] = "Aim_usernum";ret.mp3[4] = "string";
    ret.mp1["info"] = 5;ret.mp2[5] = "info";ret.mp3[5] = "string";
    return ret;
};
JSON_Base User_GetBaseInfo_SendInfo::json_base_ = Make_Json_User_GetBaseInfo_SendInfo();
std::string User_GetBaseInfo_SendInfo::Serialization(const User_GetBaseInfo_SendInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"string",pkg.jwt_token);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(4,"string",pkg.Aim_usernum);
    ret += ",";	ret += gen_jsontoken(5,"string",pkg.info);
    ret += "}";
    return ret;
}
User_GetBaseInfo_SendInfo User_GetBaseInfo_SendInfo::Deserialization(const std::string& s){
    User_GetBaseInfo_SendInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.jwt_token);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.sendtime);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.Aim_usernum);
    get_tokenval(s , v[4]+1 , v[5]-1 ,ret.info);
    return ret;
}
JSON_Base Make_Json_User_GetBaseInfo_RecvInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["sendtime"] = 2;ret.mp2[2] = "sendtime";ret.mp3[2] = "i32";
    ret.mp1["status"] = 3;ret.mp2[3] = "status";ret.mp3[3] = "i32";
    ret.mp1["info"] = 4;ret.mp2[4] = "info";ret.mp3[4] = "string";
    return ret;
};
JSON_Base User_GetBaseInfo_RecvInfo::json_base_ = Make_Json_User_GetBaseInfo_RecvInfo();
std::string User_GetBaseInfo_RecvInfo::Serialization(const User_GetBaseInfo_RecvInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.status);
    ret += ",";	ret += gen_jsontoken(4,"string",pkg.info);
    ret += "}";
    return ret;
}
User_GetBaseInfo_RecvInfo User_GetBaseInfo_RecvInfo::Deserialization(const std::string& s){
    User_GetBaseInfo_RecvInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.sendtime);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.status);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.info);
    return ret;
}
JSON_Base Make_Json_User_GetSocialInfo_SendInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["jwt_token"] = 2;ret.mp2[2] = "jwt_token";ret.mp3[2] = "string";
    ret.mp1["sendtime"] = 3;ret.mp2[3] = "sendtime";ret.mp3[3] = "i32";
    ret.mp1["Aim_usernum"] = 4;ret.mp2[4] = "Aim_usernum";ret.mp3[4] = "string";
    ret.mp1["info"] = 5;ret.mp2[5] = "info";ret.mp3[5] = "string";
    return ret;
};
JSON_Base User_GetSocialInfo_SendInfo::json_base_ = Make_Json_User_GetSocialInfo_SendInfo();
std::string User_GetSocialInfo_SendInfo::Serialization(const User_GetSocialInfo_SendInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"string",pkg.jwt_token);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(4,"string",pkg.Aim_usernum);
    ret += ",";	ret += gen_jsontoken(5,"string",pkg.info);
    ret += "}";
    return ret;
}
User_GetSocialInfo_SendInfo User_GetSocialInfo_SendInfo::Deserialization(const std::string& s){
    User_GetSocialInfo_SendInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.jwt_token);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.sendtime);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.Aim_usernum);
    get_tokenval(s , v[4]+1 , v[5]-1 ,ret.info);
    return ret;
}
JSON_Base Make_Json_User_GetSocialInfo_RecvInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["sendtime"] = 2;ret.mp2[2] = "sendtime";ret.mp3[2] = "i32";
    ret.mp1["status"] = 3;ret.mp2[3] = "status";ret.mp3[3] = "i32";
    ret.mp1["info"] = 4;ret.mp2[4] = "info";ret.mp3[4] = "string";
    return ret;
};
JSON_Base User_GetSocialInfo_RecvInfo::json_base_ = Make_Json_User_GetSocialInfo_RecvInfo();
std::string User_GetSocialInfo_RecvInfo::Serialization(const User_GetSocialInfo_RecvInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.status);
    ret += ",";	ret += gen_jsontoken(4,"string",pkg.info);
    ret += "}";
    return ret;
}
User_GetSocialInfo_RecvInfo User_GetSocialInfo_RecvInfo::Deserialization(const std::string& s){
    User_GetSocialInfo_RecvInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.sendtime);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.status);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.info);
    return ret;
}
JSON_Base Make_Json_User_GetExInfo_SendInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["jwt_token"] = 2;ret.mp2[2] = "jwt_token";ret.mp3[2] = "string";
    ret.mp1["sendtime"] = 3;ret.mp2[3] = "sendtime";ret.mp3[3] = "i32";
    ret.mp1["Aim_usernum"] = 4;ret.mp2[4] = "Aim_usernum";ret.mp3[4] = "string";
    ret.mp1["info"] = 5;ret.mp2[5] = "info";ret.mp3[5] = "string";
    return ret;
};
JSON_Base User_GetExInfo_SendInfo::json_base_ = Make_Json_User_GetExInfo_SendInfo();
std::string User_GetExInfo_SendInfo::Serialization(const User_GetExInfo_SendInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"string",pkg.jwt_token);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(4,"string",pkg.Aim_usernum);
    ret += ",";	ret += gen_jsontoken(5,"string",pkg.info);
    ret += "}";
    return ret;
}
User_GetExInfo_SendInfo User_GetExInfo_SendInfo::Deserialization(const std::string& s){
    User_GetExInfo_SendInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.jwt_token);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.sendtime);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.Aim_usernum);
    get_tokenval(s , v[4]+1 , v[5]-1 ,ret.info);
    return ret;
}
JSON_Base Make_Json_User_GetExInfo_RecvInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["sendtime"] = 2;ret.mp2[2] = "sendtime";ret.mp3[2] = "i32";
    ret.mp1["status"] = 3;ret.mp2[3] = "status";ret.mp3[3] = "i32";
    ret.mp1["info"] = 4;ret.mp2[4] = "info";ret.mp3[4] = "string";
    return ret;
};
JSON_Base User_GetExInfo_RecvInfo::json_base_ = Make_Json_User_GetExInfo_RecvInfo();
std::string User_GetExInfo_RecvInfo::Serialization(const User_GetExInfo_RecvInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.status);
    ret += ",";	ret += gen_jsontoken(4,"string",pkg.info);
    ret += "}";
    return ret;
}
User_GetExInfo_RecvInfo User_GetExInfo_RecvInfo::Deserialization(const std::string& s){
    User_GetExInfo_RecvInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.sendtime);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.status);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.info);
    return ret;
}
JSON_Base Make_Json_User_reg_SendInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["sendtime"] = 2;ret.mp2[2] = "sendtime";ret.mp3[2] = "i32";
    ret.mp1["tel"] = 3;ret.mp2[3] = "tel";ret.mp3[3] = "string";
    ret.mp1["usernum"] = 4;ret.mp2[4] = "usernum";ret.mp3[4] = "string";
    ret.mp1["passwd"] = 5;ret.mp2[5] = "passwd";ret.mp3[5] = "string";
    return ret;
};
JSON_Base User_reg_SendInfo::json_base_ = Make_Json_User_reg_SendInfo();
std::string User_reg_SendInfo::Serialization(const User_reg_SendInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(3,"string",pkg.tel);
    ret += ",";	ret += gen_jsontoken(4,"string",pkg.usernum);
    ret += ",";	ret += gen_jsontoken(5,"string",pkg.passwd);
    ret += "}";
    return ret;
}
User_reg_SendInfo User_reg_SendInfo::Deserialization(const std::string& s){
    User_reg_SendInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.sendtime);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.tel);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.usernum);
    get_tokenval(s , v[4]+1 , v[5]-1 ,ret.passwd);
    return ret;
}
JSON_Base Make_Json_User_reg_RecvInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["sendtime"] = 2;ret.mp2[2] = "sendtime";ret.mp3[2] = "i32";
    ret.mp1["status"] = 3;ret.mp2[3] = "status";ret.mp3[3] = "i32";
    return ret;
};
JSON_Base User_reg_RecvInfo::json_base_ = Make_Json_User_reg_RecvInfo();
std::string User_reg_RecvInfo::Serialization(const User_reg_RecvInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.status);
    ret += "}";
    return ret;
}
User_reg_RecvInfo User_reg_RecvInfo::Deserialization(const std::string& s){
    User_reg_RecvInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.sendtime);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.status);
    return ret;
}
JSON_Base Make_Json_User_login_Tel_SendInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["sendtime"] = 2;ret.mp2[2] = "sendtime";ret.mp3[2] = "i32";
    ret.mp1["tel"] = 3;ret.mp2[3] = "tel";ret.mp3[3] = "string";
    ret.mp1["passwd"] = 4;ret.mp2[4] = "passwd";ret.mp3[4] = "string";
    return ret;
};
JSON_Base User_login_Tel_SendInfo::json_base_ = Make_Json_User_login_Tel_SendInfo();
std::string User_login_Tel_SendInfo::Serialization(const User_login_Tel_SendInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(3,"string",pkg.tel);
    ret += ",";	ret += gen_jsontoken(4,"string",pkg.passwd);
    ret += "}";
    return ret;
}
User_login_Tel_SendInfo User_login_Tel_SendInfo::Deserialization(const std::string& s){
    User_login_Tel_SendInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.sendtime);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.tel);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.passwd);
    return ret;
}
JSON_Base Make_Json_User_login_num_SendInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["sendtime"] = 2;ret.mp2[2] = "sendtime";ret.mp3[2] = "i32";
    ret.mp1["usernum"] = 3;ret.mp2[3] = "usernum";ret.mp3[3] = "string";
    ret.mp1["passwd"] = 4;ret.mp2[4] = "passwd";ret.mp3[4] = "string";
    return ret;
};
JSON_Base User_login_num_SendInfo::json_base_ = Make_Json_User_login_num_SendInfo();
std::string User_login_num_SendInfo::Serialization(const User_login_num_SendInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(3,"string",pkg.usernum);
    ret += ",";	ret += gen_jsontoken(4,"string",pkg.passwd);
    ret += "}";
    return ret;
}
User_login_num_SendInfo User_login_num_SendInfo::Deserialization(const std::string& s){
    User_login_num_SendInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.sendtime);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.usernum);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.passwd);
    return ret;
}
JSON_Base Make_Json_User_login_RecvInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["sendtime"] = 2;ret.mp2[2] = "sendtime";ret.mp3[2] = "i32";
    ret.mp1["status"] = 3;ret.mp2[3] = "status";ret.mp3[3] = "i32";
    ret.mp1["jwt_token"] = 4;ret.mp2[4] = "jwt_token";ret.mp3[4] = "string";
    ret.mp1["refresh_jwt_token"] = 5;ret.mp2[5] = "refresh_jwt_token";ret.mp3[5] = "string";
    return ret;
};
JSON_Base User_login_RecvInfo::json_base_ = Make_Json_User_login_RecvInfo();
std::string User_login_RecvInfo::Serialization(const User_login_RecvInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.status);
    ret += ",";	ret += gen_jsontoken(4,"string",pkg.jwt_token);
    ret += ",";	ret += gen_jsontoken(5,"string",pkg.refresh_jwt_token);
    ret += "}";
    return ret;
}
User_login_RecvInfo User_login_RecvInfo::Deserialization(const std::string& s){
    User_login_RecvInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.sendtime);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.status);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.jwt_token);
    get_tokenval(s , v[4]+1 , v[5]-1 ,ret.refresh_jwt_token);
    return ret;
}
JSON_Base Make_Json_User_logoff_SendInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["jwt_token"] = 2;ret.mp2[2] = "jwt_token";ret.mp3[2] = "string";
    ret.mp1["sendtime,"] = 3;ret.mp2[3] = "sendtime,";ret.mp3[3] = "i32";
    return ret;
};
JSON_Base User_logoff_SendInfo::json_base_ = Make_Json_User_logoff_SendInfo();
std::string User_logoff_SendInfo::Serialization(const User_logoff_SendInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"string",pkg.jwt_token);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.sendtime);
    ret += "}";
    return ret;
}
User_logoff_SendInfo User_logoff_SendInfo::Deserialization(const std::string& s){
    User_logoff_SendInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.jwt_token);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.sendtime);
    return ret;
}
JSON_Base Make_Json_User_logoff_RecvInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["sendtime"] = 2;ret.mp2[2] = "sendtime";ret.mp3[2] = "i32";
    ret.mp1["status"] = 3;ret.mp2[3] = "status";ret.mp3[3] = "i32";
    return ret;
};
JSON_Base User_logoff_RecvInfo::json_base_ = Make_Json_User_logoff_RecvInfo();
std::string User_logoff_RecvInfo::Serialization(const User_logoff_RecvInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.status);
    ret += "}";
    return ret;
}
User_logoff_RecvInfo User_logoff_RecvInfo::Deserialization(const std::string& s){
    User_logoff_RecvInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.sendtime);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.status);
    return ret;
}
JSON_Base Make_Json_User_refresh_jwt1_SendInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["sendtime"] = 2;ret.mp2[2] = "sendtime";ret.mp3[2] = "i32";
    ret.mp1["jwt_token"] = 3;ret.mp2[3] = "jwt_token";ret.mp3[3] = "string";
    ret.mp1["refresh_jwt_token"] = 4;ret.mp2[4] = "refresh_jwt_token";ret.mp3[4] = "string";
    return ret;
};
JSON_Base User_refresh_jwt1_SendInfo::json_base_ = Make_Json_User_refresh_jwt1_SendInfo();
std::string User_refresh_jwt1_SendInfo::Serialization(const User_refresh_jwt1_SendInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(3,"string",pkg.jwt_token);
    ret += ",";	ret += gen_jsontoken(4,"string",pkg.refresh_jwt_token);
    ret += "}";
    return ret;
}
User_refresh_jwt1_SendInfo User_refresh_jwt1_SendInfo::Deserialization(const std::string& s){
    User_refresh_jwt1_SendInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.sendtime);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.jwt_token);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.refresh_jwt_token);
    return ret;
}
JSON_Base Make_Json_User_refresh_jwt1_RecvInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["sendtime"] = 2;ret.mp2[2] = "sendtime";ret.mp3[2] = "i32";
    ret.mp1["status"] = 3;ret.mp2[3] = "status";ret.mp3[3] = "i32";
    ret.mp1["jwt_token"] = 4;ret.mp2[4] = "jwt_token";ret.mp3[4] = "string";
    return ret;
};
JSON_Base User_refresh_jwt1_RecvInfo::json_base_ = Make_Json_User_refresh_jwt1_RecvInfo();
std::string User_refresh_jwt1_RecvInfo::Serialization(const User_refresh_jwt1_RecvInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.status);
    ret += ",";	ret += gen_jsontoken(4,"string",pkg.jwt_token);
    ret += "}";
    return ret;
}
User_refresh_jwt1_RecvInfo User_refresh_jwt1_RecvInfo::Deserialization(const std::string& s){
    User_refresh_jwt1_RecvInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.sendtime);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.status);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.jwt_token);
    return ret;
}
JSON_Base Make_Json_User_refresh_jwt2_SendInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["sendtime"] = 2;ret.mp2[2] = "sendtime";ret.mp3[2] = "i32";
    ret.mp1["jwt_token"] = 3;ret.mp2[3] = "jwt_token";ret.mp3[3] = "string";
    ret.mp1["refresh_jwt_token"] = 4;ret.mp2[4] = "refresh_jwt_token";ret.mp3[4] = "string";
    return ret;
};
JSON_Base User_refresh_jwt2_SendInfo::json_base_ = Make_Json_User_refresh_jwt2_SendInfo();
std::string User_refresh_jwt2_SendInfo::Serialization(const User_refresh_jwt2_SendInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(3,"string",pkg.jwt_token);
    ret += ",";	ret += gen_jsontoken(4,"string",pkg.refresh_jwt_token);
    ret += "}";
    return ret;
}
User_refresh_jwt2_SendInfo User_refresh_jwt2_SendInfo::Deserialization(const std::string& s){
    User_refresh_jwt2_SendInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.sendtime);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.jwt_token);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.refresh_jwt_token);
    return ret;
}
JSON_Base Make_Json_User_refresh_jwt2_RecvInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["sendtime"] = 2;ret.mp2[2] = "sendtime";ret.mp3[2] = "i32";
    ret.mp1["status"] = 3;ret.mp2[3] = "status";ret.mp3[3] = "i32";
    ret.mp1["jwt_token"] = 4;ret.mp2[4] = "jwt_token";ret.mp3[4] = "string";
    ret.mp1["refresh_jwt_token"] = 5;ret.mp2[5] = "refresh_jwt_token";ret.mp3[5] = "string";
    return ret;
};
JSON_Base User_refresh_jwt2_RecvInfo::json_base_ = Make_Json_User_refresh_jwt2_RecvInfo();
std::string User_refresh_jwt2_RecvInfo::Serialization(const User_refresh_jwt2_RecvInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.status);
    ret += ",";	ret += gen_jsontoken(4,"string",pkg.jwt_token);
    ret += ",";	ret += gen_jsontoken(5,"string",pkg.refresh_jwt_token);
    ret += "}";
    return ret;
}
User_refresh_jwt2_RecvInfo User_refresh_jwt2_RecvInfo::Deserialization(const std::string& s){
    User_refresh_jwt2_RecvInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.sendtime);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.status);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.jwt_token);
    get_tokenval(s , v[4]+1 , v[5]-1 ,ret.refresh_jwt_token);
    return ret;
}
JSON_Base Make_Json_User_friend_SendInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["jwt_token"] = 2;ret.mp2[2] = "jwt_token";ret.mp3[2] = "string";
    ret.mp1["sendtime"] = 3;ret.mp2[3] = "sendtime";ret.mp3[3] = "i32";
    return ret;
};
JSON_Base User_friend_SendInfo::json_base_ = Make_Json_User_friend_SendInfo();
std::string User_friend_SendInfo::Serialization(const User_friend_SendInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"string",pkg.jwt_token);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.sendtime);
    ret += "}";
    return ret;
}
User_friend_SendInfo User_friend_SendInfo::Deserialization(const std::string& s){
    User_friend_SendInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.jwt_token);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.sendtime);
    return ret;
}
JSON_Base Make_Json_User_friend_RecvInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["sendtime"] = 2;ret.mp2[2] = "sendtime";ret.mp3[2] = "i32";
    ret.mp1["status"] = 3;ret.mp2[3] = "status";ret.mp3[3] = "i32";
    ret.mp1["info"] = 4;ret.mp2[4] = "info";ret.mp3[4] = "string";
    return ret;
};
JSON_Base User_friend_RecvInfo::json_base_ = Make_Json_User_friend_RecvInfo();
std::string User_friend_RecvInfo::Serialization(const User_friend_RecvInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.status);
    ret += ",";	ret += gen_jsontoken(4,"string",pkg.info);
    ret += "}";
    return ret;
}
User_friend_RecvInfo User_friend_RecvInfo::Deserialization(const std::string& s){
    User_friend_RecvInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.sendtime);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.status);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.info);
    return ret;
}
JSON_Base Make_Json_User_follow_SendInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["jwt_token"] = 2;ret.mp2[2] = "jwt_token";ret.mp3[2] = "string";
    ret.mp1["sendtime"] = 3;ret.mp2[3] = "sendtime";ret.mp3[3] = "i32";
    return ret;
};
JSON_Base User_follow_SendInfo::json_base_ = Make_Json_User_follow_SendInfo();
std::string User_follow_SendInfo::Serialization(const User_follow_SendInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"string",pkg.jwt_token);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.sendtime);
    ret += "}";
    return ret;
}
User_follow_SendInfo User_follow_SendInfo::Deserialization(const std::string& s){
    User_follow_SendInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.jwt_token);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.sendtime);
    return ret;
}
JSON_Base Make_Json_User_follow_RecvInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["sendtime"] = 2;ret.mp2[2] = "sendtime";ret.mp3[2] = "i32";
    ret.mp1["status"] = 3;ret.mp2[3] = "status";ret.mp3[3] = "i32";
    ret.mp1["info"] = 4;ret.mp2[4] = "info";ret.mp3[4] = "string";
    return ret;
};
JSON_Base User_follow_RecvInfo::json_base_ = Make_Json_User_follow_RecvInfo();
std::string User_follow_RecvInfo::Serialization(const User_follow_RecvInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.status);
    ret += ",";	ret += gen_jsontoken(4,"string",pkg.info);
    ret += "}";
    return ret;
}
User_follow_RecvInfo User_follow_RecvInfo::Deserialization(const std::string& s){
    User_follow_RecvInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.sendtime);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.status);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.info);
    return ret;
}
JSON_Base Make_Json_User_followed_SendInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["jwt_token"] = 2;ret.mp2[2] = "jwt_token";ret.mp3[2] = "string";
    ret.mp1["sendtime"] = 3;ret.mp2[3] = "sendtime";ret.mp3[3] = "i32";
    return ret;
};
JSON_Base User_followed_SendInfo::json_base_ = Make_Json_User_followed_SendInfo();
std::string User_followed_SendInfo::Serialization(const User_followed_SendInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"string",pkg.jwt_token);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.sendtime);
    ret += "}";
    return ret;
}
User_followed_SendInfo User_followed_SendInfo::Deserialization(const std::string& s){
    User_followed_SendInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.jwt_token);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.sendtime);
    return ret;
}
JSON_Base Make_Json_User_followed_RecvInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["sendtime"] = 2;ret.mp2[2] = "sendtime";ret.mp3[2] = "i32";
    ret.mp1["status"] = 3;ret.mp2[3] = "status";ret.mp3[3] = "i32";
    ret.mp1["info"] = 4;ret.mp2[4] = "info";ret.mp3[4] = "string";
    return ret;
};
JSON_Base User_followed_RecvInfo::json_base_ = Make_Json_User_followed_RecvInfo();
std::string User_followed_RecvInfo::Serialization(const User_followed_RecvInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.status);
    ret += ",";	ret += gen_jsontoken(4,"string",pkg.info);
    ret += "}";
    return ret;
}
User_followed_RecvInfo User_followed_RecvInfo::Deserialization(const std::string& s){
    User_followed_RecvInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.sendtime);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.status);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.info);
    return ret;
}
JSON_Base Make_Json_User_ModifyBaseInfo_SendInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["jwt_token"] = 2;ret.mp2[2] = "jwt_token";ret.mp3[2] = "string";
    ret.mp1["sendtime"] = 3;ret.mp2[3] = "sendtime";ret.mp3[3] = "i32";
    ret.mp1["modifyinfo"] = 4;ret.mp2[4] = "modifyinfo";ret.mp3[4] = "string";
    return ret;
};
JSON_Base User_ModifyBaseInfo_SendInfo::json_base_ = Make_Json_User_ModifyBaseInfo_SendInfo();
std::string User_ModifyBaseInfo_SendInfo::Serialization(const User_ModifyBaseInfo_SendInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"string",pkg.jwt_token);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(4,"string",pkg.modifyinfo);
    ret += "}";
    return ret;
}
User_ModifyBaseInfo_SendInfo User_ModifyBaseInfo_SendInfo::Deserialization(const std::string& s){
    User_ModifyBaseInfo_SendInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.jwt_token);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.sendtime);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.modifyinfo);
    return ret;
}
JSON_Base Make_Json_User_ModifyBaseInfo_RecvInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["sendtime"] = 2;ret.mp2[2] = "sendtime";ret.mp3[2] = "i32";
    ret.mp1["status"] = 3;ret.mp2[3] = "status";ret.mp3[3] = "i32";
    return ret;
};
JSON_Base User_ModifyBaseInfo_RecvInfo::json_base_ = Make_Json_User_ModifyBaseInfo_RecvInfo();
std::string User_ModifyBaseInfo_RecvInfo::Serialization(const User_ModifyBaseInfo_RecvInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.status);
    ret += "}";
    return ret;
}
User_ModifyBaseInfo_RecvInfo User_ModifyBaseInfo_RecvInfo::Deserialization(const std::string& s){
    User_ModifyBaseInfo_RecvInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.sendtime);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.status);
    return ret;
}
JSON_Base Make_Json_User_ModifySocialInfo_SendInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["jwt_token"] = 2;ret.mp2[2] = "jwt_token";ret.mp3[2] = "string";
    ret.mp1["sendtime"] = 3;ret.mp2[3] = "sendtime";ret.mp3[3] = "i32";
    ret.mp1["modifyinfo"] = 4;ret.mp2[4] = "modifyinfo";ret.mp3[4] = "string";
    return ret;
};
JSON_Base User_ModifySocialInfo_SendInfo::json_base_ = Make_Json_User_ModifySocialInfo_SendInfo();
std::string User_ModifySocialInfo_SendInfo::Serialization(const User_ModifySocialInfo_SendInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"string",pkg.jwt_token);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(4,"string",pkg.modifyinfo);
    ret += "}";
    return ret;
}
User_ModifySocialInfo_SendInfo User_ModifySocialInfo_SendInfo::Deserialization(const std::string& s){
    User_ModifySocialInfo_SendInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.jwt_token);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.sendtime);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.modifyinfo);
    return ret;
}
JSON_Base Make_Json_User_ModifySocialInfo_RecvInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["sendtime"] = 2;ret.mp2[2] = "sendtime";ret.mp3[2] = "i32";
    ret.mp1["status"] = 3;ret.mp2[3] = "status";ret.mp3[3] = "i32";
    return ret;
};
JSON_Base User_ModifySocialInfo_RecvInfo::json_base_ = Make_Json_User_ModifySocialInfo_RecvInfo();
std::string User_ModifySocialInfo_RecvInfo::Serialization(const User_ModifySocialInfo_RecvInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.status);
    ret += "}";
    return ret;
}
User_ModifySocialInfo_RecvInfo User_ModifySocialInfo_RecvInfo::Deserialization(const std::string& s){
    User_ModifySocialInfo_RecvInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.sendtime);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.status);
    return ret;
}
JSON_Base Make_Json_User_ModifyExInfo_SendInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["jwt_token"] = 2;ret.mp2[2] = "jwt_token";ret.mp3[2] = "string";
    ret.mp1["sendtime"] = 3;ret.mp2[3] = "sendtime";ret.mp3[3] = "i32";
    ret.mp1["modifyinfo"] = 4;ret.mp2[4] = "modifyinfo";ret.mp3[4] = "string";
    return ret;
};
JSON_Base User_ModifyExInfo_SendInfo::json_base_ = Make_Json_User_ModifyExInfo_SendInfo();
std::string User_ModifyExInfo_SendInfo::Serialization(const User_ModifyExInfo_SendInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"string",pkg.jwt_token);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(4,"string",pkg.modifyinfo);
    ret += "}";
    return ret;
}
User_ModifyExInfo_SendInfo User_ModifyExInfo_SendInfo::Deserialization(const std::string& s){
    User_ModifyExInfo_SendInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.jwt_token);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.sendtime);
    get_tokenval(s , v[3]+1 , v[4]-1 ,ret.modifyinfo);
    return ret;
}
JSON_Base Make_Json_User_ModifyExInfo_RecvInfo(){
    JSON_Base ret;
    ret.mp1["type"] = 1;ret.mp2[1] = "type";ret.mp3[1] = "i32";
    ret.mp1["sendtime"] = 2;ret.mp2[2] = "sendtime";ret.mp3[2] = "i32";
    ret.mp1["status"] = 3;ret.mp2[3] = "status";ret.mp3[3] = "i32";
    return ret;
};
JSON_Base User_ModifyExInfo_RecvInfo::json_base_ = Make_Json_User_ModifyExInfo_RecvInfo();
std::string User_ModifyExInfo_RecvInfo::Serialization(const User_ModifyExInfo_RecvInfo&pkg){
    std::string ret;
    ret += "{";
    ret += gen_jsontoken(1,"i32",pkg.type);
    ret += ",";	ret += gen_jsontoken(2,"i32",pkg.sendtime);
    ret += ",";	ret += gen_jsontoken(3,"i32",pkg.status);
    ret += "}";
    return ret;
}
User_ModifyExInfo_RecvInfo User_ModifyExInfo_RecvInfo::Deserialization(const std::string& s){
    User_ModifyExInfo_RecvInfo ret;
    std::vector<int>v;
    v.push_back(0);
    for(int i = 1;i<s.length()-1;i++){
        if(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\"'){
            v.push_back(i);
        }
    }
    v.push_back(s.length()-1);
    get_tokenval(s , v[0]+1 , v[1]-1 ,ret.type);
    get_tokenval(s , v[1]+1 , v[2]-1 ,ret.sendtime);
    get_tokenval(s , v[2]+1 , v[3]-1 ,ret.status);
    return ret;
}
