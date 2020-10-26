// 3. Longest Substring Without Repeating Characters.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<string>
#include<algorithm>


int lengthOfLongestSubstring(std::string s) {
  
    short c[128];
    memset(c, -1, 256);
    short start = -1, maxLen = 0;
    for (short i = 0; i < s.length(); i++) {
        if (c[s[i]] > -1) start = std::max(start, c[s[i]]);
        c[s[i]] = i;
        if (i - start > maxLen) maxLen = i - start;
    }
    return maxLen;
}



int main()
{
    std::string s{"aaaab" };
    int a =lengthOfLongestSubstring(s);
    return 0;
}
