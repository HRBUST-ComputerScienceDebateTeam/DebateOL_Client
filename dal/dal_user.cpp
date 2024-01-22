//提供访问数据库的方法
#include "dal_user.h"

#include <string>





//提供dal类和map的转换方式
//完善tomap函数
//完善toclass
map<string , string> DAL_User_Base::toMap(){
    map<string , string>mp;
    SettoMap(Userid)          ;         
    SettoMap(Usernum)         ;          
    SettoMap(Passwd)          ;         
    SettoMap(Tel)             ;      
    SettoMap(UserRegtime)     ;              
    SettoMap(UserLasttime)    ;               
    SettoMap(Salt)            ;       
    return mp;
}
DAL_User_Base DAL_User_Base::ToClass(map<string , string> mp){
    DAL_User_Base ret;
    SettoClass(Userid)          ;         
    SettoClass(Usernum)         ;          
    SettoClass(Passwd)          ;         
    SettoClass(Tel)             ;      
    SettoClass(UserRegtime)     ;              
    SettoClass(UserLasttime)    ;               
    SettoClass(Salt)            ;       
    return ret;
}

map<string , string> DAL_User_Social::toMap(){
    map<string , string>mp;
    SettoMap(Userid)   ;                            
    SettoMap(Username) ;                              
    SettoMap(Headshot) ;                              
    SettoMap(Sex)      ;                         
    SettoMap(Signature);                               
    SettoMap(Contact)  ;     
    return mp;
}

DAL_User_Social DAL_User_Social::ToClass(map<string , string>mp ){
    DAL_User_Social ret;
    SettoClass(Userid)   ;                            
    SettoClass(Username) ;                              
    SettoClass(Headshot) ;                              
    SettoClass(Sex)      ;                         
    SettoClass(Signature);                               
    SettoClass(Contact)  ; 
    return ret;
}


map<string , string> DAL_User_Extra::toMap(){
    map<string , string>mp;
    SettoMap(Userid)             ;       
    SettoMap(IntentionToArgue)   ;                 
    SettoMap(MatcheNum)          ;          
    SettoMap(BestPlayerNum)      ;              
    SettoMap(VectoryNum)         ;           
    SettoMap(OnePosNum)          ;          
    SettoMap(TwoPosNum)          ;          
    SettoMap(ThreePosNum)        ;            
    SettoMap(FourPosNum)         ;
    return mp;
}

DAL_User_Extra DAL_User_Extra::ToClass(map<string , string>mp ){
    DAL_User_Extra ret;
    SettoClass(Userid)             ;       
    SettoClass(IntentionToArgue)   ;                 
    SettoClass(MatcheNum)          ;          
    SettoClass(BestPlayerNum)      ;              
    SettoClass(VectoryNum)         ;           
    SettoClass(OnePosNum)          ;          
    SettoClass(TwoPosNum)          ;          
    SettoClass(ThreePosNum)        ;            
    SettoClass(FourPosNum)         ;
    return ret;
}

map<string , string> DAL_UU_relation::toMap(){
    map<string , string>mp;
    SettoMap(UseridA)          ;       
    SettoMap(UseridB)          ;                 
    SettoMap(UULevel)          ;          
    return mp;
}

DAL_UU_relation DAL_UU_relation::ToClass(map<string , string>mp ){
    DAL_UU_relation ret;
    SettoClass(UseridA)          ;       
    SettoClass(UseridB)          ;                 
    SettoClass(UULevel)          ;          
    return ret;
}
