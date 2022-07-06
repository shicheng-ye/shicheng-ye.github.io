---
layout: post
title:  "deep dark fantasy"
date:   2022-07-06 11:09:40 +0800
categories: jekyll update
---

### Part 1. Preorder

```c++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        if (!root)  return ans;
        stack<TreeNode*> s;
        s.push(root);
        while (!s.empty()){
            TreeNode* Top = s.top();
            s.pop();
            ans.push_back(Top->val);
            if (Top->right) s.push(Top->right);
            if (Top->left)  s.push(Top->left);
        }
        return ans;
    }
};
```





### Part 2. Inorder

```c++
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        if (!root)   return ans;
        stack<TreeNode*> stk;
        while (!stk.empty() || root){
            while (root){
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            ans.push_back(root->val);
            root = root->right;
        }
        return ans;
    }
};
```





### Step 3. Postorder

```c++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        if (!root)  return ans;
        stack<TreeNode*> stk;
        TreeNode* prev = nullptr;
        stk.push(root);
        while (!stk.empty() || root){
            while (root && root->left){
                stk.push(root->left);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            if (!root->right || root->right == prev){
                ans.push_back(root->val);
                prev = root;
                root = nullptr;
            }
            else {
                stk.push(root);
                stk.push(root->right);
                root = root->right;
            }
        }
        return ans;
    }
};
```





### Step 4. 复杂度分析


- 时间复杂度：`O(n)`，其中 n 是二叉树的节点数。每一个节点恰好被遍历一次。
- 空间复杂度：`O(n)`，为迭代过程中显式栈的开销，平均情况下为 O(logn)，最坏情况下树呈现链状，为 O(n)。
- 时空复杂度同递归模式相同