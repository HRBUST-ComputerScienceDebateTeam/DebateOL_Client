#ifndef DALCONFIG_H
#define DALCONFIG_H
#include <bits/stdc++.h>
using namespace std;
#define SettoMap(x) mp[#x] = to_string(this->x)
#define SettoClass(x)  SettoClass_getval(ret.x , mp[#x])
#define ToBeSQLString(x) #x
std::string to_string(string x);
void SettoClass_getval(int &a    , string &s);
void SettoClass_getval(string& a , string &s);

#endif // DALCONFIG_H
