#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include "../bst/bst.h"

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus 
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
	// Constructor/destructor.
	AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
	virtual ~AVLNode();

	// Getter/setter for the node's height.
	int getHeight() const;
	void setHeight(int height);

	// Getters for parent, left, and right. These need to be redefined since they 
	// return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
	// for more information.
	virtual AVLNode<Key, Value>* getParent() const override;
	virtual AVLNode<Key, Value>* getLeft() const override;
	virtual AVLNode<Key, Value>* getRight() const override;

protected:
	int mHeight;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a height of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
	: Node<Key, Value>(key, value, parent)
	, mHeight(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* Getter function for the height. 
*/
template<typename Key, typename Value>
int AVLNode<Key, Value>::getHeight() const
{
	return mHeight;
}

/**
* Setter function for the height. 
*/
template<typename Key, typename Value>
void AVLNode<Key, Value>::setHeight(int height)
{
	mHeight = height;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
	// Methods for inserting/removing elements from the tree. You must implement
	// both of these methods. 
	virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
	virtual void remove(const Key& key);

private:
	/* Helper functions are strongly encouraged to help separate the problem
	   into smaller pieces. You should not need additional data members. */
	
	//My helper functions:
	int getBalance(AVLNode<Key, Value> *node);
	int calcHeight(AVLNode<Key, Value> *current);
	void rotateLeft(AVLNode<Key, Value> *parent, AVLNode<Key, Value> *child);
    void rotateRight(AVLNode<Key, Value> *parent, AVLNode<Key, Value> *child);
    void insertHelper(AVLNode<Key, Value>* current, AVLNode<Key, Value>* child);
	void swapNode(AVLNode<Key,Value>* node1, AVLNode<Key,Value>* node2);
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

//Helper functions:

template<typename Key, typename Value>
int AVLTree<Key, Value>::getBalance(AVLNode<Key, Value> *node)  
{  
    if (node == NULL) {return 0;}
    //both child don't exist
    else if (node->getLeft() == NULL && node->getRight() == NULL) {return 0;}
    //only right child exists
    else if (node->getLeft() == NULL) {return node->getRight()->getHeight() + 1;}
    //only left child exists
    else if (node->getRight() == NULL) {return (-1) - node->getLeft()->getHeight();}
    //both children exist!
    else {return (node->getRight()->getHeight() - node->getLeft()->getHeight());} 

    //NOTE: Negative balance if left is larger, positive balance if right is larger.
}  

template<typename Key, typename Value>
int AVLTree<Key, Value>::calcHeight(AVLNode<Key, Value> *current)  
{
	if (current->getLeft() && current->getRight()) { //take max of both children 																							
    	return std::max(current->getLeft()->getHeight(), current->getRight()->getHeight()) + 1;
    }
    
    else if (current->getLeft()){ //only left child exists																					
    	return current->getLeft()->getHeight() + 1;
    }

    else if (current ->getRight()) { //only right exists	 																			
    	return current->getRight()->getHeight() + 1;
    }

    return 0; //is a leaf node
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateLeft (AVLNode<Key, Value> *parent, AVLNode<Key, Value> *child)
{
	if (!child) {return;} //null child

    if (parent->getParent() == NULL) { //parent is root node
        this->mRoot = child; //set child to root
    } 
    else { //grandparent exists

        if (parent == parent->getParent()->getLeft()) { //is the left child
            parent->getParent()->setLeft(child); //set child
        } 
        else { //is the right child
            parent->getParent()->setRight(child); //set child
        }
    }

    child->setParent(parent->getParent()); //set grandparent to child's parent
    parent->setParent(child); //set child to parent's parent
    parent->setRight(child->getLeft()); //set child's left child to parent's right child
    
    if (child->getLeft() != NULL) { 
        child->getLeft()->setParent(parent); //update parent's child's parent
    }
    child->setLeft(parent); //parent is child's child

    parent->setHeight(calcHeight(parent)); //reset heights
    child->setHeight(calcHeight(child)); //reset heights
}


template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateRight (AVLNode<Key, Value> *parent, AVLNode<Key, Value> *child)
{
	if (!child) {return;} //null child

    if (parent->getParent() == NULL) { //parent is root node
        this->mRoot = child; //set child to root
    } 
    else { //grandparent exists
        if (parent == parent->getParent()->getLeft()) { //is left child
            parent->getParent()->setLeft(child); //set child
        } 
        else { //is the right child
            parent->getParent()->setRight(child); //set child
        }
    }

    child->setParent(parent->getParent()); //set grandparent to child's parent
    parent->setParent(child); //set child to parent's parent
    parent->setLeft(child->getRight()); //set child's right child to parent's left child
    
    if (child->getRight() != NULL) {
        child->getRight()->setParent(parent); //update parent's child's parent
    }
    child->setRight(parent); //parent is cihld's child

    parent->setHeight(calcHeight(parent)); //reset heights
    child->setHeight(calcHeight(child)); //reset heights
}


template<typename Key, typename Value>
void AVLTree<Key, Value>::insertHelper(AVLNode<Key, Value>* current, AVLNode<Key, Value>* child) 
{ //current is parent node, child keeps track of child incase of rotation.

	if (current == NULL) {return;} //current is empty

    current->setHeight(calcHeight(current)); //update heights via max of children

    if (child != NULL) { //check if unbalanced
	    if (getBalance(current) > 1) { //rotate LEFT

	    	if (getBalance(current->getRight()) < 0) { //RightLeft case:
	    		rotateRight(current->getRight(), current->getRight()->getLeft());
        		rotateLeft(current, current->getRight()); //rotate right and left
	    	}
	    	else {//RightRight case:
	    		rotateLeft(current, current->getRight()); //rotate left
	    	}
	    }
	    else if (getBalance(current) < -1) { //rotate RIGHT 

	    	if (getBalance(current->getLeft()) > 0) { //LeftRight case:
	    		rotateLeft(current->getLeft(), current->getLeft()->getRight());
        		rotateRight(current, current->getLeft()); //rotate left and right
	    	}
	    	else { //LeftLeft case:
	    		rotateRight(current, current->getLeft()); //rotate right
	    	}
	    }
	}
    insertHelper(current->getParent(), current); //call next parent and child
}


/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	if (this->mRoot == NULL) { //if tree is empty
		this->mRoot = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
		static_cast<AVLNode<Key, Value>*>(this->mRoot)->setHeight(0);
		return; //create node, set to root, return
	}

	AVLNode<Key, Value>* parent = static_cast<AVLNode<Key, Value>*>(this->mRoot); //get root node
	AVLNode<Key, Value>* child = NULL; //for future access

	while(true) {

		if(keyValuePair.first > parent->getKey()) { //key value is greater, thus check right side
			if(parent->getRight() == NULL) { //if no right child																	
				child = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
				parent->setRight(child); //insert as new right child
				break;
			}
			parent = parent->getRight(); //move to right child
		}
		else if(keyValuePair.first < parent->getKey()) { //key value is lesser, thus check left side
			if(parent->getLeft() == NULL) { //if no left child
				child = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
				parent->setLeft(child); //insert as new right child
				break;
			}
			parent = parent->getLeft(); //move to left child
		} 
		else {
			parent->setValue(keyValuePair.second); //if same key, update the node value
			break;
		}
	}

    insertHelper(parent, child); //call insertion helper to clean up tree imbalances
}

/**
* Remove function for a given key. Finds the node, reattaches pointers, and then balances when finished. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    AVLNode<Key, Value>* delete_node = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    //find node to remove

    if(delete_node == NULL) {return;} //can't find item, so return
    
    AVLNode<Key, Value>* parent = delete_node->getParent(); //parent pointer

    if(delete_node->getLeft() && delete_node->getRight()) //check both subtrees
    {
        AVLNode<Key, Value>* next_node = delete_node->getLeft(); //set next node to left of deleted

        while(next_node->getRight()) next_node = next_node->getRight(); //get maximum node on left
        
        AVLNode<Key, Value>* beginBalance = next_node->getParent(); //make balancing node 

        if(next_node->getParent() != delete_node) { //reconnect nodes
            next_node->getParent()->setRight(next_node->getLeft());
        }
        else beginBalance = next_node; //update balance node

        this->replaceNode(delete_node, next_node); //replace with largest value node
        insertHelper(beginBalance, NULL); //uses insertion helper for imbalances
    }

    else if(delete_node->getLeft()) { // only left child
        AVLNode<Key, Value>* leftNode = delete_node->getLeft();
        this->replaceNode(delete_node, leftNode);
        insertHelper(leftNode, NULL);
    }

    else if(delete_node->getRight()) { // only right child
        AVLNode<Key, Value>* rightNode = delete_node->getRight();
        this->replaceNode(delete_node, rightNode);
        insertHelper(rightNode, NULL);
    }
    else { // no child
        this->replaceNode(delete_node, NULL);
        insertHelper(parent, NULL);
    } 
}


/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif
