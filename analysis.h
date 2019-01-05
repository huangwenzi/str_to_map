#ifndef ANALYSIS_H
#define ANALYSIS_H
// map与字符串格式转换
#include <map>
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
using namespace std;

const string SPLITE_STR = ",";
const string VALUE_STR = "===";

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
vector<string> splite(string str)
{
    // 返回的字符串数组
    vector<string> res;

    // 空字符串直接返回
    if ("" == str)
        return res;

    // 循环查找符合的字符串
    string tmp_str = str;
    while (true)
    {
        size_t find_begin = tmp_str.find(SPLITE_STR);
        // cout << "tmp_str:" << tmp_str << endl;

        // 第一个就是切割符要跳过,因为前面没有数据
        if (find_begin == 0)
        {
            tmp_str = tmp_str.substr(SPLITE_STR.length());
            continue;
        }

        // 没有找到,跳出循环
        if (find_begin == string::npos)
        {
            // 还有数据说明是最后一个,添加到数组中
            if (tmp_str.length() > 0)
            {
                res.push_back(tmp_str);
            }
            break;
        }

        // 如果是{}内的分割符,说明是对象,要特殊处理
        size_t obj_begin = tmp_str.find("{");
        // cout << "find_begin:" << find_begin << endl;
        // cout << "obj_begin:" << obj_begin << endl;
        if (obj_begin < find_begin)
        {
            // 找到配对的{}终点
            int Left_count = 0;
            int right_count = 0;
            int obj_end = 0;
            for (size_t i = obj_begin; i < tmp_str.length(); i++)
            {
                // 添加{}的数量
                if (tmp_str[i] == "{"[0])
                {
                    Left_count++;
                }
                else if (tmp_str[i] == "}"[0])
                {
                    right_count++;
                }

                // Left_count == right_count, 说明找到结束点了
                if (Left_count == right_count)
                {
                    obj_end = i;
                    break;
                }
            }

            string tmp_data = tmp_str.substr(0, obj_end + 1);
            res.push_back(tmp_data);
            tmp_str = tmp_str.substr(obj_end + 1);
            continue;
        }
        else
        {
            // 找到分隔符
            string tmp_data = tmp_str.substr(0, find_begin);
            res.push_back(tmp_data);
            tmp_str = tmp_str.substr(find_begin + 1);
        }
    }

    return res;
}

StrData get_value(string m_str)
{
    // string str = "a==={b===1,c===abc,d==={e===1,f===asd}}";
    // 要解析的数据输出一下
    cout << endl
         << "m_str:" << m_str << endl;

    // 要返回的数据
    StrData tmp_data;

    // 如果是原子数据, 只有一个VALUE_STR
    if (m_str.find_last_of(VALUE_STR) - VALUE_STR.length() + 1 == m_str.find(VALUE_STR))
    {
        int begin = m_str.find(VALUE_STR);
        string key = m_str.substr(0, begin);
        string value = m_str.substr(begin + VALUE_STR.length());
        cout << "key:" << key << endl;
        cout << "value:" << value << endl
             << endl;

        tmp_data.key = key;
        tmp_data.value = value;
    }
    else // 如果是对象数据
    {
        int begin = m_str.find(VALUE_STR);
        string key = m_str.substr(0, begin);
        string value = m_str.substr(begin + VALUE_STR.length() + 1, m_str.length() - (begin + VALUE_STR.length() + 1) - 1);
        cout << "key:" << key << endl;
        cout << "value:" << value << endl;
        tmp_data.key = key;
        Value obj_data;

        // 获取元素分割的数组
        vector<string> str_arr = splite(value);
        for (size_t i = 0; i < str_arr.size(); i++)
        {
            cout << "str_arr_" << i << ":" << str_arr[i] << endl;
        }

        for (size_t i = 0; i < str_arr.size(); i++)
        {
            StrData tmp_arr_data = get_value(str_arr[i]);
            obj_data[tmp_arr_data.key] = tmp_arr_data;
        }

        tmp_data.obj_data = obj_data;
    }

    return tmp_data;
}

#endif // ANALYSIS_H