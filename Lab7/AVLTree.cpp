#include "AVLTree.h"

using namespace std;

int AVLTree::height(Node* node){
    if (node == NULL){
        return 0;
    }
    //use node height helper to return the node height
    return node->getHeight();
}

Node* AVLTree::rotate(Node* rotateNode, string key, int balance){
    //left2
    if (balance > 1 && key < rotateNode->getLeft()->getKey()){
        return rightRotate(rotateNode);
    }
    //right2
    if (balance < -1 && key > rotateNode->getRight()->getKey()){
        return leftRotate(rotateNode);
    }

    //leftright
    if (balance > 1 && key > rotateNode->getLeft()->getKey()){
        rotateNode->setLeft(leftRotate(rotateNode->getLeft()));
        return rightRotate(rotateNode);
    }
    //rightleft
    if (balance < -1 && key < rotateNode->getRight()->getKey()){
        rotateNode->setRight(rightRotate(rotateNode->getRight()));
        return leftRotate(rotateNode);
    }
    else return nullptr;
}


void AVLTree::printBalanceFactors(Node* node){
    if (node != NULL){
        printBalanceFactors(node->getLeft());
        cout << node->getKey() <<"(" << balanceFactor(node) <<"), ";
        printBalanceFactors(node->getRight());
    }
}

void AVLTree::printBalanceFactors(){
    printBalanceFactors(root);
}
void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->getLeft()){
            visualizeTree(outFS,n->getLeft());
            outFS<<n->getKey() <<" -> " <<n->getLeft()->getKey()<<";"<<endl;    
        }

        if(n->getRight()){
            visualizeTree(outFS,n->getRight());
            outFS<<n->getKey() <<" -> " <<n->getRight()->getKey()<<";"<<endl;    
        }
    }
}

Node* AVLTree::rightRotate(Node* originalMid){
    Node* newCenter = originalMid->getLeft();
    Node* ogRight = newCenter->getRight();

    newCenter->setRight(originalMid);
    originalMid->setLeft(ogRight);

    originalMid->setHeight(max(height(originalMid->getLeft()), height(originalMid->getRight())) + 1);
    newCenter->setHeight(max(height(newCenter->getLeft()), height(newCenter->getRight())) + 1);

    return newCenter;
}

Node* AVLTree::leftRotate(Node* originalMid){
    Node* newCenter = originalMid->getRight();
    Node* ogLeft = newCenter->getLeft();

    newCenter->setLeft(originalMid);
    originalMid->setRight(ogLeft);

    originalMid->setHeight(max(height(originalMid->getLeft()), height(originalMid->getRight())) + 1);
    newCenter->setHeight(max(height(newCenter->getLeft()), height(newCenter->getRight())) + 1);

    return newCenter;
}
Node* AVLTree::insert(Node* node, string key){
    //rotate
    if (node == nullptr){
        return(new Node(key));
    }
    else if (key < node->getKey()){
        node->setLeft(insert(node->getLeft(), key));
    }
    else if (key > node->getKey()){
        node->setRight(insert(node->getRight(), key));
    }
    else{
        //duplicate case
        return node;
    }

    //check balance if rebalance is required
    int balance = balanceFactor(node);
    Node* unbalancedNode = node;

    //adjust height
    node->setHeight(1 + max(height(node->getLeft()), height(node->getRight())));
    //rebalance
    if (balance < -1 || balance > 1){
        return rotate(unbalancedNode, key , balance);
    }
    else{
        return node;
    }
}
//recurse help
void AVLTree::insert(const string &key){
    root = insert(root, key);
}

int AVLTree::balanceFactor(Node* node){
    if (node == nullptr){
        return 0;
    }
    return height(node->getLeft()) - height(node->getRight());
}



int AVLTree::maxFinder(int a, int b){
    if (a>b){
        return a;
    }else{
        return b;
    }
    
}