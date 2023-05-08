#include "Node.h"

Node::Node(const string& data)
: data(data),count(1),left(nullptr),right(nullptr){}

Node::~Node(){
    delete left;
    delete right;
}