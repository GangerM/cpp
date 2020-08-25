#include <iostream>
#include "json.hpp"

#include "priorityqueue.h"

PriorityQueue::PriorityQueue(std::size_t max_size) :
	nodes_(max_size + 1, KeyValuePair()), max_size_(max_size), size_(0) {}


bool HasParent(size_t i) {
    return i > 1;
}
size_t Parent(size_t i) {
    return  i/ 2;
}
// compare the child key with parent key
bool PriorityQueue::LessThan(size_t child, size_t parent) {
    return nodes_[child].first < nodes_[parent].first;
}
// get left and right child indicies
size_t LeftChild(size_t i) {
    return 2 * i ;
}
size_t RightChild(size_t i) {
    return 2 * i + 1;
}

bool PriorityQueue::InBounds(size_t i) {
    return i < size_ + 1;
}

void PriorityQueue::insert(Key k) {
	insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv) {
    // push back the item into the vector items
    nodes_[++size_] = kv;
    // make the vector items into a heap structure
    heapifyUp(size_);

}


KeyValuePair PriorityQueue::min() {
    return nodes_[1];
}

KeyValuePair PriorityQueue::removeMin() {
    if (size_ == 0)
        throw std::underflow_error(
                "Empty priority queue!");

    KeyValuePair root = nodes_[1];

    nodes_[1] = nodes_[size_--];
    nodes_.erase(nodes_.end());
    heapifyDown(1);
    // std::cout << "new root after heapify down: " << nodes_[1].first << std::endl;



    return root;
}

bool PriorityQueue::isEmpty() const {
	if(size_ == 0) return true;
	return false;
}

nlohmann::json PriorityQueue::JSON() const {
	nlohmann::json result;
  for (size_t i = 1; i <= size_; i++) {
      nlohmann::json node;
      KeyValuePair kv = nodes_[i];
      node["key"] = kv.first;
      node["value"] = kv.second;
      if (i != ROOT) {
          node["parent"] = std::to_string(i / 2);
      }
      if (2 * i <= size_) {
          node["leftChild"] = std::to_string(2 * i);
      }
      if (2 * i + 1 <= size_) {
          node["rightChild"] = std::to_string(2 * i + 1);
      }
      result[std::to_string(i)] = node;
  }
  result["metadata"]["max_size"] = max_size_;
  result["metadata"]["size"] = size_;
	return result;
}

void PriorityQueue::heapifyUp(size_t i) {
// see if n has a parent and if its parent is smaller than it
    while (HasParent(i) && LessThan(i, Parent(i))) {
        std::swap(nodes_[Parent(i)], nodes_[i]);
        i = Parent(i);
    }
}


void PriorityQueue::heapifyDown(size_t i) {
    while (InBounds(LeftChild(i))) {
        size_t child = LeftChild(i);
        if (InBounds((RightChild(i)))
            && LessThan(RightChild(i), LeftChild(i)))
            child = RightChild(i);
        if (LessThan(child, i)) {
            // std::cout << "bigger parent: " << nodes_[i].first << "\nsmallerchild: " << nodes_[child].first << std::endl;
            std::swap(nodes_[child], nodes_[i]);
        }
        else
            break;
        i = child;
    }
}

void PriorityQueue::removeNode(size_t i) {
    // swap root with end
    nodes_[i] = nodes_[size_--];
    // delete old root
    nodes_.erase(nodes_.end());
    if (nodes_[i].first < nodes_[Parent(i)].first) heapifyUp(i);
    else heapifyDown(i);
}

Key PriorityQueue::getKey(size_t i) {
    return nodes_[i].first;
}


/*
int main() {

    PriorityQueue test(100);
    test.insert(30);
    test.insert(20);
    test.insert(10);
    test.insert(11);
    test.insert(100);
    test.insert(2);
    test.insert(50);
    test.insert(150);
    test.insert(5);
    test.insert(250);
   test.insert(350);
    test.insert(540);
    test.insert(550);


    test.PrintTree();
    std::cout << test.removeMin().first << std::endl;
    std::cout << test.removeMin().first << std::endl;
    std::cout << test.removeMin().first << std::endl;
    std::cout << test.removeMin().first << std::endl;
    std::cout << test.removeMin().first << std::endl;
    std::cout << test.removeMin().first << std::endl;
    std::cout << test.removeMin().first << std::endl;
    std::cout << test.removeMin().first << std::endl;
    std::cout << test.removeMin().first << std::endl;

    return 0;

}
 */
