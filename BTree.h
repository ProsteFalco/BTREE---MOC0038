#include <iostream>
#include "BTreeNode.h"

class BTree
{
    BTreeNode* root;
    int degree;
public:

    BTree(int d)
    {
        root = NULL;
        degree = d;
    }

    bool search(int k)
    {
        return (root == NULL) ? NULL : root->search(k);
    }

    void insert(int k);

    void remove(int k);
    
    void Printout();

    int GetHeightOfTree();

};