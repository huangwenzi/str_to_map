
#include<stdio.h>
#include<iostream>
#include"analysis.h"

using namespace std;
// 解析map与字符串之间的互相转换

main(){
    string str = "a==={,b===1,c===abc,d==={e===1,f===asd},g===2}";
    StrData num = get_value(str);
    // sleep(1);
    return 0;
}