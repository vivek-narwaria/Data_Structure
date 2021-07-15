// Copilation g++ -o avl_tree -std=c++11 avl_tree.c

#include <iostream>
#include <string>

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

public:
    void insert(int value);
    void print();
    AVL_Tree()
    {
        root = NULL;
    }
    ~AVL_Tree()
    {
        deleteCompleteTree(root);
    }
};

// Delete all node in AVL tree
void AVL_Tree ::deleteCompleteTree(TreeNode *node)
{
    if (node == NULL)
        return;

    deleteCompleteTree(node->left);
    deleteCompleteTree(node->right);
    delete node;
}

// Return Balance factor of node in tree
int AVL_Tree ::getBalanceFactor(TreeNode *node)
{
    int balance = 0;
    if (node != NULL)
        balance = height(node->left) - height(node->right);
    return balance;
}

// Return height of node in tree
int AVL_Tree ::height(TreeNode *node)
{
    int _height = 0;
    if (node != NULL)
        _height = node->height;
    return _height;
}

// Return Max
int AVL_Tree ::max(int a, int b)
{
    return a > b ? a : b;
}

// Create New Node for Tree
TreeNode *AVL_Tree ::getNode(int value)
{
    TreeNode *node = new TreeNode();
    node->data = value;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// Rotate Left
TreeNode *AVL_Tree ::rotateLeft(TreeNode *x)
{
    TreeNode *y = x->right;
    TreeNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

// Rotate Right
TreeNode *AVL_Tree ::rotateRight(TreeNode *x)
{
    TreeNode *y = x->left;
    TreeNode *T2 = y->right;

    y->right = x;
    x->left = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

// Insert Element in AVL Tree
TreeNode *AVL_Tree ::insertNode(int value, TreeNode *root)
{
    int balance = 0;
    if (root == NULL)
    {
        return getNode(value);
    }

    if (value < root->data)
    {
        root->left = insertNode(value, root->left);
    }
    else if (value > root->data)
    {
        root->right = insertNode(value, root->right);
    }
    else
    {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));
    balance = getBalanceFactor(root);

    // Left Left Case
    if (balance > 1 && value < root->left->data)
    {
        return rotateRight(root);
    }
    // Left Right Case
    if (balance > 1 && value > root->left->data)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    // Rigt Right Case
    if (balance < -1 && value > root->right->data)
    {
        return rotateLeft(root);
    }
    // Right Left Case
    if (balance < -1 && value < root->right->data)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Inser Element in AVL Tree
void AVL_Tree ::insert(int value)
{
    root = insertNode(value, root);
}

// Print AVL Tree
void AVL_Tree ::prettyPrintTree(TreeNode *node, std ::string prefix, bool isLeft)
{
    if (node == NULL)
    {
        std ::cout << "Empty tree";
        return;
    }

    if (node->right)
    {
        prettyPrintTree(node->right, prefix + (isLeft ? "│   " : "    "), false);
    }

    std ::cout << prefix + (isLeft ? "└── " : "┌── ") + std ::to_string(node->data) + ":height(" + std ::to_string(node->height) + ")" + "\n";

    if (node->left)
    {
        prettyPrintTree(node->left, prefix + (isLeft ? "    " : "│   "), true);
    }
}

void AVL_Tree ::print()
{
    prettyPrintTree(root, "", true);
}

int main()
{
    AVL_Tree *tree = new AVL_Tree();

    for (int index = 1; index < 10; index++)
        tree->insert(index);

    tree->print();

    delete tree;
}