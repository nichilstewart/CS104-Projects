#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<Key, Value>& getItem() const;
	std::pair<Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Key& getKey();
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);

protected:
	std::pair<Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
};

/* 
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent)
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the destructor in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<Key, Value>& Node<Key, Value>::getItem() const
{
	return mItem;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& Node<Key, Value>::getItem()
{
	return mItem;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
	return mItem.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
	return mItem.second;
}

/**
* A non-const getter for the key.
*/
template<typename Key, typename Value>
Key& Node<Key, Value>::getKey()
{
	return mItem.first;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
	return mParent;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
	return mLeft;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
	return mRight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
	mParent = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
	mLeft = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
	mRight = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
	mItem.second = value;
}

/* 
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();

	virtual void insert(const std::pair<Key, Value>& keyValuePair);
	virtual void remove(const Key& key); //NOT ORIGINAL SKELETON CODE, MADE FOR VIRTUAL FUNCTIONS
	void clear();
	void print() const;

public:
	/**
	* An internal iterator class for traversing the contents of the BST.
	*/
	class iterator
	{
	public:
		iterator(Node<Key,Value>* ptr);
		iterator();

		std::pair<Key,Value>& operator*();
		std::pair<Key,Value>* operator->();

		bool operator==(const iterator& rhs) const;
		bool operator!=(const iterator& rhs) const;
		iterator& operator=(const iterator& rhs);

		iterator& operator++();

	protected:
		Node<Key, Value>* mCurrent;
	};

public:
	iterator begin();
	iterator end();
	iterator find(const Key& key) const;

protected:
	Node<Key, Value>* internalFind(const Key& key) const;
	Node<Key, Value>* getSmallestNode() const;
	void printRoot (Node<Key, Value>* root) const;

	/* Helper functions are strongly encouraged to help separate the problem
	   into smaller pieces. You should not need additional data members. */
	
	//Here are all my helper functions.
	void deleteTree(Node<Key, Value>* n); //deletes 
	Node<Key, Value>* getSmallestHelper(Node<Key, Value>* n) const;
	Node<Key, Value>* find(const Key& key, Node<Key, Value>* n) const;
	void replaceNode(Node<Key, Value>* current_node, Node<Key, Value>* next_node);


protected:
	Node<Key, Value>* mRoot;

};

/* 
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/ 

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*()
{
	return mCurrent->getItem(); 
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->()
{
	return &(mCurrent->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/* 
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/* 
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
	mRoot = NULL; //set root to null
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::deleteTree(Node<Key, Value>* n) 
{
	if (n == NULL) {return;} //if null, return

	//recursively deletes tree by deleting child and then itself
	deleteTree(n->getLeft());
	deleteTree(n->getRight());
	delete n;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
	deleteTree(mRoot); //calls delete tree helper function
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin()
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end()
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const
{
	Node<Key, Value>* current = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(current);
	return it;
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when
* inserting.
*/

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::replaceNode(Node<Key, Value>* current_node, Node<Key, Value>* next_node)
{ //replaces node in parent
	
    if (current_node->getParent() != NULL) { // attach parent branch
        if (current_node == current_node->getParent()->getLeft()) {
            current_node->getParent()->setLeft(next_node); //set left
        }
        else if (current_node == current_node->getParent()->getRight()){
            current_node->getParent()->setRight(next_node); //set right
        }
    }
    else {
        if (current_node == this->mRoot) {this->mRoot = next_node;} //check root
    }

    if (next_node != NULL) { //reconnect here
        if (next_node->getParent() != current_node) { //make sure not current node
            if (current_node->getLeft()) {
            	current_node->getLeft()->setParent(next_node); //set parent
            }
            next_node->setLeft(current_node->getLeft()); //reset left
        }
        if (current_node->getLeft() != NULL) { // left side exists
           	if (current_node->getRight() != NULL) {
           		current_node->getRight()->setParent(next_node);
           	}
            next_node->setRight(current_node->getRight()); //reset left
        }
        next_node->setParent(current_node->getParent()); //next parent
    }
    delete current_node; //delete memory
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	if (mRoot == NULL) { //if tree is empty
		mRoot = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
		return;
	}

	Node<Key, Value> *current = mRoot; //copy root node for traversal

	while(true) { //find insertion location

		if (keyValuePair.first > current->getKey()) { //key value is greater, thus check right side
			if (current->getRight() == NULL) { //if no right child																	
				Node<Key, Value> *n = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, current);
				current->setRight(n); //insert as new right child
				break; //completed insertion
			}
			current = current->getRight(); //set to right node and continue
		}
		else if (keyValuePair.first < current->getKey()) { //key value is lesser, thus check left side
			if (current->getLeft() == NULL) { //if no left child
				Node<Key, Value> *n = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, current);
				current->setLeft(n); //insert as new right child
				break; //completed insertion
			}
			current = current->getLeft(); //set to left node and continue
		} 
		else {
			current->setValue(keyValuePair.second); //if same key, update the node value
			break; //complete
		}
	}
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key) 
{
	Node<Key, Value>* delete_node = internalFind(key); //copy the desired node
    
    if (delete_node == NULL || delete_node->getKey() != key) {return;} //can't find node in tree

    Node<Key, Value>* left_node = delete_node->getLeft(); //make node to find left-max

    if (delete_node->getLeft() && delete_node->getRight()) {
        
        while (left_node->getRight()) { //get max of left part of tree
            left_node = left_node->getRight(); //left_node = max of left
        }  
        if (left_node->getParent() != delete_node) { //reattach left child pointers
            left_node->getParent()->setRight(left_node->getLeft());
            if (left_node->getLeft()) {//if rightmost node has left child		
            	left_node->getLeft()->setParent(left_node->getParent()); //reattach children
            }
        }
        replaceNode(delete_node, left_node); //replace with rightmost
    }
    else if (delete_node->getLeft()) { //only for left child
        replaceNode(delete_node, delete_node->getLeft()); //replace nodes
    }
    else if (delete_node->getRight()) { //only for right child
        replaceNode(delete_node, delete_node->getRight()); //replace nodes
    }
    else { //no child
        replaceNode(delete_node, NULL); //replace single node
    }
}

/**
* A method to remove all contents of the tree and reset the values in the tree
* for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	deleteTree(mRoot); //delete tree
	mRoot = NULL; //set root to null
}

/**
* A helper function to find the smallest node in the tree.
*/

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestHelper(Node<Key, Value>* n) const 
{	
	Node<Key, Value>* temp_left = n->getLeft(); //get leftmost node

	if (temp_left == NULL) {return n;} //no left node

	return getSmallestHelper(temp_left); //recursively call next left node
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	if (mRoot == NULL) {return NULL;} //if null return

	return getSmallestHelper(mRoot); //calls helper function
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::find(const Key& key, Node<Key, Value>* n) const 
{	
	if (n == NULL) {return NULL;} //if null, return null

	if (n->getKey() == key) {return n;} //if match
	
	else if (n->getKey() < key) {return find(key, n->getRight());} //closest on right
	
	else {return find(key, n->getLeft());} //closest on left
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
	return find(key, mRoot); //returns helper function
}

/**
* Helper function to print the tree's contents
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::printRoot (Node<Key, Value>* root) const
{
	if (root != NULL)
	{
		std::cout << "[";
		printRoot (root->getLeft());
		std::cout << " (" << root->getKey() << ", " << root->getValue() << ") ";
		printRoot (root->getRight());
		std::cout << "]";
	}
}

/* 
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif
