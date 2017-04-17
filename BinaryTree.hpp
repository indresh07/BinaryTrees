#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP 1

#define DEFAULT_KEY 0
#define DEFAULT_VAL 0

#include "queue.hpp"

using namespace std;
using namespace ind;

template<class Key, class Value>
class BinaryNode
{
public:
	Key key;
	Value val;
	BinaryNode<Key,Value> *left, *right, *parent;
	int color;
    /*Default constructor. Should assign the default value to key and value
     */
	BinaryNode();
	/*This contructor should assign the key and val from the passed parameters
     */
	BinaryNode(Key key, Value value);
};

template<class Key, class Value>
BinaryNode<Key, Value>::BinaryNode(){
	this->key = DEFAULT_KEY;
	val = (Value)DEFAULT_VAL;
	left = NULL;
	right = NULL;
	parent = NULL;
}

template<class Key, class Value>
BinaryNode<Key, Value>::BinaryNode(Key key, Value value){
	this->key = key;
	val = value;
	left = NULL;
	right = NULL;
	parent = NULL;
}

template<class Key, class Value>
class BinaryTree
{
	void print_in_order(const BinaryNode<Key, Value>* rt);
	void print_pre_order(const BinaryNode<Key, Value>* rt);
	void print_post_order(const BinaryNode<Key, Value>* rt);
	/* You can implement your own helper functions whenever required.
	 */
protected:
	BinaryNode<Key,Value> * root;

public:
	BinaryTree();
	~BinaryTree();
	  /* Implement get function to retrieve the value corresponding to given key in binary tree.
	   */
	  Value get(const Key& key);
	  /* Implement remove function that can delete a node in binary tree with given key. 
	   */
	  virtual void remove(const Key& key) ;
	  /* Implement has function which will return true if the given key is present in binary tree 
	   * otherwise return false.  
	   */
	  virtual bool has(const Key& key) ;	
	  /* Implement put function such that newly inserted node keep the tree balanced. 
	   */	
	  virtual void put(const Key& key, const Value& value) ;
	  /*
	   *This method print all the key value pairs of the binary tree, as
	   *observed in an in order traversal.
	   */
	  virtual void print_in_order();
	  /*
	   *This method print all the key value pairs of the binary tree, as
	   *observed in an pre order traversal.
	   */
	  virtual void print_pre_order();
	  /*
	   *This method print all the key value pairs of the binary tree, as
	   *observed in a post order traversal.
	   */
	  virtual void print_post_order();
	  /*
	   *This method returns the minimum element in the binary tree.
	   */
	  virtual Key minimum();
	  /*
	   * This method returns the maximum element in the binary tree.
	   */
	  virtual Key maximum();
	  /*
	   *This method returns the successor, i.e, the next larget element in the
	   *binary tree, after Key.
	   */
	  virtual Key successor(const Key& key);
	  /*
	   * This method returns the predessor, ie, the next smallest element in the
	   * binary tree, after Key.
	   */
	  virtual Key predecessor(const Key& key);
};

template<class Key, class Value>
BinaryTree<Key, Value>::BinaryTree(){
	root = NULL;
}

template<class Key, class Value>
BinaryTree<Key, Value>::~BinaryTree(){
	
	if(root != NULL){
		queue<BinaryNode<Key, Value>* > nodes;
		BinaryNode<Key,  Value> *node;
		nodes.push(root);

		while(!nodes.empty()){
			node = nodes.pop();

			if(node->left != NULL)
				nodes.push(node->left);

			if(node->right != NULL)
				nodes.push(node->right);

			delete node;
		}
	}	
}

template<class Key, class Value>
Value BinaryTree<Key, Value>::get(const Key& key){

	if(root != NULL){
		queue<BinaryNode<Key, Value>* > nodes;
		BinaryNode<Key,  Value> *node;
		nodes.push(root);

		while(!nodes.empty()){
			node = nodes.pop();

			if(node->left != NULL)
				nodes.push(node->left);

			if(node->right != NULL)
				nodes.push(node->right);

			if(node->key == key)
				return node->val;
		}
	}	

	throw "Key does not exists.";
}

template<class Key, class Value> 
void BinaryTree<Key, Value>::remove(const Key& key){
	if(root != NULL){
		queue<BinaryNode<Key, Value>* > nodes;
		BinaryNode<Key, Value> *delNode, *node;
		nodes.push(root);

		while(!nodes.empty()){
			node = nodes.front();

			if(node->left != NULL)
				nodes.push(node->left);

			if(node->right != NULL)
				nodes.push(node->right);

			if(node->key == key){
				delNode = node;
				break;
			}

			nodes.pop();
		}

		if(!nodes.empty()){

			while(!nodes.empty()){
				node = nodes.pop();

				if(node->left != NULL)
					nodes.push(node->left);

				if(node->right != NULL)
					nodes.push(node->right);
		
				if(node->left == NULL && node->right == NULL){
					delNode->val = node->val;
					delNode->key = node->key;
					
					if(node->parent != NULL){
						if(node->parent->right == node)
							node->parent->right = NULL;
						else
							node->parent->left = NULL;
					}
					
					delete node;
					return;
				}
			}
		}
	}
} 

