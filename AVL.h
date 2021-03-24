//
// Created by Jonathan Yang on 2020/4/2.
//


#ifndef PROJECT_AVL_AVL_H
#define PROJECT_AVL_AVL_H

#include <fstream>
#include <cstdlib>
#include "BST.h"

using namespace std;



class AVL : public BST<int>{
public:
    int height();
};
// Non-member function titles
int getHeight(Node<int>* node);
int check_balance(Node<int>* node);
void DeleteAVLTree(AVL* tree);
template <typename T>
void DeleteAVLTreeHelp(Node<T>* node);
void genInputFile(int n, const string& fileName);
AVL BuildAVLTree(string fileName);
void InsertNodeAVL(AVL* tree, int element);
void DeleteNodeAVL(AVL* tree, int element);
Node<int>* leftRotation(Node<int>* node);
Node<int>* rightRotation(Node<int>* node);
void printAVL(AVL *tree);
template <typename T>
void printPreOrderBTHelper(Node<T>* current);

/**
 * A recursive call that returns the height from the current node
 * @tparam T
 * @param node
 * @return
 */
int AVL::height() {
    return getHeight(root_);
}


// Non member functions

/**
 * return the bigger value between the two (a or b)
 * @param a
 * @param b
 * @return
 */
int max(int a, int b){
    return (a >= b)? a : b;
}

/**
 * Helper function of height()
 * @param node
 * @return
 */
int getHeight(Node<int> *node) {
    if(node == nullptr)
        return 0;
    return 1 + max(getHeight(node->l_),getHeight(node->r_));
}

/**
 * Get the balance of the current node by return (right - left)
 * @param node
 * @return
 */
int check_balance(Node<int> *node) {
    return getHeight(node->r_) - getHeight(node->l_);
}

/**
 * Delete the whole tree by giiving the node of the tree
 * @param tree
 */
void DeleteAVLTree(AVL* tree){
    DeleteAVLTreeHelp(tree->root_);
    tree->root_ = nullptr;
}

/**
 * Helper function of the DeleteAVLTree(AVL* tree)
 * @tparam T
 * @param node
 */
template <typename T>
void DeleteAVLTreeHelp(Node<T>* node){
    if(node->l_ != nullptr)
        DeleteAVLTreeHelp(node->l_);
    if(node->r_ != nullptr)
        DeleteAVLTreeHelp(node->r_);
//    if(node->prt_ != nullptr){
//        if(node->element_< node->prt_->element_){
//            node->prt_->l_ = nullptr;
//        }else{
//            node->prt_->r_ = nullptr;
//        }
//    }
    delete node;
}

/**
 * Generate a file about the information of the Binary tree by giving a
 * integer as n.
 * The first line is an integer (n), which represent the size of the tree;
 * Following are the elements of this tree
 * @param n
 * @param fileName
 */
void genInputFile(int n, const string& fileName){
    ofstream file(fileName);
    file.open(fileName);
    if(file.is_open()){
        file.clear();
        string input = to_string(n) + "\n";
        while(n > 0){
            int r = 1000 + rand() % 4000;
            input += to_string(r);
            n--;
            if(n != 0)
                input += "\n";
        }
        file << input;
    }
    else{
        cout << "ERROR: FILE NOT FOUND!!" << endl;
        exit(10);
    }
}

/**
 * By giving the file name, enters the values of the tree
 * Build a AVL tree with the specific rule of the AVL (rotation)
 * @param fileName
 * @return
 */
AVL BuildAVLTree(string fileName){
    ifstream file(fileName);
    if(file.is_open()){
        AVL tree;
        string line;
        getline(file,line);
//        int i = stoi(line);
        // int value -> number of nodes
        while(getline(file,line)){
            int value = stoi(line);
            InsertNodeAVL(&tree,value);
        }
        return tree;
    }
    else{
        cout << "ERROR: FILE NOT FOUND!" << endl;
        exit(0);
    }
}

/**
 * Insert a node into the avl tree. If the |balance| is larger than 1,
 * then apply rotation to the avl tree.
 *
 * @param tree
 * @param element
 */
