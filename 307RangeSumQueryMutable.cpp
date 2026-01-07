/*
* Given an integer array nums, handle multiple queries of the following types:
* Update the value of an element in nums.
* Calculate the sum of the elements of nums between indices left and right inclusive where left <= right.
*/
#include <iostream>
#include <vector>
using namespace std;

class NumArray {
private:
    vector<int> tree_;  // Segment tree
    int n_;

    void buildTree(vector<int>& nums, int node, int start, int end) {
        if (start == end) {
            tree_[node] = nums[start];
        } else {
            int mid = start + (end - start) / 2;
            int leftChild = 2 * node + 1;
            int rightChild = 2 * node + 2;
            buildTree(nums, leftChild, start, mid);
            buildTree(nums, rightChild, mid + 1, end);
            tree_[node] = tree_[leftChild] + tree_[rightChild];
        }
    }

    void updateTree(int node, int start, int end, int index, int val) {
        if (start == end) {
            tree_[node] = val;
        } else {
            int mid = start + (end - start) / 2;
            int leftChild = 2 * node + 1;
            int rightChild = 2 * node + 2;
            if (index <= mid) {
                updateTree(leftChild, start, mid, index, val);
            } else {
                updateTree(rightChild, mid + 1, end, index, val);
            }
            tree_[node] = tree_[leftChild] + tree_[rightChild];
        }
    }

    int queryTree(int node, int start, int end, int left, int right) {
        if (left > end || right < start) {
            return 0;  // Out of range
        }
        if (left <= start && end <= right) {
            return tree_[node];  // Fully within range
        }
        int mid = start + (end - start) / 2;
        int leftChild = 2 * node + 1;
        int rightChild = 2 * node + 2;
        int leftSum = queryTree(leftChild, start, mid, left, right);
        int rightSum = queryTree(rightChild, mid + 1, end, left, right);
        return leftSum + rightSum;
    }

public:
    NumArray(vector<int>& nums) {
        n_ = nums.size();
        tree_.resize(4 * n_);  // Segment tree needs at most 4n space
        buildTree(nums, 0, 0, n_ - 1);
    }
    
    void update(int index, int val) {
        updateTree(0, 0, n_ - 1, index, val);
    }
    
    int sumRange(int left, int right) {
        return queryTree(0, 0, n_ - 1, left, right);
    }
};

class NumArray2 {
private:
    vector<int> nums_;
    int n_;
    int sum_;
public:
    NumArray2(vector<int>& nums) {
        nums_ = nums;
        n_ = nums.size();
        sum_ = 0;
        for (const int& num : nums_) {  
            sum_ += num;
        }
    }
    
    void update(int index, int val) {
        if (index < 0 || index >= n_) 
            return;
        sum_ = sum_ - nums_[index] + val;
        nums_[index] = val;
    }
    
    int sumRange(int left, int right) {
        int sum = 0;
        if (left < 0 || right >= n_ || left > right) 
            return sum;
        if (left == 0 && right == n_ - 1) 
            return sum_;
        for (int i = left; i <= right; ++i) {
            sum += nums_[i];
        }
        return sum;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
int main() {
    vector<int> nums = {1, 3, 5};
    NumArray* obj = nullptr;
    obj = new NumArray(nums);
    cout << "Sum of range (0, 2): " << obj->sumRange(0, 2) << endl;  // Expected: 9
    obj->update(1, 2);
    cout << "Sum of range (0, 2) after update: " << obj->sumRange(0, 2) << endl;  // Expected: 8
    delete obj;
    
    cout << "-=======================-" << endl;

    NumArray2* obj2 = nullptr;
    obj2 = new NumArray2(nums);
    cout << "Sum of range (0, 2): " << obj2->sumRange(0, 2) << endl;  // Expected: 9
    obj2->update(1, 2);
    cout << "Sum of range (0, 2) after update: " << obj2->sumRange(0, 2) << endl;  // Expected: 8
    delete obj2;

}