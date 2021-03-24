#include <iostream>
#include "AVL.h"

/*
 * Name: Jonathan Yang
 * ID: 100317635
 * Instructor: Bita Shadgar
 * Section: CPSC 2150 - 001
 * testAVL.cpp
 *      This program tests all the functions of the AVL tree.
 *      The AVL class is a inherited class of BST
*/

int main() {
    // declaration of your variables ...
    srand(time(NULL));
    int n;
    while(true){
        cout << "Enter a non-negative integer: ";
        cin >> n;
        if(n > 0)
            break;
    }
    string filename = "/Users/jonathanYSA/Desktop/CPSC/2150/Project_AVL/inputFile.txt";
    genInputFile(n, filename);
    // generates an input file as explained in part B
    AVL avl = BuildAVLTree(filename);
    cout << "height of AVL tree is:" << avl.height() << endl;
    printAVL(&avl);
    cout << "Enter a value to insert: ";
    int node;
    cin >> node;
    InsertNodeAVL(&avl, node);
    cout << "height of AVL tree is:" << avl.height() << endl;
    printAVL(&avl);
    cout << "Enter a value to delete: ";
    cin >> node;
    DeleteNodeAVL(&avl, node);
    cout << "height of AVL tree is:" << avl.height() << endl;
    printAVL(&avl);
    DeleteAVLTree(&avl);
    printAVL(&avl);
    return 0;
}