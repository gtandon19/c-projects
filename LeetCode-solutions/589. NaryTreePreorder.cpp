/**
 * @brief 589. N-ary Tree Preorder Traversal
 *
 */
// Definition for a Node.
class Node
{
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, vector<Node *> _children)
    {
        val = _val;
        children = _children;
    }
};
* /

    class NaryTreePreorder
{
public:
    vector<int> ans;
    vector<int> preorder(Node *root)
    {
        if (root == NULL)
            return ans;
        ans.push_back(root->val);
        for (int i = 0; i < root->children.size(); i++)
        {
            ans = preorder(root->children[i]);
        }
        return ans;
    }
};
