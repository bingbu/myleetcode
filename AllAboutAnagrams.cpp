/*
242. Valid Anagram
383. Ransom Note
49. Group Anagrams
438. Find All Anagrams in a String
*/

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

class Solution {
    // 自定义 hash 函数，用于 array<int, 26> 作为 unordered_map 的 key
    struct ArrayHash {
        size_t operator()(const array<int, 26>& arr) const {
            size_t hash = 0;
            for (int i : arr) {
                hash ^= std::hash<int>()(i) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            }
            return hash;
        }
    };
public:
    bool isAnagram1(string s, string t) {
        unordered_multiset<char> charSet;
            for (char c : s) {
                charSet.insert(c);
            }

            for (char c : t) {
                if (charSet.find(c) == charSet.end()) {
                    return false;
                }
                charSet.erase(charSet.find(c));
            }

            return charSet.empty();
    }

    bool isAnagram2(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }

        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }

    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;

        int count[26] = {0};
        for (int i = 0; i < s.length(); i++) {
            count[s[i] - 'a']++;
            count[t[i] - 'a']--;
        }

        for (int c : count) {
            if (c != 0) return false;
        }
        return true;
    }

    bool canConstruct(string ransomNote, string magazine) {
        int count[26] = {0};
        for (char c : magazine) {
            count[c - 'a']++;
        }

        for (char c : ransomNote) {
            if (count[c - 'a']-- <= 0) {
                return false;
            }
        }
        return true;
    }
    // 笨办法
    vector<vector<string>> groupAnagrams1(vector<string>& strs) {
        vector<vector<string>> result;
        for (string& s : strs) {
            string sortedS = s;
            sort(sortedS.begin(), sortedS.end());
            bool found = false;
            for (auto& group : result) {
                string sortedGroupFirst = group[0];
                sort(sortedGroupFirst.begin(), sortedGroupFirst.end());
                if (sortedS == sortedGroupFirst) {
                    group.push_back(s);
                    found = true;
                    break;
                }
            }
            if (!found) {
                result.push_back({s});
            }
        }
        return result;
    }
    // 哈希表法
    vector<vector<string>> groupAnagrams2(vector<string>& strs) {
        unordered_map<string, vector<string>> anagramMap;
        for (string& s : strs) {
            string sortedS = s;
            sort(sortedS.begin(), sortedS.end());
            anagramMap[sortedS].push_back(s);
        }

        vector<vector<string>> result;
        for (auto& pair : anagramMap) {
            result.push_back(pair.second);
        }
        return result;
    }
    // 计数法
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> anagramMap;
        // use char count as key instead of sorting
        for (string& s : strs) {
            int count[26] = {0};
            for (char c : s) {
                count[c - 'a']++;
            }
            string key;
            for (int i = 0; i < 26; i++) {
                key += '#';  // delimiter to avoid ambiguity
                key += to_string(count[i]);
            }
            cout << key << endl;
            anagramMap[key].push_back(s);
        }

        vector<vector<string>> result;
        for (auto& pair : anagramMap) {
            result.push_back(pair.second);
        }
        return result;
    }

    // 质数乘积法（注意：大字符串可能溢出，不推荐使用）
    vector<vector<string>> groupAnagramsPrime(vector<string>& strs) {
        unordered_map<unsigned long long, vector<string>> anagramMap;
        const int primeNumbers[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                                       31, 37, 41, 43, 47, 53, 59, 61,  67, 71, 73, 79, 83, 89, 97, 101};
        for (string& s : strs) {
            unsigned long long key = 1;
            for (char c : s) {
                key *= primeNumbers[c - 'a'];
            }
            anagramMap[key].push_back(s);
        }

        vector<vector<string>> result;
        for (auto& pair : anagramMap) {
            result.push_back(pair.second);
        }
        return result;
    }

    // 最优解：使用 array<int, 26> 作为 key,最骚操作
    vector<vector<string>> groupAnagramsOptimal(vector<string>& strs) {
        unordered_map<array<int, 26>, vector<string>, ArrayHash> anagramMap;

        for (const string& s : strs) {
            array<int, 26> count = {0};
            for (char c : s) {
                count[c - 'a']++;
            }
            anagramMap[count].push_back(s);
        }

        vector<vector<string>> result;
        result.reserve(anagramMap.size());
        for (auto& pair : anagramMap) {
            result.push_back(std::move(pair.second));
        }
        return result;
    }

    // 滑动窗口+计数法+优化
    vector<int> findAnagrams(string s, string p) {
        if (s.length() < p.length()) return {};

        vector<int> result;
        int sublen = p.length();
        int pCount[26] = {0};
        int sCount[26] = {0};
        for (char c : p) {
            pCount[c - 'a']++;
        }

        for (int i = 0; i < sublen; i++) {
            sCount[s[i] - 'a']++;
        }
        if (equal(begin(pCount), end(pCount), begin(sCount))) {
            result.push_back(0);
        }
        // sliding window
        for (int i = 1; i < s.length() - sublen + 1; i++) {
            sCount[s[i + sublen - 1] - 'a']++;
            sCount[s[i - 1] - 'a']--;
            if (equal(begin(pCount), end(pCount), begin(sCount))) {
                result.push_back(i);
            }
        }
        return result;
    }
};

int main() {
    Solution sol;
    string s = "anagram";
    string t = "nagaram";

    string s2 = "aaaaadfc";
    string t2 = "adfc";

    if (sol.isAnagram(s, t)) {
        cout << s << " and " << t << " are anagrams." << endl;
    } else {
        cout << s << " and " << t << " are not anagrams." << endl;
    }

    if (sol.isAnagram(s2, t2)) {
        cout << s2 << " and " << t2 << " are anagrams." << endl;
    } else {
        cout << s2 << " and " << t2 << " are not anagrams." << endl;
    }

    string ransomNote = "aa";
    string magazine = "ab";
    string magazine2 = "aaab";
    if (sol.canConstruct(ransomNote, magazine)) {
        cout << "Ransom note can be constructed from magazine." << endl;
    } else {
        cout << "Ransom note cannot be constructed from magazine." << endl;
    }
    if (sol.canConstruct(ransomNote, magazine2)) {
        cout << "Ransom note can be constructed from magazine2." << endl;
    } else {
        cout << "Ransom note cannot be constructed from magazine2." << endl;
    }

    string strsArr[] = {"xyzzzzzzzzzzzz", "zzzzzzzzzzzzyx", "eat", "tea", "tan", "ate", "nat", "bat",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"};
    vector<string> strs(strsArr, strsArr + sizeof(strsArr) / sizeof(strsArr[0]));
    vector<vector<string>> groupedAnagrams = sol.groupAnagramsOptimal(strs);
    cout << "Grouped Anagrams:" << endl;
    for (const auto& group : groupedAnagrams) {
        for (const auto& str : group) {
            cout << str << " ";
        }
        cout << endl;
    }

    string s3 = "aaaaaaaabcabccbaebabacd";
    string p3 = "aaa";
    vector<int> anagramIndices = sol.findAnagrams(s3, p3);
    cout << "Anagram indices of \"" << p3 << "\" in \"" << s3 << "\": ";
    for (int index : anagramIndices) {
        cout << index << " ";
    }
    cout << endl;

    return 0;
}