template<class Key, class Value> 
bool BinaryTree<Key, Value>::has(const Key& key){
	if(root != NULL){
		queue<BinaryNode<Key, Value>* > nodes;
		nodes.push(root);
		BinaryNode<Key, Value> *node;

		while(!nodes.empty()){
			node = nodes.pop();
			
			if(node->left != NULL)
				nodes.push(node->left);

			if(node->right != NULL)
				nodes.push(node->right);

			if(node->key == key)
				return true;
		}
	}

	return false; 
}

template<class Key, class Value> 
void BinaryTree<Key, Value>::put(const Key& key, const Value& value){

	static queue<BinaryNode<Key, Value>* > nodes;
	BinaryNode<Key, Value> *node;

	if(root == NULL){
		root = new BinaryNode<Key, Value>(key, value);
		nodes.push(root);
		return;
	}

	node = nodes.front();

	BinaryNode<Key, Value> *newNode;
	newNode = new BinaryNode<Key, Value>(key, value);
	newNode->parent = node;
	
	if(node->left == NULL){
		nodes.push(newNode);
		node->left = newNode;
		return;
	}

	if(node->right == NULL){
		nodes.push(newNode);
		node->right = newNode;
		nodes.pop();
		return;	
	}

} 

template<class Key, class Value> 
void BinaryTree<Key, Value>::print_in_order(){

	print_in_order(root);
}

template<class Key, class Value> 
void BinaryTree<Key, Value>::print_in_order(const BinaryNode<Key, Value>* rt){

	if(rt != NULL){

		print_in_order(rt->left);
		cout<<"["<<rt->key<<"] : "<<rt->val<<"\n";
		print_in_order(rt->right);
	}
}

template<class Key, class Value> 
void BinaryTree<Key, Value>::print_pre_order(){

	print_pre_order(root);
}

template<class Key, class Value> 
void BinaryTree<Key, Value>::print_pre_order(const BinaryNode<Key, Value>* rt){

	if(rt != NULL){

		cout<<"["<<rt->key<<"] : "<<rt->val<<"\n";
		print_pre_order(rt->left);
		print_pre_order(rt->right);
	}
}

template<class Key, class Value> 
void BinaryTree<Key, Value>::print_post_order(){

	print_post_order(root);
}

template<class Key, class Value> 
void BinaryTree<Key, Value>::print_post_order(const BinaryNode<Key, Value>* rt){

	if(rt != NULL){

		print_post_order(rt->left);
		print_post_order(rt->right);
		cout<<"["<<rt->key<<"] : "<<rt->val<<"\n";
	}
}

template<class Key, class Value> 
Key BinaryTree<Key, Value>::minimum(){
	
	Key min;

	if(root != NULL){

		queue<BinaryNode<Key, Value>* > nodes;
		nodes.push(root);
		min = root->key;
		BinaryNode<Key, Value> *node;

		while(!nodes.empty()){
			node = nodes.pop();

			if(node->left != NULL)
				nodes.push(node->left);

			if(node->right != NULL)
				nodes.push(node->right);

			if(min > node->key)
				min = node->key;
		}

		return min;
	}
	else
		throw "Binary tree is empty.";

}

template<class Key, class Value> 
Key BinaryTree<Key, Value>::maximum(){
	Key max;

	if(root != NULL){

		queue<BinaryNode<Key, Value>* > nodes;
		nodes.push(root);
		max = root->key;
		BinaryNode<Key, Value> *node;

		while(!nodes.empty()){
			node = nodes.pop();

			if(node->left != NULL)
				nodes.push(node->left);

			if(node->right != NULL)
				nodes.push(node->right);

			if(max < node->key)
				max = node->key;
		}

		return max;
	}
	else
		throw "Binary tree is empty.";

}

template<class Key, class Value> 
Key BinaryTree<Key, Value>::successor(const Key& key){

	Key suc;
	bool init = true;

	if(root != NULL){

		queue<BinaryNode<Key, Value>* > nodes;
		nodes.push(root);
		BinaryNode<Key, Value> *node;

		while(!nodes.empty()){
			node = nodes.pop();

			if(node->left != NULL)
				nodes.push(node->left);

			if(node->right != NULL)
				nodes.push(node->right);

			if(node->key > key && (init || suc > node->key)){
				init = false;
				suc = node->key;
			}
		}

		if(init)
			throw "No successor exist for given key.";
	}
	else
		throw "Binary tree is empty.";

	return suc;
}

template<class Key, class Value> 
Key BinaryTree<Key, Value>::predecessor(const Key& key){

	Key pre;
	bool init = true;

	if(root != NULL){

		queue<BinaryNode<Key, Value>* > nodes;
		nodes.push(root);
		BinaryNode<Key, Value> *node;

		while(!nodes.empty()){
			node = nodes.pop();

			if(node->left != NULL)
				nodes.push(node->left);

			if(node->right != NULL)
				nodes.push(node->right);

			if(node->key < key && (init || pre < node->key)){
				init = false;
				pre = node->key;
			}
		}

		if(init)
			throw "No predecessor exist for given key.";
	}
	else
		throw "Binary tree is empty.";

	return pre;	
}

#endif /* ifndef BINARYTREE_HPP */
