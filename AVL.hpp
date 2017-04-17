#ifndef AVL_HPP
#define AVL_HPP 1
#include "BSTree.hpp"
template <class Key, class Value>
class AVL : public BSTree<Key, Value> {
  /*
   * Inherit as much functionality as possible from the BSTree class.
   * Then provide custom AVL Tree functionality on top of that.
   * The AVL Tree should make use of as many BST functions as possible.
   * Override only those methods which are extremely necessary.
   */
  /*
   * Apart from that, your code should have the following four functions:
   * getBalance(node) -> To get the balance at any given node;
   * doBalance(node) -> To fix the balance at the given node;
   * rightRotate(node) -> Perform a right rotation about the given node.
   * leftRotate(node) -> Perform a left rotation about the given node.
   *
   * The signature of these functions are not provided in order to provide you
   * some flexibility in how you implement the internals of your AVL Tree. But
   * make sure these functions are there.
   */
  void rightRotate(BinaryNode<Key, Value>* node, const char loc);
  void leftRotate(BinaryNode<Key, Value>* node, const char loc);
  int getBalance(BinaryNode<Key, Value>* node);
  bool doBalance(BinaryNode<Key, Value>* node, const char loc);

public:

  void put(const Key& key, const Value& value);
  void remove(const Key& key);
};

template<class Key, class Value>
void AVL<Key, Value>::rightRotate(BinaryNode<Key, Value>* node, const char loc){
  // L.    /       R.   /
  //     node1         node
  //     /            /
  //  node         node1
  //   /              \
  //node2            node2
  BinaryNode<Key, Value> *node1 = node->left;
  BinaryNode<Key, Value> *node2;
  
  if(loc == 'L'){
    node->left = node1->right;
    node1->right = node;

    node1->parent = node->parent;
    node->parent = node1;

    if(node == this->root)
      this->root = node1;
    else
      node1->parent->left = node1;

  }
  else{
    node2 = node1->right;

    node->left = node2->right;
    node1->right = node2->left;
    node2->left = node1;
    node2->right = node;

    node2->parent = node->parent;
    node->parent = node2;
    node1->parent = node2;


    if(node == this->root)
      this->root = node2; 
    else
      node2->parent->left = node2;
  }
}

template<class Key, class Value>
void AVL<Key, Value>::leftRotate(BinaryNode<Key, Value>* node, const char loc){
  // R. \        L.  \
  //   node          node
  //      \            \
  //     node1        node1
  //       \          /
  //      node2     node2
  BinaryNode<Key, Value> *node1 = node->right;
  BinaryNode<Key, Value> *node2;
  
  if(loc == 'R'){
    node->right = node1->left;
    node1->left = node;

    node1->parent = node->parent;
    node->parent = node1;

    if(node == this->root)
      this->root = node1;
    else
      node1->parent->right = node1;
  }
  else{
    node2 = node1->left;

    node->right = node2->left;
    node1->left = node2->right;
    node2->right = node1;
    node2->left = node; 

    node2->parent = node->parent;
    node->parent = node2;
    node1->parent = node2;

    if(node == this->root)
      this->root = node2; 
    else
      node2->parent->right = node2;
  }
}

template<class Key, class Value>
int AVL<Key, Value>::getBalance(BinaryNode<Key, Value>* node){

  return this->height(node->left) - this->height(node->right);
}

template<class Key, class Value>
bool AVL<Key, Value>::doBalance(BinaryNode<Key, Value>* node, const char loc){

  int bal = getBalance(node);

  if(bal > 1){
    rightRotate(node, loc);
    return true;
  }

  if(bal < -1){
    leftRotate(node, loc);
    return true;
  }

  return false;
}

template<class Key, class Value>
void AVL<Key, Value>::put(const Key& key, const Value& value){

  BinaryNode<Key, Value> *iterator = this->root;
  char loc;

  if(!this->root){
    this->root = new BinaryNode<Key,Value>(key, value);
    this->_size = 1;
    return;
  }

  BinaryNode<Key, Value> *newNode;
  newNode = new BinaryNode<Key, Value>(key, value);
  this->_size++;

  while(iterator){

    if(iterator->key == key){
      iterator->val = value;
      return;
    }

    if(iterator->key > key && !iterator->left){

      newNode->parent = iterator;
      iterator->left = newNode;
      loc = 'L';
      break;
    }

    if(iterator->key < key && !iterator->right){

      newNode->parent = iterator;
      iterator->right = newNode;
      loc = 'R';
      break;
    }

    if(iterator->key > key)
      iterator = iterator->left;
    else
      iterator = iterator->right;
  }

  while(iterator){

    if(doBalance(iterator, loc)){
      return;
    }

    iterator = iterator->parent;
  }
}

template<class Key, class Value>
void AVL<Key, Value>::remove(const Key& key){

    BinaryNode<Key, Value> *iterator = this->root;
    BinaryNode<Key, Value> *delNode;
    char loc;

    //to find position of key
    while(iterator){
      if(iterator->key == key){
        delNode = iterator;
        break;
      }

      if(iterator->key > key)
        iterator = iterator->left;
      else
        iterator = iterator->right;
    }

    //when key does not exists
    if(!iterator)
      return;

    //when key is at leaf node
    if(!iterator->left && !iterator->right){
      if(iterator->parent->left == iterator){
        loc = 'L';
        iterator->parent->left = NULL;
      }
      else{
        loc = 'R';
        iterator->parent->right = NULL;
      }

      delete iterator;
      this->_size--;
      goto end;
    }

    //to find samllest node in right subtree
    if(iterator->right){
      iterator = iterator->right;

      //when root node in right subtree is smallest node
      if(!iterator->left){
        if(iterator->right){
          iterator->parent->left = iterator->right;
          iterator->right->parent = iterator->parent;
        }

        delNode->key = iterator->key;
        delNode->val = iterator->val;
        delNode->right = NULL;
        delete iterator;
        this->_size--;
        loc = 'R';
        goto end;
      }

      while(iterator){
        if(!iterator->left){

          if(iterator->right){
            iterator->parent->left = iterator->right;
            iterator->right->parent = iterator->parent;
          }

          delNode->key = iterator->key;
          delNode->val = iterator->val;
          iterator->parent->left = NULL;
          delete iterator;
          this->_size--;
          loc = 'L';
          goto end;
        }

        iterator = iterator->left;
      }
    }

    //to find largest node in left subtree
    if(iterator->left){
      iterator = iterator->left;

      //when root node in left subtree is largest node
      if(!iterator->right){
        if(iterator->left){
          iterator->parent->right = iterator->left;
          iterator->left->parent = iterator->parent;
        }

        delNode->key = iterator->key;
        delNode->val = iterator->val;
        delNode->left = NULL;
        delete iterator;
        this->_size--;
        loc = 'L';
        goto end;
      }

      while(iterator){
        if(!iterator->right){

          if(iterator->left){
            iterator->parent->right = iterator->left;
            iterator->left->parent = iterator->parent;
          }

          delNode->key = iterator->key;
          delNode->val = iterator->val;
          iterator->parent->right = NULL;
          delete iterator;
          this->_size--;
          loc = 'R';
          goto end;
        }

        iterator = iterator->right;
      }
    }

    end :

    iterator = delNode;

    while(iterator){

      if(doBalance(iterator, loc))
        return;

      iterator = iterator->parent;
  }
}






#endif /* ifndef AVL_HPP */