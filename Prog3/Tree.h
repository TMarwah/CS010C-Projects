#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree( );
  ~Tree( );
  void insert(const string &);
  void insert(const string &, Node* node);
  void preOrder( ) const;
  void preOrder(Node* node) const;
  void inOrder( ) const;
  void inOrder(Node* node ) const;
  void postOrder( ) const;
  void postOrder(Node* node ) const;
  void remove(const string &);
  bool search (const string &) const;
  void split(Node* node, const string& value);

private:
  // Add additional functions/variables here
  const string& smallest(Node* node, const string& string);
  const string& middle(Node* node, const string& string);
  const string& largest(Node* node, const string& string);
    
};

#endif