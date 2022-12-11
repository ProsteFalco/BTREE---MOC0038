#include "BTree.h"

using namespace std;

/// <summary>
/// Inserts key to the tree
/// </summary>
/// <param name="k">Key to insert</param>
void BTree::insert(int k)
{

    if (root == NULL)
    {
        root = new BTreeNode(degree, true);
        root->keys[0] = k; 
        root->n = 1;
    }
    else
    {

        if (root->n == 2 * degree - 1)
        {
            BTreeNode* s = new BTreeNode(degree, false);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            root = s;
        }
        else 
            root->insertNonFull(k);
    }
}

/// <summary>
/// Removes key from the tree
/// </summary>
/// <param name="k">Key to remove</param>
void BTree::remove(int k)
{
    if (!root)
    {
        cout << "The tree is empty\n";
        return;
    }

    root->remove(k);


    if (root->n == 0)
    {
        BTreeNode* tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];

        delete tmp;
    }
    return;
}

/// <summary>
/// Calls printout on root
/// </summary>
void BTree::Printout()
{
    root->Printout(this->GetHeightOfTree());
}

/// <summary>
/// Gets height of the tree
/// </summary>
/// <returns>Recursively returned height</returns>
int BTree::GetHeightOfTree() {
    return root->Height(0);
}
