#include <bits/stdc++.h>

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
inline std::string gen_jsontoken(int id, std::string type_name , VAL_TYPE val);

inline std::string gen_jsontoken(int id, std::string type_name , char val);

inline std::string gen_jsontoken(int id, std::string type_name , string val);

template<typename VAL_TYPE>
void get_tokenval(const string &s , int l , int r , VAL_TYPE & typeval );

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


