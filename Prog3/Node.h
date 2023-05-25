#ifndef __NODE_H
#define __NODE_H

#include <string>

using namespace std;

class Node {

  friend class Tree;

  public:
  Node();
  Node(const string&);
  
  const string getSmall();
  const string getLarge();

  Node* getLeft();
  Node* getMiddle();
  Node* getRight();
  Node* getParent();

  const void setLeft(Node* node);
  const void setMiddle(Node* node);
  const void setRight(Node* node);
  const void setParent(Node* node);

  const void setSmall(const string&);
  const void setLarge(const string&);
  

  bool isFull() const;
  bool isLeaf() const;

private:
  string small;
  string large;

  Node *left;
  Node *middle;
  Node *right;
  Node *parent;

  // Add additional functions/variables here. Remember, you may not add any
  // Node * or string variables.
  

};

#endif