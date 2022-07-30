/**
 * @brief 235. Lowest Common Ancestor of a Binary Search Tree
 * 
 */
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class LCAofBST {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == p || root == q || (p->val < root->val  && q->val > root->val) || (p->val > root->val  && q->val < root->val))
            return root;
        TreeNode* curr = root;
        if (p->val < root->val)
            curr = lowestCommonAncestor(root->left, p, q);
        else 
            curr = lowestCommonAncestor(root->right, p, q);
        return curr;
    }
};