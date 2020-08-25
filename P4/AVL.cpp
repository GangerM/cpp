#include "AVL.h"

#include <cassert>
#include <iostream>
#include <string>
#include <queue>

#include "json.hpp"


BSTNode::BSTNode(int key) :
	key_(key),
	parent_(std::weak_ptr<BSTNode>()),
	left_(nullptr),
	right_(nullptr) {}

BSTNode::BSTNode(int key, std::weak_ptr<BSTNode> parent) :
	key_(key),
	parent_(parent),
	left_(nullptr),
	right_(nullptr) {}

bool BSTNode::IsLeaf() const {
	return left_ == nullptr && right_ == nullptr;
}

bool BSTNode::HasLeftChild() const {
	return left_ != nullptr;
}

bool BSTNode::HasRightChild() const {
	return right_ != nullptr;
}

void BSTNode::DeleteChild(std::shared_ptr<BSTNode> v) {
	if (left_ == v) {
		left_ = nullptr;
	} else if (right_ == v) {
		right_ = nullptr;
	} else {
		std::cerr << "BSTNode::DeleteChild Error: non-child passed as argument\n";
		exit(EXIT_FAILURE);
	}
}

void BSTNode::ReplaceChild(std::shared_ptr<BSTNode> v, std::shared_ptr<BSTNode> u) {
	if (left_ == u || right_ == u) {
		std::cerr << "BSTNode::ReplaceChild Error: child passed as replacement\n";
	}
	if (left_ == v) {
		left_ = u;
		u->parent_ = v->parent_;
	} else if (right_ == v) {
		right_ = u;
		u->parent_ = v->parent_;
	} else {
		std::cerr << "BSTNode::ReplaceChild Error: non-child passed as argument\n";
		exit(EXIT_FAILURE);
	}
}

BST::BST() : root_(nullptr), size_(0) {}

int BST::Height(std::shared_ptr<BSTNode> currentNode){
	int  l = 0, r = 0;
	if (currentNode == root_) return 0;

	if (currentNode->HasLeftChild()) l = Height(currentNode->left_);
	if (currentNode->HasRightChild()) r = Height(currentNode->right_);

	if (l > r) return ++l;
	else return ++r;
}
	
int BST::BalanceFactor(std::shared_ptr<BSTNode> currentNode){
	int bf = 0;
	int right = 0;
	int left = 0;
	if (currentNode->right_ != nullptr) right = Height(currentNode->right_);
	if (currentNode->left_ != nullptr) left = Height(currentNode->left_);
	bf = right - left;
	return bf;
	
		return 0;
}	

void BST::RightRight(std::shared_ptr<BSTNode> currentNode){
	std::cout << currentNode->GetKey() <<  "RR \n";
	std::shared_ptr<BSTNode> newNode = currentNode->left_;
	std::shared_ptr<BSTNode> currNode = currentNode;
	std::shared_ptr<BSTNode> grandp;
	
	if (currentNode->parent_.lock()->parent_.lock() != nullptr)  grandp = currentNode->parent_.lock()->parent_.lock();
	if (currentNode->left_ != nullptr) {
	       	//currentNode->parent_.lock()->right_ = currentNode->left_; // on rotation LEFT, LEFT child becomes right child of old parent
		currentNode->left_->parent_ = currentNode->parent_; // the PARENT of LEFT child updated to be its old grandparent
	}
	else currentNode->parent_.lock()->right_ = nullptr;   // otherwise if there is NO LEFT child, then the old parent has NO RIGHT CHILD
	
	//std::cout << currentNode->GetKey() << "\n";

	currNode->left_ = currNode->parent_.lock();	// parent is now the left child of our current node
	if (currNode->left_ == root_) root_ = currentNode;   //  If its new root , update root
	if (grandp != nullptr){
	       	currNode->parent_ = grandp;  // update cur parent to be the grandparent
		//grandp->right_ = currentNode;
	}
	else currNode->parent_.reset();  // otherwise make cur parent null (when its root)
	currNode->left_->parent_ = currNode; // update old parents' new parent to be current node
	currNode->left_->right_ = newNode;
}
void BST::LeftLeft(std::shared_ptr<BSTNode> currentNode){
	std::cout << currentNode->GetKey() << " LL \n";
	std::shared_ptr<BSTNode> y;
	std::shared_ptr<BSTNode> x;
	
	if (currentNode->right_ != nullptr) x = currentNode->right_;
	if (currentNode->parent_.lock() != nullptr)  y = currentNode->parent_.lock();
	
	if (currentNode->right_ != nullptr) {
	       	// currentNode->parent_.lock()->left_ = currentNode->right_;
		currentNode->right_->parent_ = currentNode->parent_;
	}
	// else currentNode->parent_.lock()->left_ = nullptr;

	if (y != nullptr) currentNode->right_ = y;
	if (y == root_) root_ = currentNode;
	if (y->parent_.lock() != nullptr) currentNode->parent_ = y->parent_; 
	else currentNode->parent_.reset();
	y->parent_ = currentNode;

	if (x != nullptr) y->left_ = x;
	else y->left_ = nullptr;
	
}
void BST::RightLeft(std::shared_ptr<BSTNode> currentNode){
	currentNode = (currentNode->right_ != nullptr) ? currentNode->right_ : currentNode->left_;	// set current node to the child of the current currentnode

//	std::cout << "RL " << currentNode->GetKey() << std::endl;

	std::shared_ptr<BSTNode> parent = currentNode->parent_.lock(), gparent = parent->parent_.lock();	// parent = og param, gparent = params parent
	
	currentNode->parent_.lock() = (gparent == root_) ? nullptr : gparent->parent_.lock();	// set parent to gparents parent
	if (currentNode->parent_.lock() != nullptr) currentNode->parent_.lock()->right_ = currentNode;

	if (gparent == root_) {
		root_ = currentNode;
	 	currentNode->parent_.lock();
	}
	currentNode->left_ = gparent, currentNode->right_ = parent;

	gparent->parent_ = currentNode, parent->parent_ = currentNode;

	std::cout << "left: " << gparent->GetKey() << " parent: " << currentNode->GetKey() << " right: " << parent->GetKey() << "\n";
}

