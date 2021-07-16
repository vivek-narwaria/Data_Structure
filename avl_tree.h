// Compilation g++ -o avl_tree -std=c++11 avl_tree.cpp -I.

#include <iostream>
#include <string>

typedef enum
{
    PRE_OREDER,
    POST_ORDER,
    IN_ORDER,
    LEVEL_ORDER,
    PRETTY_PRINT
} traversal;

// AVL Tree Node
typedef struct TreeNode
{
    int data;
    int height;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// AVL Tree Class
class AVL_Tree
{
private:
    TreeNode *root;
    TreeNode *insertNode(int value, TreeNode *root);
    TreeNode *getNode(int value);
    TreeNode *rotateLeft(TreeNode *x);
    TreeNode *rotateRight(TreeNode *x);
    int max(int a, int b);
    int height(TreeNode *root);
    int getBalanceFactor(TreeNode *root);
    void prettyPrintTree(TreeNode *node, std ::string prefix, bool isLeft);
    void deleteCompleteTree(TreeNode *root);
    void preOrder(TreeNode *root);
    void postOrder(TreeNode *root);
    void inOrder(TreeNode *root);
    void levelOrder(TreeNode *root);

public:
    void insert(int value);
    void print(traversal option);

    AVL_Tree()
    {
        root = NULL;
    }
    ~AVL_Tree()
    {
        deleteCompleteTree(root);
    }
};