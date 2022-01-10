#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan {preorder, inorder, postorder};

template<class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp=inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(BSTNode<T> *node, TraversalPlan tp) const;
    BSTNode<T> *findParent(BSTNode<T> *node) const;

private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_H

template<class T>
BST<T>::BST() {
    root = NULL;
}

template<class T>
BST<T>::BST(const BST<T> &obj) {
    root = obj.root;
}

template<class T>
BST<T>::~BST() {
    root = NULL;
}

template<class T>
BSTNode<T> *BST<T>::findParent(BSTNode<T> *node) const {
    BSTNode<T> *temp = new BSTNode<T>;
    BSTNode<T> *parent = new BSTNode<T>;
    temp = root;
    if(node == parent)return node;
    while(temp->data != node->data){
        if(node->data < temp->data){
            parent = temp;
            temp = temp->left;
        }
        else if(node->data > temp->data){
            parent = temp;
            temp = temp->right;
        }
    }
    return parent;
}

template<class T>
BSTNode<T> *BST<T>::getRoot() const {
    return root;
}

template<class T>
bool BST<T>::isEmpty() const {
    if(root == NULL) return true;
    else return false;
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node) const {
    BSTNode<T> *temp = new BSTNode<T>;
    temp = root;
    while(temp != NULL){
        if(temp->data == node->data) {
            return true;
            break;
        }
        if(node->data > temp->data){
            temp = temp->right;
        }
        else if(node->data < temp->data ) {
            temp = temp->left;
        }
    }
    return false;
    
}

template<class T>
void BST<T>::insert(const T &data) {
    BSTNode<T> *newNode = new BSTNode<T>;
    newNode->data = data;
    if(root == NULL){
        root = newNode;
    }
    else{
        BSTNode<T> *temp = new BSTNode<T>;
        temp = root;
        while(temp != NULL){
            if(contains(newNode)) {
                std::cout << "Cannot insert same value, value is: " << newNode->data << std::endl;
                break;
            }
            if(newNode->data > temp->data && temp->right != NULL){
                temp = temp->right;
            }
            else if (newNode->data > temp->data && temp->right == NULL){
                temp->right = newNode;
                break;
            }
            else if(newNode->data < temp->data && temp->left != NULL) {
                temp = temp->left;
            }
            else if (temp->left == NULL){
                temp->left = newNode;
                break;
            }
        }
    }
}

template<class T>
void BST<T>::remove(const T &data) {
    BSTNode<T> *curr = new BSTNode<T>;
    curr = search(data);
    
    if (curr == NULL) {
        return;
    }
    // Node is leaf
    if (curr->left == NULL && curr->right == NULL){
        if (curr != root)
        {
            BSTNode<T> *parent = new BSTNode<T>;
            parent = findParent(curr);
            if (parent->left == curr) {
                parent->left = NULL;
            }
            else {
                parent->right = NULL;
            }
        }
        else {
            root = NULL;
        }
    }
    // Node has one child to the left
    if (curr->left && curr->right == NULL){
        BSTNode<T> *parent = new BSTNode<T>;
        parent = findParent(curr);
        if (parent->left == curr) {
            parent->left = curr->left;
        }
        else {
            parent->right = curr->left;
        }
    }
    // Node has one child to the left
    if (curr->left == NULL && curr->right){
        BSTNode<T> *parent = new BSTNode<T>;
        parent = findParent(curr);
        if (parent->left == curr) {
            parent->left = curr->right;
        }
        else {
            parent->right = curr->right;
        }
    }
    
    // Node has two child
    if(curr->right && curr->left ){
        BSTNode<T> *succ = new BSTNode<T>;
        succ = getSuccessor(curr, inorder);
        BSTNode<T> *parent = new BSTNode<T>;
        parent = findParent(curr);
        if(succ == curr->right){
            succ->left = curr->left;
            if(curr == parent->right){
                parent->right = succ;
            }
            else{
                parent->left = succ;
            }
        }
        else if(curr == parent->right){
            curr->right->left = succ->right;
            succ->left = curr->left;
            succ->right = curr->right;
            parent->right = succ;
        }
        else{
            curr->right->left = succ->right;
            succ->left = curr->left;
            succ->right = curr->right;
            parent->left = succ;
        }
    }
    
    
}

template<class T>
void BST<T>::removeAllNodes() {
    root = NULL;
}

template<class T>
BSTNode<T> *BST<T>::search(const T &data) const {
    BSTNode<T> *temp = new BSTNode<T>;
    temp = root;
    while(temp != NULL){
        if(temp->data == data) {
            return temp;
            break;
        }
        if(data > temp->data){
            temp = temp->right;
        }
        else if(data < temp->data ) {
            temp = temp->left;
        }
    }
    return NULL;
}

template<class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const {
    if(root == NULL)return NULL;
    if(node == NULL)return NULL;
    if (tp == inorder) {
        if(node->right != NULL){
            BSTNode<T> *temp = new BSTNode<T>;
            temp = node->right;
            while(temp->left != NULL) temp = temp->left;
            return temp;
        }
        else{
            BSTNode<T> *temp = new BSTNode<T>;
            BSTNode<T> *successor = new BSTNode<T>;
            temp = root;
            while(temp != node){
                if(node->data < temp->data){
                    successor = temp;
                    temp = temp->left;
                }
                else
                    temp = temp->right;
            }
            return successor;
        }
    }
    else if (tp == preorder) {
        if(node->left != NULL)return node->left;
        else if(node->right != NULL)return node->right;
        BSTNode<T> *parentNode = new BSTNode<T>;
        parentNode = findParent(node);
        if(parentNode && node == parentNode->left){
            while(parentNode)
                {
                    if (parentNode->right)return parentNode->right;
                    parentNode = findParent(parentNode);
                }
                return parentNode;
        }
        else{
            BSTNode<T> *curr = new BSTNode<T>;
            curr = node;
            while(parentNode){
                if(curr == parentNode->left && parentNode->right)return parentNode->right;
                curr = parentNode;
                parentNode = findParent(parentNode);
            }
        }
        return NULL;
        
    }
    else if (tp == postorder) {
        BSTNode<T> *parentNode = new BSTNode<T>;
        parentNode = findParent(node);
        if (parentNode == NULL)return NULL;
        if (node == parentNode->right){
                return parentNode;
            }
            if (parentNode->right){
                BSTNode<T> *temp = new BSTNode<T>;
                temp = parentNode->right;
                while (temp->left){
                    temp = temp->left;
                }
                return temp;
            }
            return parentNode;
    }
    return NULL;
}

template<class T>
void BST<T>::print(TraversalPlan tp) const {

    if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, inorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == preorder) {
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        std::cout << "BST_preorder{" << std::endl;
        print(root, preorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) {
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }
        std::cout << "BST_postorder{" << std::endl;
        print(root, postorder);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    /* TODO */
}

template<class T>
void BST<T>::print(BSTNode<T> *node, TraversalPlan tp) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    if (tp == inorder) {
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->data;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } else if (tp == preorder) {
        std::cout << "\t" << node->data;
        
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);
        
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
        
    } else if (tp == postorder) {
        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }
        
        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
        std::cout << "\t" << node->data;
    }
}
