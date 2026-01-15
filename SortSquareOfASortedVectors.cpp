/*
双指针算法是一种高效的数据结构遍历技巧，利用两个指针（通常是索引或地址）在数组或链表上协同移动，
以简化问题、减少时间复杂度（常从 \(O(N^{2})\) 降至 \(O(N)\)）。
主要分为快慢指针（同向移动，如找链表中间点/环）和对撞指针/左右指针（相向移动，如在有序数组中查找和）两大类，
常用于区间操作、排序优化、链表环检测等场景。 
核心思想与类型 
核心思想：
用两个指针（left, right / slow, fast）同时遍历数据结构，协同完成任务，避免暴力搜索的多次遍历。
快慢指针 (快指针/慢指针)：
    特点：同向移动，快指针比慢指针移动快一倍。
    用途：检测链表环、查找链表中间节点。
对撞指针 (左右指针/首尾指针)：
    特点：通常在有序数组中，一个从头开始，一个从尾开始，相向而行。
    用途：查找和、回文串判断、区间查找。
滑动窗口：
    特点：指向同一序列，同向移动，两个指针之间形成一个“窗口”。
    用途：解决区间问题，如最大子数组和。
应用场景示例:
    有序数组中找两数之和：排序后，左右指针相向移动，判断和与目标值的大小关系，调整指针。
    链表判环：fast 指针每次走两步，slow 指针走一步，若相遇则有环。
    合并两个有序数组：归并排序中，两个指针分别指向两个数组的当前元素，比较后放入结果数组。
    移除数组中的重复元素：慢指针记录不重复元素的位置，快指针遍历。
    最大子数组和：滑动窗口调整窗口大小，计算当前窗口和，更新最大值。
总结:
    双指针是算法竞赛和面试中非常重要的技巧，理解其“同向/相向、快/慢、剪枝优化”的特点，
    能有效解决许多数组和链表问题。 
*/

/* Given a sorted integer vectors, re-sort their squares of all elements */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> sortedSquares(const vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);
        int left = 0, right = n - 1;
        int pos = n - 1;

        while (left <= right) {
            int leftSquare = nums[left] * nums[left];
            int rightSquare = nums[right] * nums[right];
            
            if (leftSquare > rightSquare) {
                result[pos] = leftSquare;
                left++;
            } else {
                result[pos] = rightSquare;
                right--;
            }
            pos--;
        }

        return result;
    }
};

// test cases
int main() {
    Solution sol;
    vector<int> test1 = {-4, -1, 0, 3, 10};
    vector<int> result1 = sol.sortedSquares(test1);
    cout << "Test 1: ";
    for (int num : result1) {
        cout << num << " ";
    }
    cout << endl;  // Expected: [0, 1, 9, 16, 100]

    vector<int> test2 = {-7, -3, 2, 3, 11};
    vector<int> result2 = sol.sortedSquares(test2);
    cout << "Test 2: ";
    for (int num : result2) {
        cout << num << " ";
    }
    cout << endl;  // Expected: [4, 9, 9, 49, 121]

    vector<int> test3 = {-5, -3, -2, -1};
    vector<int> result3 = sol.sortedSquares(test3);
    cout << "Test 3: ";
    for (int num : result3) {
        cout << num << " ";
    }
    cout << endl;  // Expected: [1, 4, 9, 25]

    return 0;
}
