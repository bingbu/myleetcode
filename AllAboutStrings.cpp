/*
Leetcode String Problems:
344. Reverse String
345. Reverse Vowels of a String
541. Reverse String II
151. Reverse Words in a String
186. Reverse Words in a String II
557. Reverse Words in a String III
3. Longest Substring Without Repeating Characters
28. Find the Index of the First Occurrence in a String
*: replace digits in a string with "number"
459. Repeated Substring Pattern
《编程之法》1.1 字符串的旋转: left and right rotate a string by k steps
796. Rotate String
*: string contains
917. Reverse Only Letters
2810. Faulty Keyboard
3823. Reverse Letters Then Special Characters in a String
1309. Decrypt String from Alphabet to Integer Mapping
《编程之法》1.3 字符串的全排列 (字典序排列)
《编程之法》1.3 输出所有字母字符的所有组合
《编程之法》1.5 回文字符串
《编程之法》1.6 最长回文子字符串
9. Palindrome Number
125. Valid Palindrome
409. Longest Palindrome
131. Palindrome Partitioning
《编程之法》字符串的正则表达式匹配
《编程之法》第一个只出现一次的字符
《编程之法》删除字符串中的指定字符
1763. Longest Nice Substring
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <deque>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    void reverseString(vector<char>& s) {
        int l = 0;
        int r = s.size() - 1;
        while (l < r) {
            // XOR swap without temporary variable
            s[l] ^= s[r];
            s[r] ^= s[l];
            s[l] ^= s[r];
            l++;
            r--;
        }
    }

    string reverseVowels(string s) {
        int l = 0;
        int r = s.size() - 1;
        while (l < r) {
            while (l < r && !isVowel(s[l])) {
                l++;
            }
            while (l < r && !isVowel(s[r])) {
                r--;
            }
            if (l < r) {
                swap(s[l], s[r]);
                l++;
                r--;
            }
        }
        return s;
    }

    string reverseStr(string s, int k) {
        int n = s.size();
        for (int i = 0; i < n; i += 2 * k) {
            int l  = i;
            int r = min(i + k - 1, n - 1);
            while (l < r) {
                swap(s[l], s[r]);
                l++;
                r--;
            }
        }
        return s;
    }

    string reverseWordsOrders(string s) {
        int l = 0;
        int n = s.size();
        int r = n - 1;
        while (l < r) {
            s[l] ^= s[r];
            s[r] ^= s[l];
            s[l] ^= s[r];
            l++;
            r--;
        }

        l = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == ' ' || i == n - 1) {
                r = (s[i] == ' ') ? i - 1 : i;
                while (l < r) {
                    swap(s[l], s[r]);
                    l++;
                    r--;
                }
                l = i + 1;
            }
        }
        // remove leading, trailing and multiple spaces
        int index = 0;
        for (int i = 0;i < n; i++) {
            if (s[i] != ' ' || (i > 0 && s[i - 1] != ' ')) {
                s[index++] = s[i];
            }
        }
        if (index > 0 && s[index - 1] == ' ') index--;
        s.resize(index);

        return s;
    }

    string reverseWords(string s) {
        int n = s.size();
        int l = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == ' ' || i == n - 1) {
                int r = (s[i] == ' ') ? i - 1 : i;
                while (l < r) {
                    swap(s[l], s[r]);
                    l++;
                    r--;
                }
                l = i + 1;
            }
        }
        return s;
    }

    string reverseOnlyLetters(string s) {
        int n = s.size();
        int l = 0;
        int r = n - 1;
        while (l < r) {
            while (l < r && !isalpha(s[l])) {
                l++;
            }
            while (l < r && !isalpha(s[r])) {
                r--;
            }
            if (l < r) {
                swap(s[l], s[r]);
                l++;
                r--;
            }
        }
        return s;
    }

    int strStr(string haystack, string needle) {
        int n = haystack.size();
        int m = needle.size();
        if (m == 0) return 0;
        for (int i = 0; i <= n - m; i++) {
            if (haystack.substr(i, m) == needle) return i;
        }
        return -1;
    }

    /* KMP algorithm: O(n+m) time, O(m) space(完全没有搞懂) */
    int strStrKMP(string haystack, string needle) {
        int n = haystack.size();
        int m = needle.size();
        if (m == 0) return 0;

        // Build prefix table (next array)
        // next[i] = length of longest proper prefix of needle[0..i] that is also a suffix
        vector<int> next(m, 0);
        int len = 0; // length of previous longest prefix suffix
        int i = 1;
        while (i < m) {
            if (needle[i] == needle[len]) {
                next[i++] = ++len;
            } else if (len > 0) {
                len = next[len - 1]; // fall back, don't increment i
            } else {
                next[i++] = 0;
            }
        }

        i = 0;       // index in haystack
        int j = 0;   // index in needle
        while (i < n) {
            if (haystack[i] == needle[j]) {
                i++;
                j++;
                if (j == m) return i - m; // found
            } else if (j > 0) {
                j = next[j - 1]; // fall back using prefix table
            } else {
                i++;
            }
        }
        return -1;
    }

    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        if (n == 0) return 0;

        int maxLength = 1;
        int start = 0;
        unordered_map<char, int> charMap;
        for (int end = 0; end < n; end++) {
            char c = s[end];
            if (charMap.find(c) != charMap.end()) {
                /* check repeated char is in current sliding window */
                if (charMap[c] >= start)
                    start = charMap[c] + 1;
            }
            charMap[c] = end;
            maxLength = max(maxLength, end - start + 1);
        }
        return maxLength;
    }

    /* 递归算法找出最长连续重复字符 */
    int longestOfContinuousRepeatingChars(string s, int start) {
        if (start >= s.size()) return 0;

        int maxLength = 0;
        int length = 1;
        // iterate through the string to find the longest sequence of repeating characters
        while (start + length < s.size() && s[start] == s[start + length]) {
            length++;
        }
        maxLength = max(maxLength, length);
        maxLength = max(maxLength, longestOfContinuousRepeatingChars(s, start + length));

        return maxLength;
    }

    string restoreString(string s, vector<int>& indices) {
        string r(s.size(), ' ');
        for (int i = 0; i < s.size(); i++) {
            r[indices[i]] = s[i];
        }
        return r;
    }

    string restoreString2(string s, vector<int>& indices) {
        for (int i = 0; i < s.size(); i++) {
            while (indices[i] != i) {
                swap(s[i], s[indices[i]]);
                swap(indices[i], indices[indices[i]]);
            }
        }
        return s;
    }

    /*
    If "s" can be constructed by repeating a substring, it definitely appears
    in the middle of "s + s" (without the first and last character)
    */
    bool repeatedSubstringPattern(string s) {
        string ss = s + s;
        //return ss.substr(1, ss.size() - 2).find(s) != string::npos;
        /* if no repeated substring, the found substring will be 2nd s */
        return ss.find(s, 1) != s.size();
    }
    /*
    Replace the digits in the string with "number", for example:
    "a1b2c3" --> "anumbderbnumbdercnumbder"
    "4b5" --> "numbderbnumder"
    */
    string replacedigits(string s) {
        for (int i = 0; i < s.size(); i++) {
            if (isdigit(s[i])) {
                s[i] = 'n';
                s.insert(i + 1, "umbder");
                i += 6;
            }
        }
        return s;
    }

    string leftRotateString(string s, int k) {
        int n = s.size();
        k = k % n;
        reverseString(s, 0, k - 1);
        reverseString(s, k, n - 1);
        reverseString(s, 0, n - 1);

        return s;
    }

    string rightRotateString(string s, int k) {
        int n = s.size();
        k = k % n;
        reverseString(s, 0, n - 1);
        reverseString(s, 0, k - 1);
        reverseString(s, k, n - 1);

        return s;
    }

    bool rotateString(string s, string goal) {
        if (s.size() != goal.size()) return false;
        string ss = s + s;
        return ss.find(goal) != string::npos;
    }

    /*
    Check if string a contains the letters in string b, for example:
    a = "hello world", b = "hoooold" --> true
    */
    bool stringContains(string &a, string &b) {
        unsigned int bitmap = 0;

        for (char c : a) {
            if (isalpha(c)) bitmap |= 1 << (tolower(c) - 'a');
        }

        for (char c : b) {
            if (isalpha(c))
                if (!(bitmap & (1 << (tolower(c) - 'a')))) return false;
        }
        return true;
    }

    string finalString(string s) {
        int n = s.size();
        string result;

        for (int i = 0; i < n; i++) {
            if (s[i] == 'i') {
                // reverse all characters already in result
                reverseString(result, 0, result.size() - 1);
            } else {
                result += s[i];
            }
        }

        return result;
    }

    string finalString_dq(string s) {
        deque<char> dq;
        bool reversed = false;
        for (char c : s) {
            if (c == 'i') {
                reversed = !reversed;  // O(1) flip, no actual reverse
            } else {
                if (reversed) dq.push_front(c);
                else dq.push_back(c);
            }
        }
        string result(dq.begin(), dq.end());
        if (reversed) reverse(result.begin(), result.end());
        return result;
    }

    string reverseByType(string s) {
        int n = s.size() - 1;
        int l = 0;
        int r = n;

        while (l < r) {
            while (!isalpha(s[l]) && l < r) l++;
            while (!isalpha(s[r]) && l < r) r--;
            swap(s[l], s[r]);
            l++;
            r--;
        }

        l = 0;
        r = n;
        while (l < r) {
            while (isalpha(s[l]) && l < r) l++;
            while (isalpha(s[r]) && l < r) r--;
            swap(s[l], s[r]);
            l++;
            r--;
        }
        return s;
    }

    /*
    Characters ('a' to 'i') are represented by ('1' to '9') respectively.
    Characters ('j' to 'z') are represented by ('10#' to '26#') respectively.
    */
    string freqAlphabets(string s) {
        string result;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            if (i + 2 < n && s[i + 2] == '#') {
                int num = (s[i] - '0') * 10 + (s[i + 1] - '0'); // No substring and stoi
                result += (char)('a' + num - 1);
                i += 2;
            } else {
                int num = s[i] - '0';
                result += (char)('a' + num - 1);
            }
        }
        return result;
    }

    /* Output all the permutations of a string via dictionary order */
    void outputPermutations(string s) {
        sort(s.begin(), s.end());
        do {
            cout << s << " ";
        } while (AllPermutations(s));
        cout << endl;
    }

    /* Output all the combinations of letters 'a' to 'c'
    用位掩码枚举字符串的所有子集组合
    "abc" --> "a", "b", "c", "ab", "ac", "bc", "abc"
    */
    void outputCombinations(string s) {
        int n = s.size();
        int total = 1 << n; // 2^n combinations
        for (int i = 1; i <= n; i++) { // group by combination length
            for (int mask = 1; mask < total; mask++) {
                if (__popcnt(mask) != i) continue; // skip if bit count != current length
                string combination;
                for (int j = 0; j < n; j++) {
                    if (mask & (1 << j)) {
                        combination += s[j];
                    }
                }
                cout << combination << " ";
            }
        }
        cout << endl;
    }

    /*
    Implement atoi which converts a string to an integer.
    1. ignore any leading whitespace, '+' or '-'.
    2. convert the following characters until a non-digit is encountered.
    3. check overflow, return INT_MAX or INT_MIN.
     */
    int str2int(string s) {
        int n = s.size();
        int num = 0;
        int sign = 1;
        int i = 0;

        if (n == 0) return 0;
        while (i < n && s[i] == ' ') {
            i++;
        }

        int start = i;
        for (; i < n; i++) {
            char c = s[i];
            if ((c < '0' || c > '9') && !(i == start && (c == '-' || c == '+'))) {
                break;
            }
            if (i == start && c == '-') {
                sign = -1;
                continue;
            }
            if (i == start && c == '+') {
                continue;
            }

            if (num > INT_MAX / 10 || (num == INT_MAX / 10 && (c - '0') > INT_MAX % 10))
                return sign == 1 ? INT_MAX : INT_MIN;

            num = num * 10 + (c - '0');
        }
        return num * sign;
    }

    bool isPalindromeString(string s) {
        int l = 0;
        int n = s.size();
        if (n < 2) return true;

        int r = n - 1;
        while (l < r) {
            if (s[l] != s[r]) return false;
            l++;
            r--;
        }
        return true;
    }

    bool isValidPalindromeString(string s) {
        int l = 0;
        int n = s.size();
        if (n < 2) return true;

        int r = n - 1;
        while (l < r) {
            while (l < r && !isalnum(s[l])) l++;
            while (l < r && !isalnum(s[r])) r--;
            if (tolower(s[l]) != tolower(s[r])) return false;
            l++;
            r--;
        }
        return true;
    }

    bool isPalindromeNumber(int x) {
        long long r = 0; // use long long to avoid overflow when reversing
        int original = x;

        if (x < 0) return false;

        while (x > 0) {
            r = r * 10 + x % 10;
            x /= 10;
        }
        return r == original;
    }

    /* 给定一个字符串，找到其中最长的回文子串的长度 */
    static int expandAroundCenter(const string& s, int l, int r) {
        int n = s.size();
        while (l >= 0 && r < n && s[l] == s[r]) {
            l--;
            r++;
        }
        return r - l - 1;
    }

    int longestPalindromeSubstr(string s) {
        int n = s.size();
        if (n < 2) return n;
        int maxLength = 1;
        for (int i =0; i < n; i++) {
            int len1 = expandAroundCenter(s, i, i);
            int len2 = expandAroundCenter(s, i, i + 1);
            maxLength = max(maxLength, max(len1, len2));
        }
        return maxLength;
    }

    /* move all '*' to the leftmost position*/
    void moveStars2Leftmost(string &s) {
        int n = s.size();
        int index = n - 1;
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] != '*') {
                s[index--] = s[i];
            }
        }
        while (index >= 0) {
            s[index--] = '*';
        }
    }

    /* move all '*' to the rightmost position*/
    void moveStars2Rightmost(string &s) {
        int n = s.size();
        int index = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] != '*') {
                s[index++] = s[i];
            }
        }
        while (index < n) {
            s[index++] = '*';
        }
    }

    /*
    string pattern matching
    wildcard * matches any sequence of characters (including the empty sequence)
    wildcard ? matches any single character
    */
    bool stringRegxMatch(string s, string p) {
        int i, j;
        int starIdx = -1;
        int match = 0;
        int m = s.size();
        int n = p.size();
        for (i = 0, j = 0; i < m; ) {
            if (j < n && (p[j] == '?' || p[j] == s[i])) {
                i++;
                j++;
            } else if (j < n && p[j] == '*') {
                starIdx = j;
                match = i;
                j++;
            } else if (starIdx != -1) {
                j = starIdx + 1;
                match++;
                i = match;
            } else {
                return false;
            }
        }
        while (j < n && p[j] == '*') j++;
        return j == n;
    }

    /*
    409. Longest Palindrome
    Given a string s which consists of lowercase or uppercase letters,
    return the length of the longest palindrome that can be built with those letters.
    Letters are case sensitive, for example, "Aa" is not considered a palindrome
    */
    int longestPalindrome(string s) {
        int count[128] = {0};
        for (char c : s) {
            count[c]++;
        }
        int n = 0;
        for (int i = 0; i < 128; i++) {
            n += count[i] / 2 * 2;
            if (n % 2 == 0 && count[i] % 2 == 1) {
                n++;
            }
        }
        return n;
    }

    /*
    131. Palindrome Partitioning
    Given a string s, partition s such that every substring of the partition is a palindrome.
    Return all possible palindrome partitioning of s.
    */
   vector<vector<string>> partition(string s) {
        int n = s.size();
        vector<vector<string>> result;
        for (int i = 0; i < n; i++) {
            if (isPalindromeString(s.substr(0, i + 1))) {
                vector<string> path = {s.substr(0, i + 1)};
                backtrack(s, i + 1, path, result);
            }
        }
        return result;
   }

   char firstUniqChar(string s) {
        int count[26] = {0};
        for (char c : s) {
            count[c - 'a']++;
        }
        for (char c : s) {
            if (count[c - 'a'] == 1) {
                return c;
            }
        }
        return ' ';
    }

    void removeSpecifiedChars(string &s, string pattern) {
        int index = 0;
        unordered_set<char> toRemove(pattern.begin(), pattern.end());
        for (char c : s) {
            if (toRemove.find(c) == toRemove.end()) {
                s[index++] = c;
            }
        }
        s.resize(index);
    }

    static bool isNiceSubstring(string s) {
        unordered_set<char> chars(s.begin(), s.end());
        for (char c : chars) {
            if (isalpha(c)) {
                if (chars.find(tolower(c)) == chars.end() || chars.find(toupper(c)) == chars.end()) {
                    return false;
                }
            }
        }
        return true;
    }

    string longestNiceSubstringI(string s) {
        int n = s.size();
        if (n < 2) return "";

        int maxLength = 0;
        string longest;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                string substr = s.substr(i, j - i + 1);
                if (isNiceSubstring(substr) && substr.size() > maxLength) {
                    maxLength = substr.size();
                    longest = substr;
                }
            }
        }
        return longest;
    }
    /*
    Divide and conquer approach: O(n^2) time, O(n) space
    分治递归算法：O(n^2)时间，O(n)空间
    */
    string longestNiceSubstring(string s) {
        int n = s.size();
        if (n < 2) return "";
        unordered_set<char> chars(s.begin(), s.end());

        for (int i = 0; i < n; i++) {
            if (chars.count(tolower(s[i])) && chars.count(toupper(s[i]))) {
                continue;
            }
            string left = longestNiceSubstring(s.substr(0, i));
            string right = longestNiceSubstring(s.substr(i + 1));
            return left.size() >= right.size() ? left : right;
        }
        return s; // entire string is nice
    }

    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size();
        int n = text2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }

    /*
    空间优化版：O(min(m,n)) 空间，一维滚动数组 + prev 变量保存左上角
    让较短字符串做内层循环，进一步节省空间
    */
    int longestCommonSubsequenceII(string text1, string text2) {
        if (text1.size() < text2.size()) swap(text1, text2);
        int m = text1.size();
        int n = text2.size();
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= m; i++) {
            int prev = 0; // 等价于 dp[i-1][j-1]
            for (int j = 1; j <= n; j++) {
                int temp = dp[j]; // 保存 dp[i-1][j]，下轮变成 prev
                if (text1[i - 1] == text2[j - 1]) {
                    dp[j] = prev + 1;
                } else {
                    dp[j] = max(dp[j], dp[j - 1]); // max(上方, 左方)
                }
                prev = temp;
            }
        }
        return dp[n];
    }

