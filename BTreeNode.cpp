#include "BTreeNode.h"

using namespace std;

/// <summary>
/// Constructor for tree node
/// </summary>
/// <param name="t1">Tree degree</param>
/// <param name="leaf1">Leaf or internal node</param>
BTreeNode::BTreeNode(int t1, bool leaf1)
{
    t = t1;
    leaf = leaf1;


    keys = new int[2 * t - 1];
    C = new BTreeNode * [2 * t];

    n = 0;
}

/// <summary>
/// Function to find key
/// </summary>
/// <param name="k">Key to find</param>
/// <returns></returns>
int BTreeNode::findKey(int k)
{
    int idx = 0;
    while (idx < n && keys[idx] < k)
        ++idx;
    return idx;
}

/// <summary>
/// Function to find key in the part of the tree rooted in this node
/// </summary>
/// <param name="k">Key to find</param>
void BTreeNode::remove(int k)
{
    int idx = findKey(k);

    if (idx < n && keys[idx] == k)
    {

        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else
    {

        if (leaf)
        {
            cout << "The key " << k << " does not exist in the tree\n";
            return;
        }


        bool flag = ((idx == n) ? true : false);

        if (C[idx]->n < t)
            fill(idx);

        if (flag && idx > n)
            C[idx - 1]->remove(k);
        else
            C[idx]->remove(k);
    }
    return;
}

/// <summary>
/// Function to remove key on index, if the node is leaf
/// </summary>
/// <param name="idx">Index to remove</param>
void BTreeNode::removeFromLeaf(int idx)
{
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];

    n--;

    return;
}

/// <summary>
/// Function to delete the key on index if the node is not leaf
/// </summary>
/// <param name="idx">Index of the key</param>
void BTreeNode::removeFromNonLeaf(int idx)
{

    int k = keys[idx];

  
    if (C[idx]->n >= t)
    {
        int pred = getPred(idx);
        keys[idx] = pred;
        C[idx]->remove(pred);
    }

    else if (C[idx + 1]->n >= t)
    {
        int succ = getSucc(idx);
        keys[idx] = succ;
        C[idx + 1]->remove(succ);
    }

    else
    {
        merge(idx);
        C[idx]->remove(k);
    }
    return;
}

/// <summary>
/// Function to find predecessor (left side)
/// </summary>
/// <param name="idx"></param>
/// <returns></returns>
int BTreeNode::getPred(int idx)
{
    BTreeNode* cur = C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];

    return cur->keys[cur->n - 1];
}
/// <summary>
/// Function to find successor (right side)
/// </summary>
/// <param name="idx"></param>
/// <returns></returns>
int BTreeNode::getSucc(int idx)
{

    BTreeNode* cur = C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];
    return cur->keys[0];
}

/// <summary>
/// Function to fill child on index, that is not full
/// </summary>
/// <param name="idx">Index</param>
void BTreeNode::fill(int idx)
{

    if (idx != 0 && C[idx - 1]->n >= t)
        borrowFromPrev(idx);

    else if (idx != n && C[idx + 1]->n >= t)
        borrowFromNext(idx);

    else
    {
        if (idx != n)
            merge(idx);
        else
            merge(idx - 1);
    }
    return;
}

/// <summary>
/// Function to borrow key on index (left)
/// </summary>
/// <param name="idx">Index</param>
void BTreeNode::borrowFromPrev(int idx)
{

    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx - 1];


    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf)
    {
        for (int i = child->n; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }

    child->keys[0] = keys[idx - 1];

    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;

    return;
}

/// <summary>
/// Function to borrow key on index (right)
/// </summary>
/// <param name="idx">Index</param>
void BTreeNode::borrowFromNext(int idx)
{

    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx + 1];

    child->keys[(child->n)] = keys[idx];

    if (!(child->leaf))
        child->C[(child->n) + 1] = sibling->C[0];

    keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf)
    {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->C[i - 1] = sibling->C[i];
    }

    child->n += 1;
    sibling->n -= 1;

    return;
}

/// <summary>
/// Function to merge nodes, second node is freed after
/// </summary>
/// <param name="idx">Index</param>
void BTreeNode::merge(int idx)
{
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx + 1];


    child->keys[t - 1] = keys[idx];

    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + t] = sibling->keys[i];

  
    if (!child->leaf)
    {
        for (int i = 0; i <= sibling->n; ++i)
            child->C[i + t] = sibling->C[i];
    }

   
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];

    for (int i = idx + 2; i <= n; ++i)
        C[i - 1] = C[i];

    child->n += sibling->n + 1;
    n--;

  
    delete(sibling);
    return;
}

/// <summary>
/// Function to print out tree/subtree based on level (starts at tree height)
/// </summary>
/// <param name="level"></param>
void BTreeNode::Printout(int level)
{
    for (int i = 0; i < level - 1; i++) {
        cout << "\t";    }
    for (int i = 0; i < n; i++) {
        cout << keys[i] << " ";

    }

    if (leaf == false) {
        cout << endl;
        for (int i = 0; i < n + 1; i++) {
            C[i]->Printout(level - 1);
        }
        cout << endl;

    }


}

/// <summary>
/// Recursive method to find height of the tree
/// </summary>
/// <param name="height">Input height</param>
/// <returns>Height + 1</returns>
int BTreeNode::Height(int height)
{
    if (leaf == true)
        return height + 1;
    else {
        return C[0]->Height(height + 1);
    }
}



/// <summary>
/// Insert to non full node
/// </summary>
/// <param name="k">Key to insert</param>
void BTreeNode::insertNonFull(int k)
{
    int i = n - 1;

    if (leaf == true)
    {

        while (i >= 0 && keys[i] > k)
        {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        n = n + 1;
    }
    else 
    {
     
        while (i >= 0 && keys[i] > k)
            i--;

        if (C[i + 1]->n == 2 * t - 1)
        {

            splitChild(i + 1, C[i + 1]);

            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

/// <summary>
/// Splits child 
/// </summary>
/// <param name="i"></param>
/// <param name="y"></param>
void BTreeNode::splitChild(int i, BTreeNode* y)
{

    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];


    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }


    y->n = t - 1;


    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];


    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];


    keys[i] = y->keys[t - 1];


    n = n + 1;
}


/// <summary>
/// Recursive function to search for a key
/// </summary>
/// <param name="k">Key to find</param>
/// <returns>1 or 0 if found or not found</returns>
bool BTreeNode::search(int k)
{
 
    int i = 0;
    while (i < n && k > keys[i])
        i++;


    if (keys[i] == k)
        return true;

    if (leaf == true)
        return NULL;


    return C[i]->search(k);
}