void BST::LeftRight(std::shared_ptr<BSTNode> currentNode){  // current = 3
	std::cout << currentNode->GetKey() << " LR " << std::endl;
	std::shared_ptr<BSTNode> parent = currentNode->parent_.lock(); // parent = 8
	std::shared_ptr<BSTNode> right = currentNode->right_; // child = 4
	std::shared_ptr<BSTNode> gparent;
	std::shared_ptr<BSTNode> rightleft;
	if (parent->parent_.lock() != nullptr)  gparent = parent->parent_.lock(); // gparent = 14
	else root_ = right;  // renaming of root taken care of if this is the case
	if (right->left_ != nullptr) rightleft = right->left_; // carrying over left child basically taken care of

	currentNode->parent_.lock() = right; // 3's new parent is 4
	right->left_ = currentNode; //4's left child is now 3

	right->right_ = parent; // 4's right child is now 8
	parent->parent_.lock() = right;  // 8's dad is now 4

	if (gparent != nullptr) {
		right->parent_.lock() = gparent; // 4's gparent is 14
		gparent->left_ = right;
	}
	else right->parent_.reset(); //otherwise make it null bc its the new root 
	
	currentNode->right_ = rightleft; // carry over left child 
	
	
}

void BST::Insert(int key) {
	std::shared_ptr<BSTNode> inserted;
	
	
	if (root_ == nullptr) {
		root_ = std::make_shared<BSTNode>(key);
		size_++;
		return;
	}
	std::shared_ptr<BSTNode> currentNode = root_, lastNode = nullptr;
	while (currentNode != nullptr) {
		lastNode = currentNode;
		// std::cout << "current key: " << lastNode->GetKey() << "bal fac: " << BalanceFactor(lastNode) << std::endl;
		currentNode = (key < currentNode->key_) ?
			currentNode->left_ : currentNode->right_;
	}
	if (key < lastNode->key_) {
		lastNode->left_ = std::make_shared<BSTNode>(key, lastNode);
		inserted = lastNode->left_;
		
	} else {
		lastNode->right_ = std::make_shared<BSTNode>(key, lastNode);
		inserted = lastNode->right_;
	
	}
	size_++;
	bool unbalanced = true;
	int root = 0;
	while (unbalanced){
	
		if (inserted != root_) inserted = inserted->parent_.lock();
		else root = 1;
		int lbf = 0, rbf = 0;
		int bf = BalanceFactor(inserted);
		if (inserted->left_ != nullptr) lbf = BalanceFactor(inserted->left_);
		if (inserted->right_!= nullptr) rbf = BalanceFactor(inserted->right_);
		// std::cout << "bf " << bf << "\n";

		bool l = false;
		if (bf < -1) l = true;

		if (bf > 1 || bf < -1){
			if (l){		// if its L-L or L-R
				std::cout << "INSERTED.LEFT " << inserted->left_->GetKey() << std::endl;
				if (lbf > 0) LeftRight(inserted->left_);
				else LeftLeft(inserted->left_);
			} else {	// if its R-R or R-L
				if (rbf < 0) RightLeft(inserted->right_);
				else RightRight(inserted->right_);
			}
		}
		if (root == 1) unbalanced = false;
			
	}


}

