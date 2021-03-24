//
// Created by Jonathan Yang on 2020/2/22.
//

#ifndef AS3_BST_H
#define AS3_BST_H

#include <iostream>
#include <cmath>

using namespace std;

template <typename T>
class Node{
public:
    Node(){
        l_ = nullptr;
        r_ = nullptr;
        prt_ = nullptr;
    };
    Node(T element){
        l_ = nullptr;
        r_ = nullptr;
        prt_ = nullptr;
        element_ = element;
    };
    Node<T>* l_; // left
    Node<T>* r_; // right
    Node<T>* prt_; // parent
    T element_;
    int hasChild(){
        int result = 0;
        if(l_ != nullptr)
            result++;
        if(r_ != nullptr)
            result++;
        return result;
    }
};


/**
 * BST stands for Binary Search Tree
 */
template <typename T>
class BST {
public:
    BST();
    BST(T element);
    Node<T>* addNext(T element);
    const BST& operator=(const BST& bst);
    Node<T>* root_;

};
template <typename T>
Node<T>* remove(T, BST<T>*);
template <typename T>
T removeInOrderSucc(Node<T>* node);

template <typename T>
BST<T>::BST(){
    root_ = nullptr;
}

template <typename T>
BST<T>::BST(T element) {
    root_ = new Node<T>(element);
}

template <typename T>
Node<T>* BST<T>::addNext(T element) {
    if(root_ == nullptr){
        root_ = new Node<T>(element);
        return root_;
    }
    else{
        Node<T>* current = root_;
        while(true){
            if(element == current->element_)
                return current;
            else if(element < current->element_){
                if(current->l_ == nullptr){
                    current->l_ = new Node<T>(element);
                    current->l_->prt_ = current;
                    return current->l_;
                }
                else
                    current = current->l_;
            }
            else if(element > current->element_){
                if (current->r_ == nullptr) {
                    current->r_ = new Node<T>(element);
                    current->r_->prt_ = current;
                    return current->r_;
                }
                else
                    current = current->r_;
            }
        }
    }
}



template <typename T>
const BST<T> & BST<T>::operator=(const BST<T> &bst) {
    this->root_ = bst.root_;
    return *this;
}


template <typename T>
void printBT(BST<T>* bst) {
    cout << "Print in in-order traversal: " << endl;
    printBTHelper(bst->root_);
    cout << "\n";
}

template <typename T>
void printBTHelper(Node<T> *current) {
    if(current == nullptr){
        cout << "Empty!";
        return;
    }
    if(current->l_ != nullptr){
        printBTHelper(current->l_);
    }
    cout << current->element_ << " ";
    if(current->r_ != nullptr){
        printBTHelper(current->r_);
    }
}

template <typename T>
BST<T> makeBST(T list[]){
    BST<T> tree(list[0]);
    for (int i = 1; list[i]!=(int)NULL ; ++i) {
        tree.addNext(list[i]);
    }
    return tree;
}

int* genData(int n){
    if(n < 0)
        throw runtime_error("ERROR: n < 0");
    if(n == 0)
        return nullptr;
    int* list = new int[n + 1];
    for (int i = 1; i < n - 1; ++i) {
        list[i] = rand() % n * pow(-1,rand());
    }
    list[n] = (int)NULL;
    return list;
}

void printList(int list[]){
    cout << "Printing list: ";
    for (int i = 0; list[i] != (int)NULL; ++i) {
        cout << list[0] << " ";
    }
    cout << "\n";
}

template <typename T>
int height(BST<T> bst){
    Node<T>* current = bst.getRoot();
    return heightHelp(current);
}

template <typename T>
int heightHelp(Node<T>* current){ // false -> left, true -> right
    if(current == nullptr)
        return 0;
    int left =  1 + heightHelp(current->l_);
    int right = 1 + heightHelp(current->r_);
    if(left >= right)
        return left;
    else
        return right;
}

template <typename T>
Node<T>* remove(T element, BST<T>* bst){
    if(bst->root_->element_ == element){
        if(bst->root_->hasChild() == 0){
            delete bst->root_;
            return nullptr;
        }
        else if(bst->root_->hasChild() == 1){
            if(bst->root_->l_ != nullptr){
                Node<T>* temp = bst->root_;
                bst->root_ = bst->root_->l_;
                delete temp;
                bst->root_->l_ = nullptr;
            }
            else{
                Node<T>* temp = bst->root_;
                bst->root_ = bst->root_->r_;
                delete temp;
            }
            return bst->root_;
        }
        else{
            bst->root_->element_= removeInOrderSucc(bst->root_);
            bst->root_->l_->prt_ = bst->root_;
            bst->root_->r_->prt_ = bst->root_;
            return bst->root_;
        }
    }
    // element != root->element
    Node<T>* previous = bst->root_;
    Node<T>* current;
    if(element > previous->element_)
        current = previous->r_;
    else
        current = previous->l_;
    while(previous != nullptr && current != nullptr){
        if(current->element_ == element) {
            if (current->hasChild() == 0) {
                delete current;
                if(element > previous->element_)
                    previous->r_ = nullptr;
                else
                    previous->l_ = nullptr;
                return previous;
            } else if (current->hasChild() == 1) {
                if (current->l_ != nullptr) {
                    Node<T> *temp = current;
                    if (current->element_ > previous->element_) {
                        current->l_->prt_ = previous->r_;
                        previous->r_ = current->l_;
                    } else {
                        current->l_->prt_ = previous->l_;
                        previous->l_ = current->l_;
                    }
                    delete temp;
                } else {
                    Node<T> *temp = current;
                    if (current->element_ > previous->element_) {
                        current->r_->prt_ = previous->r_;
                        previous->r_ = current->r_;
                    } else {
                        current->r_->prt_ = previous->l_;
                        previous->l_ = current->r_;
                    }
                    delete temp;
                }
                return previous;
            } else {
                current->element_ = removeInOrderSucc(current);
                return previous;
            }
        }
        previous = current;
        if(element > previous->element_)
            current = previous->r_;
        else
            current = previous->l_;
    }
    cout << "element: " << element << " not found!" << endl;
    return nullptr;
}

/**
 * Assumed that this node has two children
 * @tparam T
 * @param node
 * @return
 */
template <typename T>
T removeInOrderSucc(Node<T>* node){
    Node<T>* r = node->r_;
    while (r->l_ != nullptr){
        r = r->l_;
    }
    T ele = r->element_;
    if(ele > r->prt_->element_)
        r->prt_->r_ = nullptr;
    else
        r->prt_->l_ = nullptr;
    delete r;
    return ele;
}


#endif //AS3_BST_H
