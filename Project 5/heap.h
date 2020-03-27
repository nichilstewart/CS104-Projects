#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>


template <typename T>
class MinHeap {
  public:

    struct Node {
      T item;
      int priority;
      int index;
      Node(T t, int p, int i) : item(t), priority(p), index(i) { }
    };

    MinHeap(int d);
     /* Constructor that builds a d-ary Min Heap
        This should work for any d >= 2,
        but doesn't have to do anything for smaller d.*/

    ~MinHeap();

    int add(T item, int priority);
       /* adds the item to the heap, with the given priority. 
          multiple identical items can be in the heap simultaneously. 
          Returns the number of times add has been called prior to this
          call (for use with the update function).*/

    T & peek();
    //const T & peek() const;
       /* returns the element with smallest priority.  
          If two elements have the same priority, use operator< on the 
          T data, and return the one with smaller data.*/

    void remove();
       /* removes the element with smallest priority, with the same tie-breaker
          as peek. */

    void update(int nth, int priority);
       /* finds the nth item (where nth is 0-based) that has ever been added 
          to the heap (the node that was created on the nth call to add), 
          and updates its priority accordingly. */

    bool isEmpty();
    //const bool isEmpty() const;
       /* returns true if there are no elements on the heap. */

  private:

    int base; //stores the d-ary base value      
    int total; //total node additions

    std::vector<Node*> min_heap; //array storing nodes by priority order in the minheap
    std::vector<int> position_map; //array mapping nodes order of insertion to their current position in the heap

    //T& operator<(const T& other); //if existing operator doesn't work, overload it.

    int parent(int pos); //get parent location
    int child(int pos, int count); //get child location

    void swapNodes(Node* node1, Node* node2, int pos1, int pos2); //swap nodes + update maps
    int smallestChild(int pos); //find smallest child

    void bubbleUp(int pos); //heap helpers
    void trickleDown(int pos); //heap helpers
};


template<typename T>
MinHeap<T>::MinHeap(int d) {

  if (d >= 2){
    base = d;
    total = 0;
  }
  else {
    throw std::logic_error("Please provide a valid minHeap base value.");
  }
}


template<typename T>
MinHeap<T>::~MinHeap() {

  for (size_t i = 0; i < min_heap.size(); i++) {
    delete min_heap[i];
  }
  //clear anything else?
}


template<typename T>
int MinHeap<T>::add(T item, int priority) {

  Node* new_node = new Node(item, priority, total); 
  //create pointer to node
  min_heap.push_back(new_node); //add node to heap
  position_map.push_back((int)min_heap.size()-1); //size corresponds to order inserted 

  bubbleUp((int)min_heap.size()-1); 

  total++;
  return total-1;
}


template<typename T>
T& MinHeap<T>::peek() {

  if (isEmpty()) {
    throw std::logic_error("MinHeap is empty!");
    //can't peek empty minheap
  }
  else {
    return min_heap[0]->item;
    //return top item
  }
}


template<typename T>
void MinHeap<T>::remove() {

  if (!isEmpty()){

    swapNodes(min_heap[0], min_heap[(int)min_heap.size()-1], 0, (int)min_heap.size()-1);
    //swap first and last nodes
    position_map[min_heap[min_heap.size()-1]->index] = -1;
    //set positoin map value to invalid index
    delete min_heap[min_heap.size()-1];
    //delete allocated memory
    min_heap.pop_back();
    //pop removed node
    trickleDown(0);
    //trickle down top node
  }
}


template<typename T>
void MinHeap<T>::update(int nth, int priority) {

  if (nth < 0 || nth >= total) {return;}
  //if nth is out of bounds
  int pos = position_map[nth]; 
  //get min_heap position
  if (pos < 0 || pos >= (int)min_heap.size()) {return;}
  //if position is out of bounds
  min_heap[pos]->priority = priority; 
  //update node priority

  if (pos >= 0 && pos < (int)min_heap.size()) {

    if (min_heap[pos]->priority <= min_heap[parent(pos)]->priority) {
      //if parent node has lesser priority
      bubbleUp(pos);
    }

    if (child(pos, 0) < (int)min_heap.size()) {
    //check if child exists
      if (min_heap[pos]->priority >= min_heap[smallestChild(pos)]->priority) {
        //if child node has lesser priority
          trickleDown(pos);
      }   
    }
  } 
}


