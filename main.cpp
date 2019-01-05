
#include<stdio.h>
#include<iostream>
#include"analysis.h"

using namespace std;
// 解析map与字符串之间的互相转换

main(){
    string str = "aa==={,bb===1,cc===abc,df==={er===1,ff===asd},ggg===2}";
    StrData num = get_value(str);
    // sleep(1);
    return 0;
}