/**
 * @brief 102. Binary Tree Level Order Traversal
 *
 */
 * Definition for a binary tree node.
 * struct TreeNode
 {
     *int val;
     *TreeNode *left;
     *TreeNode *right;
     *TreeNode() : val(0), left(nullptr), right(nullptr){} * TreeNode(int x) : val(x), left(nullptr), right(nullptr){} * TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right){}
                                                                                                                                                                                                    *
 };
 * /
     //#include <queue>
     class LevelOrderTraversal
 {
 public:
     vector<vector<int>> ans;
     vector<vector<int>> levelOrder(TreeNode *root)
     {
         if (root == NULL)
         {
             return ans;
         }
         queue<TreeNode *> chil;
         chil.push(root);

         while (!chil.empty())
         {
             vector<int> currlevel;
             int size = chil.size();
             for (int i = 0; i < size; i++)
             {
                 TreeNode *curr = chil.front(); // take the front node from queue (all children) and pop them
                 chil.pop();
                 currlevel.push_back(curr->val); // add this node to current level answers
                 // push this level's children into queue:
                 if (curr->left != NULL)
                     chil.push(curr->left);
                 if (curr->right != NULL)
                     chil.push(curr->right);
             }
             // we finished this level so push it onto the main vector
             ans.push_back(currlevel);
         }
         return ans;
     }
 };