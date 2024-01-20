#include "openssl.h"

string sha256(string str){
  return QCryptographicHash::hash(str, QCryptographicHash::Sha256).toStdString();
}

std::string Base64Encode(string data)
{
    return QByteArray::fromStdString(data).toBase64().toStdString();
}


std::string Base64Decode(std::string src)
{
    return QByteArray::fromBase64(QByteArray::fromStdString(src)).toStdString();
}


std::string Base64toBase64URL(std::string s){
    //变符号 去除等号
    int len = s.length();
    string ret = s;
    for(int i = 0 ;i<len;i++){
        if(ret[i] == '+'){
            ret[i] = '-';
        }
        if(ret[i] == '/'){
            ret[i] = '_';
        }
        if(ret[i] == '='){
            ret = ret.substr(0 , i);
            break;
        }
    }
    return ret;
}

std::string Base64URLtoBase64(std::string s){
    //变符号 去除等号
    int len = s.length();
    string ret = s;
    for(int i = 0 ;i<len;i++){
        if(ret[i] == '-'){
            ret[i] = '+';
        }
        if(ret[i] == '_'){
            ret[i] = '/';
        }
    }

    //补齐长度为4的倍数
    if((len %4) == 0){
        return ret;
    }else if((len %4) == 1){
        ret+= "===";
        return ret;       
    }else if((len %4) == 2){
        ret+= "==";
        return ret;       
    }else{
        ret+= "=";
        return ret;       
    }
}
