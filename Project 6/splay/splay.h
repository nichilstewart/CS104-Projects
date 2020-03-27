#ifndef SPLAY_H
#define SPLAY_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "../bst/bst.h"

/**
* A templated binary search tree implemented as a Splay tree.
*/
template <class Key, class Value>
class SplayTree : public BinarySearchTree<Key, Value>
{
public:
	// Methods for inserting/removing elements from the tree. You must implement
	// both of these methods.
	SplayTree();
	virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
	virtual void remove(const Key& key);
	int report() const;

private:
	/* You'll need this for problem 5. Stores the total number of inserts where the
	   node was added at level strictly worse than 2*log n (n is the number of nodes
	   including the added node. The root is at level 0). */
	int badInserts;
	int totalInserts;

 	//new added functions:
 	void rotateLeft(Node<Key, Value>* n);
 	void rotateRight(Node<Key, Value>* n);
 	void splay(Node<Key, Value>* n);
 	void checkBadInserts(int inserts);
 };

/*
--------------------------------------------
Begin implementations for the SplayTree class.
--------------------------------------------
*/

template<typename Key, typename Value>
SplayTree<Key, Value>::SplayTree() : badInserts(0), totalInserts(0) { }

template<typename Key, typename Value>
int SplayTree<Key, Value>::report() const {
	return badInserts;
}

template<typename Key, typename Value>
void SplayTree<Key, Value>::rotateLeft(Node<Key, Value>* n)
{
	if(n == NULL) {return;} //null node

    Node<Key, Value>* child = n->getRight(); //get right child

    if(n->getParent() == NULL) { //if root-node
        child->setParent(NULL); //set child's parent to null
        this->mRoot = child; //child is new root
    }

    else if(n->getParent() != NULL) { //if not root-node

        Node<Key, Value>* parent = n->getParent(); //make parent node

        if (n==(parent->getLeft())) { //if node is on left
            parent->setLeft(child); //set child left of parent
        }
        else if(n==(parent->getRight())) { //if node is on right
            parent->setRight(child); //set child right of parent
        }
        child->setParent(parent); //set parent as child's parent
    }

    if(child->getLeft() != NULL) { //if left child exists
        child->getLeft()->setParent(n); //rotate left child, change parent
        n->setRight(child->getLeft());
    }

    else{n->setRight(NULL);} //no left child

    child->setLeft(n); //set left child
    n->setParent(child); //set node parent
}


template<typename Key, typename Value>
void SplayTree<Key, Value>::rotateRight(Node<Key, Value>* n)
{
    if (n == NULL) {return;} //null node

    Node<Key, Value>* child = n->getLeft(); //get left child

    if (n->getParent() == NULL) { //if root-node
        child->setParent(NULL); //set child's parent to null
        this->mRoot = child; //child is new root
    }

    else if (n->getParent() != NULL) { //if not root-node

        Node<Key, Value>* parent = n->getParent(); //make parent node

        if (n == (parent->getLeft())) { //if node is on left
            parent->setLeft(child); //set child left of parent
        }
        else if (n==(parent->getRight())) { //if node is on right
            parent->setRight(child); //set child right of parent
        }
        child->setParent(parent); //set parent as child's parent
    }

    if (child->getRight() != NULL) { //if right child exists
        child->getRight()->setParent(n); //rotate right child, change parent
        n->setLeft(child->getRight()); 
    }

    else {n->setLeft(NULL);} //no right child

    child->setRight(n); //set right child
    n->setParent(child); //set node parent
}


template<typename Key, typename Value>
void SplayTree<Key, Value>::splay(Node<Key, Value>* n){
	
	if (n == NULL) {return;} //if empty

	while (true) {//iterative splay

		Node<Key, Value>* parent = n->getParent(); //make parent

		if (parent == NULL) {break;} //no parent exists, return
		
		Node<Key, Value>* grandparent = parent->getParent(); //make grandparent

		if (grandparent == NULL) { //no grandparent, thus single rotation
			if (parent->getLeft() == n) {rotateRight(parent);} //on left
			else {rotateLeft(parent);} //on right
			break;
		}
		if (grandparent->getLeft() == parent) { //if Left
			if (parent->getLeft() == n) { //Left-Left
				rotateRight(grandparent); //rotate grandparent
				rotateRight(parent); //rotate parent
			}
			else { // Left-Right
				rotateLeft(parent); //rotate parent
				rotateRight(grandparent); //rotate grandparent
			}
		}
		else { //if Right
			if (parent->getLeft() == n) { //Right-Left
				rotateRight(parent); //rotate parent
				rotateLeft(grandparent); //rotate grandparent
			}
			else { //Left-Left
				rotateLeft(grandparent); //rotate grandparent
				rotateLeft(parent); //rotate parent
			}
		}
	}
	this->mRoot = n; //set root to most recent node
}

