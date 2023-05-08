#include "BSTree.h"
#include <stdexcept>
#include <iostream>

using namespace std;
//creates empty tree with null root
BSTree::BSTree()
: root(nullptr){}

BSTree::~BSTree(){
    //keep calling clear from root
    treeClear(root);

}

void BSTree::treeClear(Node* node) {
    if (node != nullptr) {
        //recall this function and delete all nodes from left and right subtree (effectively clearing the tree and root)
        treeClear(node->left);
        treeClear(node->right);
        delete node;
    }
}

void BSTree::insert(const string& insertValue){
    if (root == nullptr){
        root = new Node(insertValue);
        return;
    }

    Node* curr = root;

    //do not end until node is added
    while (1){
        //check case for duplicate data node
        if (insertValue == curr->data){
            curr->count++;
            return;
        }
        else if(insertValue < curr->data){
            //if left node is empty, put new node there
            if (curr->left == nullptr){
                curr->left = new Node(insertValue);
                return;
            }
            //else, continue traversal
            curr = curr->left;
        }
        else{
            if (curr->right == nullptr){
                curr->right = new Node(insertValue);
                return;
            }
            curr = curr->right;
        }
    }
}

bool BSTree::search(const string& searchVal) const{
    Node* curr = root;

    while (curr != nullptr){
        //if the value being searched resides at the root of the tree
        if (searchVal == curr->data){
            return true;
        }
        //otherwise, traverse left
        else if (searchVal < curr->data){
            curr = curr->left;
        }
        //otherwise, traverse right
        else {
            curr = curr->right;
        }
    }
    //if the node is never found, return false
    return false;
}

string BSTree::largest() const{
    //empty tree check case
    if (root == nullptr){
        return "";
    }

    Node* curr = root;

    //keep setting "curr" to its right child (larger) until no larger nodes exist
    while (curr->right != nullptr){
        curr = curr->right;
    }
    return curr->data;
}

string BSTree::smallest() const{
    //empty tree check case
    if (root == nullptr){
        return "";
    }
    Node* curr = root;
    
    //keep setting "curr" to its left child (smaller) until no smaller nodes exist
    while (curr->left != nullptr){
        curr = curr->left;
    }
    return curr->data;
}

int BSTree::height(const string& heightVal) const{
    Node* curr = root;
    int height = 0;

    while (curr != nullptr){
        if (heightVal == curr->data){
            //once node is found, return height (aka the number of layers traversed)
            return height;
        }
        else if (heightVal< curr->data){
            //traverse left
            curr = curr->left;
        }
        else {
            //traverse right
            curr = curr->right;
        }
        //for each layer traversed, the height is incremented to track where the heightVal is located
        height++;
    }
    //if the heightVal is never found, "return height" never happens therefore -1 is returned
    return -1;
}

void BSTree::remove(const string& removeVal){
    Node* curr = root;
    Node* parent = nullptr;

    //determine node for removal and parent
    //as long as end of tree is not reached && the removeVal is not found, continue traverse/store
    while (curr != nullptr && curr->data != removeVal){
        parent = curr;
        //traverse left, storing parent
        if (removeVal < curr->data){
            curr = curr->left;
        }
        //traverse right, storing parent
        else {
            curr = curr->right;
        }
    }

    //check case for node-not-found
    if (curr == nullptr){
        throw runtime_error("Node not found");
    }

    //if the found node has a count > 1, decrement
    if (curr->count > 1){
        curr->count = curr->count - 1;
        return;
    }

    //check case for leaf removal
    if (curr->left == nullptr && curr->right == nullptr){
        //root check case
        if (curr == root){
            root = nullptr;
        }
        //if leaf is a left child
        else if (curr == parent->left){
            parent->left = nullptr;
        }
        //if leaf is a right child
        else{
            parent->right = nullptr;
        }
        delete curr;
    //if node has a left child
    }else if (curr->left != nullptr){
        Node* lsbtLargest = curr->left;
        Node* lsbtParent = curr;

        //left sub tree largest
        //keep traversing until largest left sub tree is found (aka no more right children exist)
        while (lsbtLargest->right != nullptr){
            //new parent is curr largest
            lsbtParent = lsbtLargest;
            //traverse right
            lsbtLargest = lsbtLargest->right;
        }

        //replace removal node with largest of left subtree to maintain BST
        curr->data = lsbtLargest->data;
        curr->count = lsbtLargest->count;

        //link removed node to new largest
        if (lsbtLargest == curr->left){
            curr->left = lsbtLargest->left;
        }
        //otherwise, remove and set new parent child
        else{
            lsbtParent->right = lsbtLargest->left;
        }

        delete lsbtLargest;
    }
    //check case: node has no children but isnt leaf
    else{
        //similar double pointer approach
        Node* rsbtSmallest = curr->right;
        Node* rsbtParent = curr;

        //find smallest node in the right subtree
        //traverse right sub tree until no smaller nodes exist
        while (rsbtSmallest->left != nullptr){
            //set new parent
            rsbtParent = rsbtSmallest;
            //traverse left
            rsbtSmallest = rsbtSmallest->left;
        }

        //replace removal node with the smallest value in the right subtree to maintain BST

        if (rsbtSmallest == curr->right){
            curr->right = rsbtSmallest->right;
        }
        else{
            rsbtParent->left = rsbtSmallest->right;
        }
        delete rsbtSmallest;
    }
}

void BSTree::printNode(const Node* curr) const{
    if (curr == nullptr){
        return;
    }
    cout << curr->data << "(" << curr->count << "), ";
}

void BSTree::inOrder() const {
    inOrder(root);
}

void BSTree::preOrder() const {
    preOrder(root);
    
}

void BSTree::postOrder() const {
    postOrder(root);
    
}

void BSTree::preOrder(Node* node) const {
    if (node != nullptr) {
        //start root
        //print helper
        printNode(node);
        //left subtree
        preOrder(node->left);
        //right subtree
        preOrder(node->right);
    }
}

void BSTree::postOrder(Node* node) const {
    if (node != nullptr) {
        //left subtree
        preOrder(node->left);
        //right subtree
        preOrder(node->right);
        //root
        //print helper
        printNode(node);
    }
}

void BSTree::inOrder(Node* node) const {
    if (node != nullptr) {
        //recursion to start from smallest node possible
        inOrder(node->left);
        //print helper
        printNode(node);
        //recursion to then print larger values last
        preOrder(node->right);
    }
}