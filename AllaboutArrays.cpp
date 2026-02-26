/*
349. Intersection of Two Arrays
350. Intersection of Two Arrays II
1. Two Sum
15. 3Sum
16. 3Sum Closest
18. 4Sum
349. Intersection of Two Arrays
350. Intersection of Two Arrays II
454. 4Sum II
《编程之法》2.1 寻找最小的k个数
《编程之法》2.1 三元组的数量
《编程之法》2.2 寻找树中和为某值的路径
53. Maximum Subarray
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;
class Solution {
public:
    /*
    Given two integer arrays nums1 and nums2, return an array of their intersection.
    Each element in the result must be unique and you may return the result in any order.
    */
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> s;
        vector<int> result;
        for (int num : nums1) {
            s.insert(num);
        }
        for (int num : nums2) {
            if (s.count(num) > 0) {
                result.push_back(num);
                s.erase(num);
            }
        }
        return result;
    }

    vector<int> intersectionII(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> count;
        for (int num : nums1) {
            count[num]++;
        }
        vector<int> result;
        for (int num : nums2) {
            if (count[num] > 0) {
                result.push_back(num);
                count[num]--;
            }
        }
        return result;
    }

    /* optimal solution for Intersection of Two Arrays II using Double Pointers */
    vector<int> intersectionII_DoublePointers(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        vector<int> result;

        int i = 0, j = 0;
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] < nums2[j]) {
                i++;
            } else if (nums1[i] > nums2[j]) {
                j++;
            } else {
                result.push_back(nums1[i]);
                i++;
                j++;
            }
        }
        return result;
    }

    /* Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.*/
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++) {
            int c = target - nums[i];
            if (map.find(c) != map.end()) {
                return {map[c], i};
            }
            map[nums[i]] = i;
        }
        return {};
    }

    vector<vector<int>> twoSumII(vector<int>& nums, int target) {
        vector<vector<int>> res;
        int n = nums.size() - 1;
        int l = 0;
        int r = n;
        sort(nums.begin(), nums.end());

        while (l < r) {
            while((l < r) && nums[l] + nums[r] < target) l++;
            while((l < r) && nums[l] + nums[r] > target) r--;
            if (nums[l] + nums[r] == target) {
                res.push_back({nums[l], nums[r]});
                l++;
                r--;
            }
        }
        return res;
    }

    /*
    Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that:
    i != j != k and nums[i] + nums[j] + nums[k] == 0.
    */
   vector<vector<int>> threeSum(vector<int>& nums, int sum = 0) {
        vector<vector<int>> result;
        size_t n = nums.size();

        if (n < 3) return result;
        sort(nums.begin(), nums.end());

        if (nums[0] > sum) return result;
        if (nums[n - 1] + nums[n - 2] + nums[n - 3] < sum) return result;

        for (int i = 0; i < n - 2; i++) {
            if (nums[i] + nums[i+1] + nums[i+2] > sum) break;
            if (nums[i] + nums[n-2] + nums[n-1] < sum) continue;
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int left = i + 1, right = n - 1;
            while (left < right) {
                int s3 = nums[i] + nums[left] + nums[right];
                if (s3 == sum) {
                    result.push_back({nums[i], nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    left++;
                    right--;
                } else if (s3 < sum) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        return result;
    }

    /*
    Given an integer array nums of length n and an integer target, find three integers at distinct indices in nums such that:
    the sum is closest to target. Return the sum of the three integers.
    */
    int threeSumClosest(vector<int>& nums, int target) {
        size_t n = nums.size();
        if (n < 3) return 0;
        sort(nums.begin(), nums.end());
        int closestSum = nums[0] + nums[1] + nums[2];
        int gap = abs(closestSum - target);
        if (gap == 0) return closestSum;

        for (int i = 0; i < n - 2; i++) {
            // pruning
            int s = nums[i] + nums[i+1] + nums[i+2];
            if (s > target) {
                if (s - target < gap) {
                    gap = s - target;
                    closestSum = s;
                }
                break;
            }
            // pruning
            s = nums[i] + nums[n-2] + nums[n-1];
            if (s < target) {
                if (target - s < gap) {
                    gap = target - s;
                    closestSum = s;
                }
                continue;
            }

            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int left = i + 1, right = n - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum == target) return sum;

                if (abs(sum - target) < gap) {
                    gap = abs(sum - target);
                    closestSum = sum;
                }
                // No need to skip duplicates
                if (sum < target)
                    left++;
                else
                    right--;
            }
        }
        return closestSum;
    }

    /*
    Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]].
    fourSum optimized with pruning + long long to prevent overflow
    */
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        if (n < 4) return result;

        for (int i = 0; i < n - 3; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            // prune: min possible sum too large max possible sum too small
            if ((long long)nums[i] + nums[i+1] + nums[i+2] + nums[i+3] > target) break;
            if ((long long)nums[i] + nums[n-3] + nums[n-2] + nums[n-1] < target) continue;

            for (int j = i + 1; j < n - 2; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;

                // prune: min possible sum too large or max possible sum too small
                if ((long long)nums[i] + nums[j] + nums[j+1] + nums[j+2] > target) break;
                if ((long long)nums[i] + nums[j] + nums[n-2] + nums[n-1] < target) continue;

                int left = j + 1, right = n - 1;
                while (left < right) {
                    long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];
                    if (sum == target) {
                        result.push_back({nums[i], nums[j], nums[left], nums[right]});
                        // skip duplicates for the third and fourth number
                        while (left < right && nums[left] == nums[left + 1]) left++;
                        while (left < right && nums[right] == nums[right - 1]) right--;
                        left++;
                        right--;
                    } else if (sum < target) {
                        left++;
                    } else {
                        right--;
                    }
                }
            }
        }
        return result;
    }

    /* Given four integer arrays nums1, nums2, nums3, and nums4 all of length n, return the number of tuples (i, j, k, l) such that:
     nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0.
     */
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4, int sum = 0) {
        int count = 0;
        unordered_map<int, int> sumCount;

        for (int a : nums1) {
            for (int b : nums2) {
                sumCount[a + b]++;
            }
        }
        for (int c : nums3) {
            for (int d : nums4) {
                int target = sum - (c + d);
                auto it = sumCount.find(target);
                if (it != sumCount.end()) {
                    count += it->second;
                }
            }
        }
        return count;
    }

    /* 输入两个整数sum 和 n, 要求从数列1，2，3，4, ..., n中随意取若干个数，使得它们的和为sum，返回所有可能的组合
     * 使用迭代法实现
    */
    vector<vector<int>> combinationSum(int sum, int n) {
        if (sum == 0) return {{}};
        // 递归退出条件：如果 n <= 0，说明没有合法组合，返回空数组
        if (n <= 0) return {};
        if (sum > n * (n + 1) / 2) return {};
        vector<vector<int>> result;

        // 不选 n：从 1~(n-1) 中凑 sum
        for (auto& comb : combinationSum(sum, n - 1)) {
            result.push_back(comb);
        }
        // 选 n：从 1~(n-1) 中凑 sum-n，再把 n 加上
        for (auto comb : combinationSum(sum - n, n - 1)) {
            comb.push_back(n);
            result.push_back(comb);
        }
        return result;
    }

    /*
    Given an array arr and an integer k, return the k smallest numbers in the array.
    */
   /*
   First solution using insertion sort idea, time complexity O(n*k), space complexity O(k)
   输出的结果是排序的，从大到小
    */
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        int n = arr.size();
        if (k <= 0) return {};
        if (k > n) return arr;
        vector<int> r(k);
        int kmax = arr[0];
        for (int i = 0; i < k; i++) {
            r[i] = arr[i];
            kmax = max(kmax, arr[i]);
        }
        // swapping to sort the first k elements in descending order, so that the largest of the k smallest is at r[0]
        for (int i = 1; i < k; i++) {
            int j = i;
            while (j > 0 && r[j] > r[j - 1]) {
                swap(r[j], r[j - 1]);
                j--;
            }
        }

        for (int i = k; i < n; i++) {
            if (arr[i] < kmax) {
                r[0] = arr[i];
                // swap down to maintain descending order
                int j = 0;
                while (j < k - 1 && r[j] < r[j + 1]) {
                    swap(r[j], r[j + 1]);
                    j++;
                }
            }
        }
        return r;
    }

    /*
    optimal solution using a max heap of size k
    输出的结果也是排序的，时间复杂度 O(n log k)，空间复杂度 O(k)
     */
    vector<int> getLeastNumbers_heap(vector<int>& arr, int k) {
        if (k <= 0) return {};
        if (k >= arr.size()) return arr;
        priority_queue<int> maxHeap; // 大顶堆
        for (int num : arr) {
            if (maxHeap.size() < k) {
                maxHeap.push(num);
            } else if (num < maxHeap.top()) {
                maxHeap.pop();
                maxHeap.push(num);
            }
        }
        vector<int> r;
        while (!maxHeap.empty()) {
            r.push_back(maxHeap.top());
            maxHeap.pop();
        }
        return r;
    }
    /*
    quick select solution, time complexity O(n) on average, space complexity O(1)
    输出的结果是排序的，从小到大
    */
    vector<int> getLeastNumbers_quickSelect(vector<int>& arr, int k) {
        if (k <= 0) return {};
        if (k >= arr.size()) return arr;
        nth_element(arr.begin(), arr.begin() + k, arr.end());
        return vector<int>(arr.begin(), arr.begin() + k);
    }

    /* 给定一个数列和m个三元组表示的查询，对于每个查询(i, j, k), 输出数列第i个到第j个的升序排列中的第k个元素 */
    vector<int> queryKthSmallest(vector<int>& arr, vector<vector<int>>& queries) {
        vector<int> result;
        for (const auto& q : queries) {
            int i = q[0], j = q[1], k = q[2];
            vector<int> sub(arr.begin() + i, arr.begin() + j + 1);
            nth_element(sub.begin(), sub.begin() + k - 1, sub.end());
            result.push_back(sub[k - 1]);
        }
        return result;
    }

    int partition(vector<int>& arr, int left, int right) {
        int pivot = arr[left];
        int i = left + 1;
        for (int j = left + 1; j <= right; j++) {
            if (arr[j] > pivot) {
                swap(arr[j], arr[i]);
                i++;
            }
        }
        swap(arr[left], arr[i - 1]);
        return i - 1;
    }

    void quickSelect(vector<int>& arr, int left, int right, int k) {
        if (left >= right) return;
        int pivot = partition(arr, left, right);
        if (pivot == k) {
            return;
        } else if (pivot < k) {
            quickSelect(arr, pivot + 1, right, k);
        } else {
            quickSelect(arr, left, pivot - 1, k);
        }
    }

    vector<int> getLargestNumbers_quickSelect(vector<int>& arr, int k) {
        if (k <= 0) return {};
        if (k >= arr.size()) return arr;
        nth_element(arr.begin(), arr.begin() + k, arr.end(), greater<int>());
        return vector<int>(arr.begin(), arr.begin() + k);
    }

    vector<int> getLargestNumbers_quickSelectII(vector<int>& arr, int k) {
        if (k <= 0) return {};
        if (k >= arr.size()) return arr;
        quickSelect(arr, 0, arr.size() - 1, k);
        return vector<int>(arr.begin(), arr.begin() + k);
    }

    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int result = nums[0];
        int sum = 0;

        for (int i = 0; i < n; i++) {
            if (sum < 0) sum = nums[i];
            else sum += nums[i];
            result = max(result, sum);
        }
        return result;
    }
};

