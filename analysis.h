
// map与字符串格式转换
#include <map>
#include <vector>
#include <string>
#include<stdio.h>
#include<iostream>
using namespace std;

// 对象结构
struct StrData;
typedef map<string, StrData> Value;

struct StrData
{
    // 这个变量对应的键和值
    string key;
    string value;
    // 如果是对象
    Value obj_data;
};

// 根据字符串切割
// 只是针对这里获取对象分割的，不能用于其它分割
vector<string> splite(string str, string spl_str)
{
    // 返回的字符串数组
    vector<string> res;

    // 空字符串直接返回
	if("" == str) return  res;
    
    // 循环查找符合的字符串
    string tmp_str = str;
    while(true){
        size_t begin = tmp_str.find(spl_str);
        cout << "tmp_str:" << tmp_str << endl;
        // cout << "begin:" << begin << endl;
        
        
        // 第一个就是切割符要跳过,因为前面没有数据
        if (begin == 0) {
            tmp_str = tmp_str.substr(spl_str.length());
            continue;
        }
        
        // 没有找到,跳出循环
        if (begin == string::npos) {
            if (tmp_str.length() > 0) {
                res.push_back(tmp_str);
            }
            break;
        }

        // 如果是{}内的分割符要特殊处理
        size_t begin_postion = tmp_str.find("{");
        // cout << "begin_postion:" << begin_postion << endl;
        if (begin_postion != string::npos && begin_postion < begin) {
            // 找到配对的{}终点
            int Left_num = 0;
            int right_num = 0;
            int end_postion = 0;
            for(size_t i = begin_postion; i < tmp_str.length(); i++)
            {
                // 添加{}的数量
                if (tmp_str[i] == "{"[0]) {
                    Left_num ++;
                }else if (tmp_str[i] == "}"[0]) {
                    right_num ++;
                }
                
                // 如果Left_num == right_num, 说明找到结束点了
                if (Left_num == right_num) {
                    end_postion = i;
                    break;
                }
            
            }
            
            string postion_str = tmp_str.substr(0, end_postion + 1);
            res.push_back(postion_str);
            tmp_str = tmp_str.substr(end_postion + 1);
            continue;
        }else
        {
            // 找到分隔符
            string tmp_data = tmp_str.substr(0, begin);
            res.push_back(tmp_data);
            tmp_str = tmp_str.substr(begin+1);
        }
        
        

        
    }
    
    return res;
}

StrData get_value(string m_str)
{
    // 要解析的数据输出一下
    cout << "m_str:" << m_str << endl << endl;
    // 如果是原子数据
    size_t last_num = m_str.find_last_of("===");
    if (m_str.find_last_of("===") - 2 == m_str.find("==="))
    {
        int begin = m_str.find("===");
        string key = m_str.substr(0, begin);
        string value = m_str.substr(begin + 3, m_str.length());
        cout << "key:" << key << endl;
        cout << "value:" << value << endl << endl;

        StrData tmp_data;
        tmp_data.key = key;
        tmp_data.value = value;
        return tmp_data;
    }

    // 如果是对象数据
    // string str = "a==={b===1,c===abc,d==={e===1,f===asd}}";

    int begin = m_str.find("===");
    string key = m_str.substr(0, begin);
    string value = m_str.substr(begin + 4, m_str.length() - begin - 5);
    cout << "key:" << key << endl;
    cout << "value:" << value << endl;
    StrData tmp_data;
    tmp_data.key = key;
    Value obj_data;

    // 获取元素分割的数组
    vector<string> str_arr = splite(value, ",");
    
    for(size_t i = 0; i < str_arr.size(); i++)
    {
        cout << "str_arr_" << i << ":" << str_arr[i] << endl;
    }
    
    for(size_t i = 0; i < str_arr.size(); i++)
    {
        StrData tmp_arr_data = get_value(str_arr[i]);
        obj_data[tmp_arr_data.key] = tmp_arr_data;
    }

    tmp_data.obj_data = obj_data;
    return tmp_data;
}