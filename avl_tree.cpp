// Compilation g++ -o avl_tree -std=c++11 avl_tree.cpp -I.

#include <avl_tree.h>
#include <queue>

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

    std ::cout << prefix + (isLeft ? "└── " : "┌── ") + std ::to_string(node->data) + "\n";

    if (node->left)
    {
        prettyPrintTree(node->left, prefix + (isLeft ? "    " : "│   "), true);
    }
}

// Pre Order Trversal
void AVL_Tree ::preOrder(TreeNode *root)
{
    if (root == NULL)
        return;

    std ::cout << std ::to_string(root->data) << " ";
    preOrder(root->left);
    preOrder(root->right);
}

// Post Order Traversal
void AVL_Tree ::postOrder(TreeNode *root)
{
    if (root == NULL)
        return;

    postOrder(root->left);
    postOrder(root->right);
    std ::cout << std ::to_string(root->data) << " ";
}

// In Order Traversal
void AVL_Tree ::inOrder(TreeNode *root)
{
    if (root == NULL)
        return;
    postOrder(root->left);
    std ::cout << std ::to_string(root->data) << " ";
    postOrder(root->right);
}

// Level Order or BFS Traversal
void AVL_Tree ::levelOrder(TreeNode *root)
{
    if (root == NULL)
        return;

    std ::queue<TreeNode *> Q;
    Q.push(root);

    while (!Q.empty())
    {
        TreeNode *node = Q.front();
        Q.pop();

        std ::cout << std ::to_string(node->data) << " ";

        if (node->left)
            Q.push(node->left);

        if (node->right)
            Q.push(node->right);
    }

    return;
}

void AVL_Tree ::print(traversal option)
{
    switch (option)
    {
    case PRE_OREDER:
        preOrder(root);
        break;
    case POST_ORDER:
        postOrder(root);
        break;
    case IN_ORDER:
        inOrder(root);
        break;
    case LEVEL_ORDER:
        levelOrder(root);
        break;
    case PRETTY_PRINT:
        prettyPrintTree(root, "", true);
        break;
    }
}

int main()
{
    AVL_Tree *tree = new AVL_Tree();

    for (int index = 1; index < 10; index++)
        tree->insert(index);

/*  Options
    PRE_OREDER,
    POST_ORDER,
    IN_ORDER,
    LEVEL_ORDER,
    PRETTY_PRINT
*/
    tree->print(PRETTY_PRINT);

    delete tree;
}