#include "Tree.h"
#include <iostream>

Tree::Tree() {
  root = nullptr;
}

Tree::~Tree() {
  // TODO: Implement tree destruction (deallocate memory)
}

void Tree::insert(const string &string){
    if (root == nullptr){
        root = new Node(string);
        return;
    }

    insert(string,root);
    
}

void Tree::insert(const string &s, Node* node){
    
    if(!node->isLeaf()) { // if internal node
        if(s < node->getSmall()) return insert(s, node->getLeft());
        if(s > node->getLarge() && node->getRight() != nullptr) return insert(s, node->getRight());
        else return insert(s, node->getMiddle());
    }

    if(node->getLarge() == "" && node->isLeaf()) { // If there's only one key in the node
        if(s < node->getSmall()) { 
            // If we need to switch the inserted key and the key that was already there
            node->setLarge(node->getSmall());
            node->setSmall(s);
            return;
        } 
        // If we don't need to switch, just insert to the open key
        node->setLarge(s);
        return;
    } else if(node->isFull() && node->isLeaf()){
        split(node, s);
    }
}
const string& Tree::smallest(Node* node, const string& value) {
  if (value < node->small) {
    return node->small;
  } else {
    return node->large;
  }
}

const string& Tree::middle(Node* node, const string& value) {
  return node->small;
}

const string& Tree::largest(Node* node, const string& value) {
  if (value > node->large) {
    return node->large;
  } else {
    return node->small;
  }
}

void Tree::split(Node* node, const string& s) {
    // Find what's going to be the left, middle, right, after the "split"
    string left = smallest(node, s);
    string mid = middle(node, s);
    string right = largest(node, s);
    if(node == root && root->getLeft() == nullptr) { //splitting root node
        
        node->setSmall(left);
        node->setLarge("");
        root = new Node(mid);
        root->setLeft(node);
        node->setParent(root);
        root->setMiddle(new Node(right));
        root->getMiddle()->setParent(root);
    } else if(node->getLeft() == nullptr) { // splitting a leaf node
        Node* parent = node->getParent();
        if(node->getParent()->getLarge() == "" && node == parent->getLeft()) { // 2 children and parent's left child

            parent->setLarge(parent->getSmall());
            parent->setSmall(mid);
            parent->setRight(new Node(parent->getMiddle()->getSmall()));
            parent->getRight()->setParent(parent);
            parent->getMiddle()->setSmall(right);
            node->setSmall(left);
            node->setLarge("");
        } else if(node->getParent()->getLarge() == "" && node == parent->getMiddle()) { // 2 children and parent's middle child
            node->getParent()->setLarge(mid);
            node->getParent()->setRight(new Node(right));
            node->getParent()->getRight()->setParent(node->getParent());
            node->setSmall(left);
            node->setLarge("");
        } else { // 2 children and parent's rights child
            node->setSmall(left);
            node->setLarge(right);
            split(node->getParent(), mid);
        }
    }   
    return;
}

void Tree::preOrder(Node* node) const {
  if (node == nullptr) {
    return;
  }

  cout << node->small << " ";

  if (node->left != nullptr) {
    preOrder(node->left);
  }

  if (node->large != "") {
    cout << node->large << " ";
  }

  if (node->middle != nullptr) {
    preOrder(node->middle);
  }

  if (node->right != nullptr) {
    preOrder(node->right);
  }
}

void Tree::preOrder() const {
  preOrder(root);
  cout << endl;
}

void Tree::inOrder(Node* node) const {
  if (node == nullptr) {
    return;
  }

  if (node->left == nullptr && node->middle == nullptr && node->right == nullptr) {
    // Node is a leaf
    cout << node->small << " ";
  } else if (node->large.empty()) {
    // Node is a 2-node
    inOrder(node->left);
    cout << node->small << " ";
    inOrder(node->right);
  } else {
    // Node is a 3-node
    inOrder(node->left);
    cout << node->small << " ";
    inOrder(node->middle);
    cout << node->large << " ";
    inOrder(node->right);
  }
}

void Tree::inOrder() const {
  inOrder(root);
  cout << endl;
}


void Tree::postOrder(Node* node) const {
  if (node == nullptr) {
    return;
  }

  if (node->left != nullptr) {
    postOrder(node->left);
  }

  if (node->middle != nullptr) {
    postOrder(node->middle);
  }

  if (node->right != nullptr) {
    postOrder(node->right);
  }

  cout << node->small << " ";

  if (node->large != "") {
    cout << node->large << " ";
  }
}

void Tree::postOrder() const {
  postOrder(root);
  cout << endl;
}




void Tree::remove(const string& value) {
  // TODO: Implement removal logic for a 2-3 tree
}

bool Tree::search(const string& value) const {
  Node* curr = root;

  while (curr != nullptr){
    if (value == curr->small || value == curr->large){
        return true;
    }
    if (value < curr->small){
        curr = curr->left;
    }
    else if (curr->large != "" && value > curr->large){
        curr = curr->right;
    }
  }
  return false;
}