void InsertNodeAVL(AVL* tree, int element){
    Node<int>* key = tree->addNext(element);
    if(key->prt_ == nullptr || key->prt_ == tree->root_)
        return;
    Node<int>* actr = key->prt_->prt_; // ancestor node
    int balance;
    // Start rotating
    while(actr != nullptr) {
        balance = check_balance(actr);
        if (balance < -1) {
            if (element < actr->l_->element_)
                actr = rightRotation(actr); // R rotation
            else if (element > actr->l_->element_) {
                actr->l_ = leftRotation(actr->l_);
                actr = rightRotation(actr);
            } // LR rotation
            if(actr->prt_ != nullptr){
                if(actr->element_< actr->prt_->element_){
                    actr->prt_->l_ = actr;
                }else{
                    actr->prt_->r_ = actr;
                }
            }
        }
        else if (balance > 1) {
            if (element > actr->r_->element_)
                actr = leftRotation(actr); // L rotation
            else if (element < actr->r_->element_) {
                actr->r_ = rightRotation(actr->r_);
                actr = leftRotation(actr);
            } // RL rotation
            if(actr->prt_ != nullptr){
                if(actr->element_< actr->prt_->element_){
                    actr->prt_->l_ = actr;
                }else{
                    actr->prt_->r_ = actr;
                }
            }
        }
        if(tree->root_->prt_ != nullptr) {
            tree->root_ = tree->root_->prt_;
            break;
        }
        actr = actr->prt_;
    }
}

/**
 * Delete the node in the avl, if not found, return nullptr
 *
 * @param tree
 * @param element
 */
void DeleteNodeAVL(AVL* tree, int element){
    Node<int>* actr = remove(element,tree);
    if(actr != nullptr) {
        int balance;
        while (true) {
            balance = check_balance(actr);
            if (balance > 1) {
                actr = leftRotation(actr);
            } else if (balance < -1) {
                actr = rightRotation(actr);
            }
            if (tree->root_->prt_ != nullptr) {
                tree->root_ = tree->root_->prt_;
                break;
            }
            if (actr ->prt_ == nullptr)
                return;
            else{
                if(actr->element_< actr->prt_->element_){
                    actr->prt_->l_ = actr;
                }else{
                    actr->prt_->r_ = actr;
                }
            }
            actr = actr->prt_;
        }
    }
}

/**
 * - Left rotation
 *      actr                            node->prt_
 *          \                           /      \
 *           node->prt_;     ->     actr       node
 *             \
 *             node
 * @param node
 * @return
 */
Node<int>* leftRotation(Node<int>* node){
    Node<int>* pr = node->prt_;
    Node<int>* newRoot = node->r_;
    Node<int>* pivot = newRoot->l_; // possible nullptr
    newRoot->l_ = node;
    node->r_ = pivot;
    // update parent node
    node->prt_ = newRoot;
    if(pivot != nullptr)
        pivot->prt_ = node;
    newRoot->prt_ = pr;
    return newRoot;
}

/**
 * - Right rotation
 *          actr                      node->prt_
 *          /                        /      \
 *     node->prt_;     ->          actr       node
 *         /
 *     node
 * @param node
 * @return
 */
Node<int>* rightRotation(Node<int>* node){
    Node<int>* pr = node->prt_;
    Node<int>* newRoot = node->l_;
    Node<int>* pivot = newRoot->r_; // possible nullptr
    newRoot->r_ = node;
    node->l_ = pivot;
    // update parent node
    node->prt_ = newRoot;
    if(pivot != nullptr)
        pivot->prt_ = node;
    newRoot->prt_ = pr;
    return newRoot;
}

/**
 * Prints the tree in pre-order traversal
 * Recursive function
 * @param tree
 */
void printAVL(AVL *tree){
    cout << "Print in pre-order traversal: " << endl;
    printPreOrderBTHelper(tree->root_);
    cout << "\n";
    printBT(tree);
}

/**
 * Helper function of printAVL()
 * @tparam T
 * @param current
 */
template <typename T>
void printPreOrderBTHelper(Node<T>* current){
    if (current == nullptr){
        cout << "Empty!";
        return;
    }
    cout << current->element_ << " ";
    if(current->l_ != nullptr){
        printBTHelper(current->l_);
    }
    if(current->r_ != nullptr){
        printBTHelper(current->r_);
    }
}



#endif //PROJECT_AVL_AVL_H
