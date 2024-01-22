//提供访问数据库的方法
#include "dal_room.h"
#include <bits/stdc++.h>
#include <string>


//提供dal类和map的转换方式
//完善tomap函数
//完善toclass
map<string , string> DAL_Room_Base::toMap(){
    map<string , string>mp;
    SettoMap(Roomid)          ;         
    SettoMap(Roomnum)         ;          
    SettoMap(Passwd)          ;         
    SettoMap(Salt)            ;      
    SettoMap(RoomCreatetime)  ;     
    return mp;
}
DAL_Room_Base DAL_Room_Base::ToClass(map<string , string> mp){
    DAL_Room_Base ret;
    SettoClass(Roomid)          ;         
    SettoClass(Roomnum)         ;          
    SettoClass(Passwd)          ;                   
    SettoClass(RoomCreatetime)  ;               
    SettoClass(Salt)            ;       
    return ret;
}

map<string , string> DAL_Room_Extra::toMap(){
    map<string , string>mp;
    SettoMap(Roomid)               ;       
    SettoMap(Roomnum)              ;                 
    SettoMap(Roomname)             ;          
    SettoMap(Signature)            ;              
    SettoMap(Islocking)            ;           
    SettoMap(Debate_posbitmap)     ;          
    SettoMap(Debate_name)          ;  
    return mp;
}

DAL_Room_Extra DAL_Room_Extra::ToClass(map<string , string>mp ){
    DAL_Room_Extra ret;
    SettoClass(Roomid)               ;       
    SettoClass(Roomnum)              ;                 
    SettoClass(Roomname)             ;          
    SettoClass(Signature)            ;              
    SettoClass(Islocking)            ;           
    SettoClass(Debate_posbitmap)     ;          
    SettoClass(Debate_name)          ;  
    return ret;
}

map<string , string> DAL_UR_relation::toMap(){
    map<string , string>mp;
    SettoMap(Userid)               ;       
    SettoMap(Roomid)               ;                 
    SettoMap(Debate_pos)           ;  
    SettoMap(Permissions)          ;            
    return mp;
}

DAL_UR_relation DAL_UR_relation::ToClass(map<string , string>mp ){
    DAL_UR_relation ret;
    SettoClass(Userid)               ;       
    SettoClass(Roomid)               ;                 
    SettoClass(Debate_pos)           ;   
    SettoClass(Permissions)          ;        
    return ret;
}