template<typename Key, typename Value>
void SplayTree<Key, Value>::checkBadInserts(int inserts) 
{
	//std::cerr << "total nodes: " << totalInserts << std::endl;
	//std::cerr << "insert count: " << inserts << std::endl;
	//std::cerr << "2*log(n) value: " << 2.0 * std::log2(totalInserts) << std::endl;


	if ((double)inserts > (2 * std::log2(totalInserts))) { 
		badInserts++; //splay insertion is more expensive than AVL insertion
	}
}


/**
* Insert function for a key value pair. Finds location to insert the node and then splays it to the top.
*/

template<typename Key, typename Value>
void SplayTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair) {

	totalInserts++; //add one to total inserts
	Key k = keyValuePair.first; //make key variable

	if(this->mRoot == NULL) { //if tree is empty
		this->mRoot = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
		return;
	}

	Node<Key, Value>* parent = this->mRoot; //copy root node
	int inserts = 0; //create inserts variable

	while(true) { //insert node in position
		inserts++; //update total inserts

		if(parent->getKey() == k){ //found the key in tree
			parent->setValue(keyValuePair.second); //update value
			break;
		}

		if(parent->getKey() > k) { //value must go to left

			if(parent->getLeft() != NULL) { //exists a left child
				parent = parent->getLeft(); //move parent
			}
			else{ //there does not exist a left child
				Node<Key, Value>* n = new Node<Key, Value>(k, keyValuePair.second, parent);
				parent->setLeft(n); //set node as child
				parent = parent->getLeft(); //update parent to new node
				break;
			}
		}

		else{ //value must go to right
			if(parent->getRight() != NULL) { //exists a right child
				parent = parent->getRight(); //mov parent
			}
			else{ //does not exist right child
				Node<Key, Value>* n = new Node<Key, Value>(k, keyValuePair.second, parent);
				parent->setRight(n); //set node as child
				parent = parent->getRight(); //update parent to new node
				break;
			}
		}
	}

	if (inserts != -1) {
		checkBadInserts(inserts); //check if expensive insertion
	}
	splay(parent); //splay the new node to the top!
}

/**
* Remove function for a given key. Finds the node, reattaches pointers, and then splays the parent
* of the deleted node to the top.
*/

template<typename Key, typename Value>
void SplayTree<Key, Value>::remove(const Key& key)
{
    Node<Key, Value>* delete_node = this->internalFind(key); //copy node to remove
    
    if (delete_node == NULL || delete_node->getKey() != key) {return;} //can't find node in tree

    totalInserts--; //remove 1 insertion from total
    Node<Key, Value>* parent = delete_node->getParent(); //make parent for final splay
    Node<Key, Value>* left_node = delete_node->getLeft(); //make node to find left-max

    if (delete_node->getLeft() && delete_node->getRight()) {

        while(left_node->getRight()) { //get max of left part of tree
            left_node = left_node->getRight(); //left_node = max of left
        }
        if(left_node->getParent() != delete_node) { //reattach left child pointers
            left_node->getParent()->setRight(left_node->getLeft());

            if (left_node->getLeft()) {//if rightmost node has left child		
            	left_node->getLeft()->setParent(left_node->getParent()); //reattach children
            }	
        }
        this->replaceNode(delete_node, left_node); //replace with rightmost
    }
    else if(delete_node->getLeft()) //only for left child
    {
        this->replaceNode(delete_node, delete_node->getLeft()); //replace nodes
    }
    else if(delete_node->getRight()) //only for right child
    {
        this->replaceNode(delete_node, delete_node->getRight()); //replace nodes
    }
    else // no child
    {
        this->replaceNode(delete_node, NULL); //replace single node
    }

    if (parent != NULL) {
        splay(parent); //splay parent to the top
    }
}

/*
------------------------------------------
End implementations for the SplayTree class.
------------------------------------------
*/

#endif