bool BST::Delete(int key) {
	std::shared_ptr<BSTNode> currentNode = root_;
	while (currentNode != nullptr) {
		if (currentNode->key_ == key) {
			if (currentNode->IsLeaf()) {
				DeleteLeaf(currentNode);
			} else if (currentNode->left_ == nullptr) {
				assert(currentNode->right_ != nullptr);
				std::shared_ptr<BSTNode> parent = currentNode->parent_.lock();
				parent->ReplaceChild(currentNode, currentNode->right_);
				size_--; assert(size_ >= 0);
			} else if (currentNode->right_ == nullptr) {
				assert(currentNode->left_ != nullptr);
				std::shared_ptr<BSTNode> parent = currentNode->parent_.lock();
				parent->ReplaceChild(currentNode, currentNode->left_);
				size_--; assert(size_ >= 0);
			} else {
				currentNode->key_ = DeleteMin(currentNode);
			}
		}
		currentNode = (key < currentNode->key_) ?
			currentNode->left_ : currentNode->right_;
	}
	return false;
}

int BST::DeleteMin() {
	return DeleteMin(root_);
}


void BST::DeleteLeaf(std::shared_ptr<BSTNode> currentNode) {
	std::shared_ptr<BSTNode> parent = currentNode->parent_.lock();
	if (parent == nullptr) {
		// Delete root
		root_ = nullptr;
		size_--; assert(size_ == 0);
	} else {
		if (parent->right_ == currentNode) {
			parent->right_ = nullptr;
		} else if (parent->left_ == currentNode) {
			parent->left_ = nullptr;
		} else {
			std::cerr << "BST::DeleteLeaf Error: inconsistent state\n";
		}
		size_--; assert(size_ >= 0);
	}
}

int BST::DeleteMin(std::shared_ptr<BSTNode> currentNode) {
	std::shared_ptr<BSTNode> lastNode = nullptr;
	while (currentNode != nullptr) {
		lastNode = currentNode;
		currentNode = currentNode->left_;
	}
	int result = lastNode->key_;
	std::shared_ptr<BSTNode> parent = lastNode->parent_.lock();
	if (parent == nullptr) {
		// lastNode is root
		if (lastNode->right_ != nullptr) {
			root_ = lastNode->right_;
			lastNode->right_->parent_.reset();
		} else {
			root_ = nullptr;
		}
	} else {
		// lastNode under the root
		if (lastNode->right_ != nullptr) {
			parent->left_ = lastNode->right_;
			lastNode->right_->parent_ = parent;
		} else {
			parent->left_ = nullptr;
		}
  }
	size_--; assert(size_ >= 0);
	return result;
}

size_t BST::size() const {
	return size_;
}

bool BST::empty() const {
	return size_ == 0;
}

bool BST::Find(int key) const {
	std::shared_ptr<BSTNode> currentNode = root_;
	while (currentNode != nullptr) {
		if (currentNode->key_ == key) {
			return true;
		}
		currentNode = (key < currentNode->key_) ?
			currentNode->left_ : currentNode->right_;
	}
	return false;
}

std::string BST::JSON() const {
	nlohmann::json result;
	std::queue< std::shared_ptr<BSTNode> > nodes;
	if (root_ != nullptr) {
		std::cout << root_->key_ << "\n";
		result["root"] = root_->key_;
		nodes.push(root_);
		while (!nodes.empty()) {
			auto v = nodes.front();
			nodes.pop();
			std::string key = std::to_string(v->key_);
			if (v->left_ != nullptr) {
				result[key]["left"] = v->left_->key_;
				nodes.push(v->left_);
			}
			if (v->right_ != nullptr) {
				result[key]["right"] = v->right_->key_;
				nodes.push(v->right_);
			}
			if (v->parent_.lock() != nullptr) {
				result[key]["parent"] = v->parent_.lock()->key_;
			} else {
				result[key]["root"] = true;
			}
		}
	}
	result["size"] = size_;
	return result.dump(2) + "\n";
}

int main(){
	BST tree;
	tree.Insert(11);
	tree.Insert(2);
	tree.Insert(20);
	tree.Insert(25);
	tree.Insert(22);
	std::cout << tree.JSON();
	return 1;
}
