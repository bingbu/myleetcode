/*
* 110. Balanced Binary Tree
* Given a binary tree, determine if it is height-balanced.
* A height-balanced binary tree is defined as:
* a binary tree in which the depth of the two subtrees of every node never differs by more than one.
*/

#include <iostream>
#include <algorithm>
using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return checkBalance(root) != -1;
    }
private:
    // return height if balanced, -1 if not
    int checkBalance(TreeNode* node) {
        if (node == nullptr) return 0;
        
        int left = checkBalance(node->left);
        if (left == -1) 
            return -1;
        
        int right = checkBalance(node->right);
        if (right == -1) 
            return -1;
        
        if (abs(left - right) > 1)
            return -1;

        return max(left, right) + 1;
    }
};


int main() {
    Solution sol;

    // Test case 1: Balanced tree
    // root1 = [3,9,20,null,null,15,7]
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);
    
    cout << "Test case 1: " << (sol.isBalanced(root1) ? "Balanced" : "Not Balanced") << endl;

    // Test case 2: Unbalanced tree
    // root2 = [1,2,2,3,3,null,null,4,4]
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(2);
    root2->left->left = new TreeNode(3);
    root2->left->right = new TreeNode(3);
    root2->left->left->left = new TreeNode(4);
    root2->left->left->right = new TreeNode(4);
    
    cout << "Test case 2: " << (sol.isBalanced(root2) ? "Balanced" : "Not Balanced") << endl;

    return 0;
}