private:
    void backtrack(string& s, int start, vector<string>& path, vector<vector<string>>& result) {
        if (start == s.size()) {
            result.push_back(path);
            return;
        }
        for (int i = start; i < s.size(); i++) {
            if (isPalindromeString(s.substr(start, i - start + 1))) {
                path.push_back(s.substr(start, i - start + 1));
                backtrack(s, i + 1, path, result);
                path.pop_back();
            }
        }
    }

    bool isVowel(char c) {
        c = tolower(c);
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }

    void reverseString(string &s, int l, int r) {
        while (l < r) {
            swap(s[l], s[r]);
            l++;
            r--;
        }
    }
    bool AllPermutations(string &s) {
        int i;
        int n = s.size();

        for (i = n - 2; i >= 0; i--) {
            if (s[i] < s[i + 1]) {
                break;
            }
        }
        if (i < 0) {
            return false;
        }
        for (int j = n - 1; j > i; j--) {
            if (s[j] > s[i]) {
                swap(s[i], s[j]);
                break;
            }
        }

        reverseString(s, i + 1, n - 1);
        return true;
    }


};

int main() {
    Solution sol;
    vector<char> s = {'h', 'e', 'l', 'l', 'o'};
    sol.reverseString(s);
    for (char c : s) {
        cout << c << " ";
    }
    cout << endl;
    string s2 = "IceCreAm";
    s2 = sol.reverseVowels(s2);
    cout << s2 << endl;

    string s3 = "abcdefg";
    int k = 2;
    s3 = sol.reverseStr(s3, k);
    cout << s3 << endl;

    string s4 = "Let's take   LeetCode contest ";
    s4 = sol.reverseWords(s4);
    cout << s4 << endl;

    string s5 = "a1b2c3";
    s5 = sol.replacedigits(s5);
    cout << s5 << endl;

    string s6 = " the    sky is blue ";
    s6 = sol.reverseWordsOrders(s6);
    cout << s6 << endl;

    string s7 = "abcdefg";
    int k2 = 3;
    s7 = sol.leftRotateString(s7, k2);
    cout << s7 << endl;

    s7 = sol.rightRotateString(s7, k2);
    cout << s7 << endl;

    string s8 = "abcde";
    string goal = "aaaaaeeeebcdddddddddddeeeeeeeeeee";
    bool contains = sol.stringContains(s8, goal);
    cout << "Contains: " << (contains ? "true" : "false") << endl;

    string s9 = "pwwkew";
    cout << "Length of longest substring w/o repeating characters: " << sol.lengthOfLongestSubstring(s9) << endl;

    string haystack = "hello";
    string needle = "ll";
    cout << "Index of first occurrence: " << sol.strStrKMP(haystack, needle) << endl;

     haystack = "aaaaa";
     needle = "bba";
     cout << "Index of first occurrence: " << sol.strStr(haystack, needle) << endl;

     haystack = "mississippi";
     needle = "issip";
     cout << "Index of first occurrence: " << sol.strStrKMP(haystack, needle) << endl;

     haystack = "abc";
     needle = "";
     cout << "Index of first occurrence: " << sol.strStr(haystack, needle) << endl;

    string s10 = "codeleet";
    vector<int> indices = {4, 5, 6, 7, 0, 2, 1, 3};
    string restored = sol.restoreString(s10, indices);
    cout << "Restored string: " << restored << endl;
    restored = sol.restoreString2(s10, indices);
    cout << "Restored string (in-place): " << restored << endl;

    string s11 = "abcabcabcabc";
    string s12 = "aba";
    cout << "Repeated substring pattern: " << (sol.repeatedSubstringPattern(s11) ? "true" : "false") << endl;
    cout << "Repeated substring pattern: " << (sol.repeatedSubstringPattern(s12) ? "true" : "false") << endl;

    string s13 = "a-bC-dEf-ghIj";
    cout << "Reversed only letters: " << sol.reverseOnlyLetters(s13) << endl;

    string s14 =  "poiin  ter";
    string s15 = "string";
    cout << "Final string: " << sol.finalString(s14) << endl;
    cout << "Final string: " << sol.finalString_dq(s15) << endl;

    string s16 = ")ebc#da@f(";
    cout << "Reverse by type: " << sol.reverseByType(s16) << endl;

    string s17 = "10#11#3428#12";
    cout << "Decrypted string: " << sol.freqAlphabets(s17) << endl;

    string s18 = "dabc";
    cout << "All permutations of " << s18 << ":" << endl;
    sol.outputPermutations(s18);

    sol.outputCombinations("abcd");
    string s19 = "+2147483648";
    string s20 = "-12345678901234567890";
    string s21 = "  -123456789";
    cout << "String to int: " << sol.str2int(s19) << endl;
    cout << "String to int: " << sol.str2int(s20) << endl;
    cout << "String to int: " << sol.str2int(s21) << endl;

    string s22 = "$3adffda3$";
    cout << "Is palindrome: " << (sol.isPalindromeString(s22) ? "true" : "false") << endl;

    string s23 = "abccccdd";
    cout << "longest palindrome length: " << sol.longestPalindrome(s23) << endl;

    string s24 = "aab";
    vector<vector<string>> partitions = sol.partition(s24);
    cout << "Palindrome partitions of " << s24 << ":" << endl;
    for (const auto& partition : partitions) {
        for (const auto& str : partition) {
            cout << str << " ";
        }
        cout << endl;
    }

    string s25 = "abccccddddd";
    cout << "Longest palindrome substring length: " << sol.longestPalindromeSubstr(s25) << endl;

    string s26 = "a*b*c*de*";
    sol.moveStars2Leftmost(s26);
    cout << "After moving stars to the leftmost: " << s26 << endl;
    sol.moveStars2Rightmost(s26);
    cout << "After moving stars to the rightmost: " << s26 << endl;

    string s27 = "JohnSmith";
    string pattern = "J*Smi??*";
    cout << "String regex match: " << (sol.stringRegxMatch(s27, pattern) ? "true" : "false") << endl;

    string s28 = "aobaccdeffe";
    cout << "First unique char: " << sol.firstUniqChar(s28) << endl;

    string s29 = "hello world";
    string pattern2 = "lo";
    sol.removeSpecifiedChars(s29, pattern2);
    cout << "After removing specified chars: " << s29 << endl;

    string s30 = "aaaabbbcdddddde";
    cout << "Longest sequence of repeating chars: " << sol.longestOfContinuousRepeatingChars(s30, 0) << endl;

    string s31 ="YazaAay";
    cout << "Longest nice substring: " << sol.longestNiceSubstring(s31) << endl;

    string text1 = "AGGTAB";
    string text2 = "GXTXAYB";
    cout << "Longest common subsequence length: " << sol.longestCommonSubsequence(text1, text2) << endl;

    return 0;
}