#include "binary-search-tree.h"
#include <iostream>
#include <queue>

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

using namespace std;

BinarySearchTree::Node::Node(DataType newval)
{
    //INITIALIZING VAL TO NEW VAL, LEFT AND RIGHT TO BE NULL
    val = newval;
    left = right = NULL;
}

int BinarySearchTree::getNodeDepth(Node* n) const
{
    //RECURSIVE FUNCTION RETURNS THE MAX DEPTH OF NODE
    if(n == NULL) return -1;
    return 1 + std::max(getNodeDepth(n->left), getNodeDepth(n->right));
}

BinarySearchTree::BinarySearchTree()
{
    //INITIALIZING ROOT TO NULL AND SIZE TO 0
    root_ = NULL;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree()
{
    //WHILE THE TREE ISN'T EMPTY, REMOVING THE ROOT
    while(size_ > 0)
    {
        remove(root_->val);
    }
}

unsigned int BinarySearchTree::size() const
{
    //RETURNS SIZE OF THE TREE
    return size_;
}

DataType BinarySearchTree::max() const
{
    //TRAVERSING THRU THE TREE TO THE RIGHT MOST NODE AND RETURNING IT
    Node* tempNode = root_;
    while(tempNode -> right != NULL)
    {
        tempNode = tempNode -> right;
    }
    return tempNode -> val;
}

DataType BinarySearchTree::min() const
{
    //TRAVERSING THRU THE TREE TO THE LEFT MOST NODE AND RETURNING IT
    Node* tempNode = root_;
    while(tempNode -> left != NULL)
    {
        tempNode = tempNode -> left;
    }
    return tempNode -> val;
}

unsigned int BinarySearchTree::depth() const
{
    //CALLING THE RECURSIVE FUNCTION
    return getNodeDepth(root_);
}

void BinarySearchTree::print() const
{
    //DOES NOT NEED TO BE COMPLETED!
}

bool BinarySearchTree::exists(DataType val) const
{
    //INITIALIZING A TEMPORARY NODE EQUAL TO THE ROOT
    Node* tempNode = root_;

    //LOOP RUNS TILL TEMPORARY NODE IS NOT EQUAL TO NULL, TILL THE ENTIRE TREE IS SEARCHED
    while(tempNode != NULL)
    {
        //IF VAL IS FOUND, RETURNS TRUE, OTHERWISE, TRAVERSING THRU TREE BASED ON
        //IF THE VAL IS GREATER OR SMALLER THAN THE VALUE OF TEMPORARY NODE
        if(tempNode->val == val) return true;
        else if(val < tempNode->val)
        {
            tempNode = tempNode->left;
        }
        else
        {
            tempNode = tempNode->right;
        }
    }
    //RETURNING FALSE
    return false;
}

Node* BinarySearchTree::getRootNode()
{
    //RETURNING THE ROOT
    return root_;
}

Node** BinarySearchTree::getRootNodeAddress()
{
    //RETURNING THE ADDRESS OF THE ROOT
    return &root_;
}

bool BinarySearchTree::insert(DataType val)
{
    //IF THE ROOT IS NULL, ROOT BECOMES THE NODE OF THE VALUE, SIZE INCREMENTS BY 1,
    //RETURNS TRUE
    if(root_ == NULL)
    {
        root_ = new Node(val);
        size_++;
        return true;
    }
    //IF THE VALUE ALREADY EXISTS, RETURNS FALSE
    if(exists(val)) return false;

    //INITIALIZING A TEMPORARY NODE TO BE EQUAL TO THE ROOT
    Node* tempNode = root_;

    //WHILE LOOP RUNS INFINITELY
    while(true)
    {
        //IF THE VALUE IS SMALLER THAN THE TEMP NODE VALUE
        if(val < tempNode->val)
        {
            //IF THE NEXT NODE TO THE LEFT IS NULL, THE VALUE IS INSERTED TO ITS LEFT
            //BREAKING THE LOOP
            if(tempNode->left == NULL)
            {
                tempNode->left = new Node(val);
                break;
            }
            //TRAVERSING TO THE LEFT OF THE TREE
            tempNode = tempNode->left;
        }
        //OTHERWISE
        else
        {
            //IF THE NEXT NODE TO THE RIGHT IS NULL, THE VALUE  IS INSERTED TO THE RIGHT
            //BREAKING THE LOOP
            if(tempNode->right == NULL)
            {
                tempNode->right = new Node(val);
                break;
            }
            //TRAVERSING TO THE RIGHT OF THE TREE
            tempNode = tempNode->right;
        }
    }
    //SIZE INCREMENTS BY 1, RETURNS TRUE
    size_++;
    return true;
}

Node* findPredecessor(Node* ptr)
{
    //DOES NOT NEED TO BE COMPLETED!
}
Node* delNode(Node* root_, DataType val)
{
    //IF THE ROOT IS NULL, ROOT IS RETURNED
    if (root_ == NULL) return root_;
    //RECURSIVELY CALLING THE SAME FUNCTION BASED ON IF ITS GREATER OR SMALLER THAN ROOT_
    //NOTE THAT ROOT_ CHANGES WITH EVERY FUNCTION CALL
    if (val < root_->val)
        root_->left = delNode(root_->left, val);
    else if (val > root_->val)
        root_->right = delNode(root_->right, val);

    //OTHERWISE, THE NODE HAS BEEN FOUND
    else
    {
        //IF TO THE LEFT IS EMPTY, INITIALIZING A TEMPORARY NODE FROM THE RIGHT, DELETING
        //ROOT AND RETURNING THE TEMPORARY NODE
        if (root_->left == NULL)
        {
            Node* tempNode = root_->right;
            delete root_;
            return tempNode;
        }
        //ELSE IF TO THE RIGHT IS EMPTY, INITIALIZING A TEMPORARY NODE FROM THE LEFT,
        // DELETING ROOT AND RETURNING THE TEMPORARY NODE
        else if (root_->right == NULL)
        {
            Node* tempNode = root_->left;
            delete root_;
            return tempNode;
        }
        //OTHERWISE,
        else
        {
            //INITIALIZING A TEMPORARY NODE EQUAL TO THE RIGHT OF THE ROOT
            Node* tempNode = root_->right;
            //TRAVERSING THRU TO THE LEFT OF THE RIGHT TREE, SO THE MIN VALUE FROM THE RIGHT
            while (tempNode->left != NULL)
                tempNode = tempNode->left;

            //ROOTS VALUE BECOMES TEMPORARY NODES VALUE
            root_->val = tempNode->val;
            //ROOT TO THE RIGHT IS EQUAL TO THE RECURSIVE FUNCTION, SO NULL AND THUS,
            //ROOT IS RETURNED
            root_->right = delNode(root_->right, tempNode->val);
        }
    }
    //RETURNING THE ROOT
    return root_;

}

bool BinarySearchTree::remove(DataType val)
{
    //IF THE VALUE DOESNT EXISTS, RETURNING FALSE
    if (!exists(val)) return false;

    //CALLING HELPER FUNCTION, SIZE DECREASES BY 1, RETURNS TRUE
    root_ = delNode(root_, val);
    size_--;
    return true;
}