template<typename T>
bool MinHeap<T>::isEmpty() {

  if (min_heap.size() == 0){
    return true;
    //is empty
  }
  else {
    return false;
    //is not empty
  }
}


template<typename T>
int MinHeap<T>::parent(int pos) {
  return (pos-1)/base;
  //calculate the parent position
}


template<typename T>
int MinHeap<T>::child(int pos, int count) {
  return base*pos+count+1;
  //count is indexed at 0, thus count 0 is first child, count 1 is second, etc.
}


template<typename T>
void MinHeap<T>::swapNodes(Node* node1, Node* node2, int pos1, int pos2) {

  position_map[node1->index] = pos2;
  position_map[node2->index] = pos1;
  //update the position map

  T temp_item = node1->item;
  int temp_priority = node1->priority;
  int temp_index = node1->index;
  //create temp variables

  node1->item = node2->item;
  node1->priority = node2->priority;
  node1->index = node2->index;
  //swap node 1

  node2->item = temp_item;
  node2->priority = temp_priority;
  node2->index = temp_index;
  //swap node 2
}


template<typename T>
int MinHeap<T>::smallestChild(int pos) {

  Node* min = min_heap[child(pos, 0)];
  int index = 0;
  //set min variables

  for (int i=1; i < base; i++) {

    if (child(pos, i) >= (int)min_heap.size()) {
    //if there are not max children
      break;
    }

    Node* nextchild = min_heap[child(pos, i)];

    if (min->priority == nextchild->priority) {
      //if both children have same priority
      if (min->item > nextchild->item) {
        //item value is less or equal to min
        min = nextchild;
        index = i;
      }
    }

    else if (min->priority > nextchild->priority) {
      //if next child has smaller priority
      min = nextchild;
      index = i;
    }
  }
  return child(pos, index);
}


template<typename T>
void MinHeap<T>::bubbleUp(int pos) {

  if (pos > 0 && pos < (int)min_heap.size()) {
    //if not root node and pos is in range

    if (min_heap[pos]->priority < min_heap[parent(pos)]->priority) {
      //if child node has lesser priority
      swapNodes(min_heap[pos], min_heap[parent(pos)], pos, parent(pos));
      bubbleUp(parent(pos));
    }

    else if(min_heap[pos]->priority == min_heap[parent(pos)]->priority) {
      //if same priority, do a tiebreaker
      if (min_heap[pos]->item < min_heap[parent(pos)]->item) {
        swapNodes(min_heap[pos], min_heap[parent(pos)], pos, parent(pos));
        bubbleUp(parent(pos)); 
      }
    }
  }
}


template<typename T>
void MinHeap<T>::trickleDown(int pos) {

  if (pos >= 0 && pos < (int)min_heap.size()-1 && child(pos,0) < (int)min_heap.size()) {
    //if pos is in range and there exists a child node

    if (min_heap[pos]->priority > min_heap[smallestChild(pos)]->priority) {
      //if child node has lesser priority
      swapNodes(min_heap[pos], min_heap[smallestChild(pos)], pos, smallestChild(pos));
      trickleDown(smallestChild(pos));
    }

    else if(min_heap[pos]->priority == min_heap[smallestChild(pos)]->priority) {
      //if same priority, do a tiebreaker
      if (min_heap[pos]->item > min_heap[smallestChild(pos)]->item) {
        swapNodes(min_heap[pos], min_heap[smallestChild(pos)], pos, smallestChild(pos));
        trickleDown(smallestChild(pos)); 
      }
    }
  }
}