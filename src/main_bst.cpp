#include <iostream>

#include "BST.h"

int main() {
    BST<int> tree;

    tree.print(inorder);
    //tree.print(preorder);
    //tree.print(postorder);
    tree.insert(25);
    tree.insert(15);
    tree.insert(50);
    tree.insert(10);
    tree.insert(22);
    tree.insert(35);
    tree.insert(70);
    tree.insert(4);
    tree.insert(12);
    tree.insert(18);
    tree.insert(24);
    tree.insert(31);
    tree.insert(44);
    tree.insert(66);
    tree.insert(90);
    tree.insert(42);
    tree.insert(43);
    
    tree.remove(35);
    tree.print(inorder);
    //std::cout << tree.getSuccessor(tree.search(24), postorder)->data << std::endl;
    
    //tree.print(preorder);
    //tree.print(postorder);
    return 0;
}