int main() {
    Solution sol;
    vector<int> nums1 = {1, 2, 2, 1};
    vector<int> nums2 = {2, 2};
    vector<int> nums3 = {4, 9, 5, 4};
    vector<int> nums4 = {9, 4, 9, 8, 4, 4, 4, 4, 4, 4};
    vector<int> result = sol.intersection(nums1, nums2);
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;
    vector<int> result2 = sol.intersection(nums3, nums4);
    cout << "Intersection of nums3 and nums4: " << endl;
    for (int num : result2) {
        cout << num << " ";
    }
    cout << endl;
    vector<int> result3 = sol.intersectionII(nums1, nums2);
    cout << "Intersection II of nums1 and nums2: " << endl;
    for (int num : result3) {
        cout << num << " ";
    }
    cout << endl;
    vector<int> result4 = sol.intersectionII(nums3, nums4);
    cout << "Intersection II of nums3 and nums4: " << endl;
    for (int num : result4) {
        cout << num << " ";
    }
    cout << endl;
    vector<int> result5 = sol.intersectionII_DoublePointers(nums1, nums2);
    cout << "Intersection II with Double Pointers of nums1 and nums2: " << endl;
    for (int num : result5) {
        cout << num << " ";
    }
    cout << endl;
    vector<int> result6 = sol.intersectionII_DoublePointers(nums3, nums4);
    cout << "Intersection II with Double Pointers of nums3 and nums4: " << endl;
    for (int num : result6) {
        cout << num << " ";
    }
    cout << endl;
    vector<int> nums7 = {2, 3, 7, 8, 11, 15, 6, 1, 4, 5, 9, 0};
    int target = 9;
    vector<int> result7 = sol.twoSum(nums7, target);
    cout << "Two Sum indices: " << endl;
    for (int num : result7) {
        cout << num << " ";
    }
    cout << endl;

    vector<vector<int>> res = sol.twoSumII(nums7, target);
    cout << "Two Sum II indices: " << endl;
    for (const auto& pair : res) {
        cout << "[ ";
        for (int num : pair) {
            cout << num << " ";
        }
        cout << "],";
    }
    cout << endl;

    vector<int> nums9 = {-1, 0, 1, 2, -1, -4};
    vector<vector<int>> result9 = sol.threeSum(nums9);
    cout << "Three Sum triplets: " << endl;
    for (const auto& triplet : result9) {
        for (int num : triplet) {
            cout << num << " ";
        }
        cout << endl;
    }

    vector<int> nums14 = {-1, 2, 1, -4};
    int target3 = 1;
    int closestSum = sol.threeSumClosest(nums14, target3);
    cout << "Three Sum Closest: " << closestSum << endl;

    vector<int> nums8 = {1, 0, -1, 0, -2, -2, 0, 2};
    int target2 = 0;
    vector<vector<int>> result8 = sol.fourSum(nums8, target2);
    cout << "Four Sum quadruplets: " << endl;
    for (const auto& quad : result8) {
        for (int num : quad) {
            cout << num << " ";
        }
        cout << endl;
    }

    vector<int> nums10 = {1, 2};
    vector<int> nums11 = {-2, -1};
    vector<int> nums12 = {-1, 2};
    vector<int> nums13 = {0, 2};
    int count = sol.fourSumCount(nums10, nums11, nums12, nums13, 2);
    cout << "fourSumCount: " << count << endl;

    vector<int> arr = {1, 3, 2, 5, 5, 4};
    int k = 3;
    vector<int> leastNumbers = sol.getLeastNumbers(arr, k);
    cout << "Least " << k << " numbers: " << endl;
    for (int num : leastNumbers) {
        cout << num << " ";
    }
    cout << endl;

    vector<int> leastNumbers2 = sol.getLeastNumbers_heap(arr, k);
    cout << "Least " << k << " numbers using heap: " << endl;
    for (int num : leastNumbers2) {
        cout << num << " ";
    }

    cout << endl;
    vector<int> leastNumbers3 = sol.getLeastNumbers_quickSelect(arr, k);
    cout << "Least " << k << " numbers using quick select: " << endl;
    for (int num : leastNumbers3) {
        cout << num << " ";
    }
    cout << endl;
    vector<int> arr2 = {9, 1, 3, 2, 7, 8, 5, 5, 4};
    vector<int> largestNumbers = sol.getLargestNumbers_quickSelectII(arr2, 2);
    cout << "Largest 2 numbers using quick select II: " << endl;
    for (int num : largestNumbers) {
        cout << num << " ";
    }
    cout << endl;

    vector<int> arr3 = {3, 1, 2, 5, 4};
    vector<vector<int>> queries = {{0, 4, 3}, {1, 3, 2}, {0, 2, 1}};
    vector<int> queryResults = sol.queryKthSmallest(arr3, queries);
    cout << "Query Kth Smallest results: " << endl;
    for (int num : queryResults) {
        cout << num << " ";
    }
    cout << endl;

    // Test combinationSum: 从 1~n 中选若干数使和为 sum
    vector<vector<int>> combResults = sol.combinationSum(10, 5);
    cout << "combinationSum(10, 5): " << endl;
    for (const auto& comb : combResults) {
        cout << "[ ";
        for (int num : comb) {
            cout << num << " ";
        }
        cout << "]" << endl;
    }
    vector<int> nums15 = {3, 1, -2, 3, 10, -4, 7, 2, -5};
    int maxSum = sol.maxSubArray(nums15);
    cout << "Maximum Subarray Sum: " << maxSum << endl;

    return 0;
}