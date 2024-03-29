//输入的是 thrift里面的结构体 
//输出的是 make_json_struct 里面的结构体

// struct Echo_SendInfo {
//     1:i32 id,
//     2:string info
// }


// struct Json_Echo_SendInfo{
//     std::map<std::string , int> mp1;//对应的是名称 - id
//     std::map<int , std::string>mp2;//id - 名称
//     std::map<int , std::string>mp3;//id - 类型
// }

//Json_Echo_SendInfo Make_Json_Echo_SendInfo(){
//      Json_Echo_SendInfo ret;
//      mp1["id"] = 1;mp2[1] = "id";mp3[1] = "i32";
//      mp1["info"] = 2;mp2[2] = "info";mp3[2] = "string";
//      return ret;
//}

#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

class INFO{
public:
    string name;
    string type;
    int id;
};

std::map<string , string>mp_lx{
    {"bool","bool"},
    {"i8","int8_t"},
    {"i16","int16_t"},
    {"i32","int32_t"},
    {"i64","int64_t"},
    {"byte","char"},
    {"string","string"}
};
int main(int argc , char ** argv){
    if(argc != 2){
        cerr << "input one file" <<endl;
        return 0;
    }
    fstream input;
    input.open(argv[1] , ios::out | ios::in );
    fstream output1 , output2;
    output1.open("./gen-code1.txt" , ios::out | ios::in |ios::trunc);
    output2.open("./gen-code2.txt" , ios::out | ios::in |ios::trunc );


    string unused;
    string s;
    string struct_name;
    while(input>>unused){
        if(unused == "service") break;
		if(unused != "struct") continue;//处理备注 备注只能单行位于结构体上面
        //处理第一行
        input >> struct_name;
        input >> unused;

        int id;
        string s_type;
        string s_name;
        vector<INFO>info;
        //尝试处理
        while(input >> s){
            if(s == "}"){//结束
                break;
            }else{
                if(!info.empty()){
                    info[info.size()-1].name = info[info.size()-1].name.substr(0 ,info[info.size()-1].name.length()-1);
                }
            }
            int pos = s.find(":");
            //获取id
            string s1 = s.substr(0,pos);
            id= atoi(s1.c_str());
            
            //获取类型
            string s2 = s.substr(pos+1,s.length() - pos);
            s_type = s2;
            
            //获取名称
            input >> s;
            s_name = s;
            info.push_back({s_name , s_type , id});
        }
        //生成类 idl -> struct
        output1 << "class "<<struct_name << "{" <<endl;
        output1 << "public:"<<endl;
        output1 << "\tstatic JSON_Base json_base_;"<<endl;
        output1 << "public:"<<endl;
        output1 << "\tstatic std::string Serialization(const "<<struct_name << " &);"<<endl;
        output1 << "\tstatic "<<struct_name << " Deserialization(const std::string&);"<<endl;
        output1 << "public:"<<endl;
            for(auto it :info ){
            output1 << "\t" << mp_lx[it.type] << " " << it.name <<";" << endl;
        }
        output1 << "};" <<endl;

// 上面的放入到 .h 
        // //生成解析结构体
        // output << "struct JSON_"<<struct_name << "{" <<endl;
        // output << "\tstd::map<std::string , int> mp1;//对应的是名称 - id" <<endl;
        // output << "\tstd::map<int , std::string>mp2;//id - 名称" <<endl;
        // output << "\tstd::map<int , std::string>mp3;//id - 类型" <<endl;
        // output << "};"<<endl;

        //填充解析结构体 函数
        output2 << "JSON_Base" <<" " << "Make_Json_" << struct_name << "(){" <<endl;
        output2 << "\t" << "JSON_Base" << " ret;" << endl;
        for(auto it:info){
            output2 << "\tret.mp1[\"" << it.name << "\"] = "<< it.id <<\
                    ";ret.mp2[" << it.id << "] = \"" << it.name << \
                    "\";ret.mp3[" << it.id <<"] = \"" <<it.type << "\";"<<endl; 
        }
        output2 << "\treturn ret;" <<endl;
        output2 << "};" <<endl;

        //定义初始化
        output2 << "JSON_Base "<<struct_name << "::json_base_ = Make_Json_"<< struct_name<<"();" <<endl;
        

        //json序列化生成器
        output2 << "std::string "<< struct_name <<"::Serialization(const "<<struct_name <<"&pkg""){" <<endl;
        output2 << "\tstd::string ret;" <<endl;
        output2 << "\tret += \"{\";" <<endl;
        int cnt = 0;
        for(auto it:info){
            if(cnt++)  output2 <<"\tret += \",\";";
            output2 << "\tret += gen_jsontoken("<<it.id <<",\""<<it.type<<"\","<<"pkg."<<it.name<<");"<<endl;
        }
        output2 << "\tret += \"}\";" <<endl;
        output2 <<"\treturn ret;" <<endl;
        output2 << "}" <<endl;

        //json反序列化生成器
        output2 << struct_name <<" " << struct_name<<"::Deserialization(const std::string& s){" <<endl;
        output2 << "\t" << struct_name << " ret;" <<endl;
        output2 << "\tstd::vector<int>v;" <<endl;
        output2 << "\tv.push_back(0);"<<endl;
        output2 << "\tfor(int i = 1;i<s.length()-1;i++){" <<endl;
        output2 << "\t\tif(s[i] == ',' && s[i-1] == '}' && s[i+1] =='\\\"'){" << endl;
        output2 << "\t\t\tv.push_back(i);"<< endl;
        output2 << "\t\t}" <<endl;
        output2 << "\t}" <<endl;
        output2 << "\tv.push_back(s.length()-1);" <<endl;
        cnt = 0;
        for(auto it: info){
            output2 << "\tget_tokenval(s , v["<<cnt<<"]+1 , v["<<cnt+1<<"]-1 ,ret."<<it.name<<");" <<endl;
            cnt++;
        }
        output2 << "\treturn ret;" << endl;
        output2 << "}" <<endl;

        
    }
    input.close();
    output1.close();
    output2.close();
}
