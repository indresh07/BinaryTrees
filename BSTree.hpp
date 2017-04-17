#ifndef BSTREE_HPP
#define BSTREE_HPP 1
#include "BinaryTree.hpp"
template <class Key, class Value>
class BSTree : public BinaryTree<Key, Value> {

/* Inherit as many functions as possible from BinaryTree.
 * Only override those where you can decrease the time complexity and where you absolutely need to do it.
 * Also make sure that all inherited functions work correctly in the context of a binary search tree.
 */
protected:
  int height(BinaryNode<Key, Value>* rt);
  int _size;
 public:
    Value get(const Key& key);
    /* Implement remove function that can delete a node in binary tree with given key. 
     */
    virtual void remove(const Key& key) ;
    /* Implement has function which will return true if the given key is present in binary tree 
     * otherwise return false.  
     */
    bool has(const Key& key) ;  
    /* Implement put function such that newly inserted node keep the tree balanced. 
     */ 
    virtual void put(const Key& key, const Value& value) ;
    /*
     *This method returns the minimum element in the binary tree.
     */
    Key minimum();
    /*
     * This method returns the maximum element in the binary tree.
     */
    Key maximum();
    /*
     *This method returns the successor, i.e, the next larget element in the
     *binary tree, after Key.
     */
    Key successor(const Key& key);
    /*
     * This method returns the predessor, ie, the next smallest element in the
     * binary tree, after Key.
     */
    Key predecessor(const Key& key);
    /*
     * This method returns the current height of the binary search tree.
     */
    virtual int getHeight();
    /*
     * This method returns the total number of elements in the binary search tree.
     */
    virtual int size();
    /*
     * This method prints the key value pairs of the binary search tree, sorted by
     * their keys.
     */
    virtual void print();
};

template<class Key, class Value>
Value BSTree<Key, Value>::get(const Key& key){

    BinaryNode<Key, Value> *iterator = this->root;

    while(iterator){
      if(iterator->key == key)
        return iterator->val;

      if(iterator->key > key)
        iterator = iterator->left;
      else
        iterator = iterator->right;
    }

    throw "Key does not exist.";
}

template<class Key, class Value>
void BSTree<Key, Value>::remove(const Key& key){

    BinaryNode<Key, Value> *iterator = this->root;
    BinaryNode<Key, Value> *delNode;

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
      if(iterator->parent->left == iterator)
        iterator->parent->left = NULL;
      else
        iterator->parent->right = NULL;

      delete iterator;
      _size--;
      return;
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
        _size--;
        return;
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
          _size--;
          return;
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
        _size--;
        return;
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
          _size--;
          return;
        }

        iterator = iterator->right;
      }
    }
}

template<class Key, class Value>
bool BSTree<Key, Value>::has(const Key& key){

  BinaryNode<Key, Value> *iterator = this->root;

  while(iterator){
    if(iterator->key == key)
      return true;

    if(iterator->key > key)
      iterator = iterator->left;
    else
      iterator = iterator->right;
  }

  return false;
}

template<class Key, class Value>
void BSTree<Key, Value>::put(const Key& key, const Value& value){

  BinaryNode<Key, Value> *iterator = this->root;

  if(this->root == NULL){
    this->root = new BinaryNode<Key,Value>(key, value);
    _size = 1;
    return;
  }

  BinaryNode<Key, Value> *newNode;
  newNode = new BinaryNode<Key, Value>(key, value);
  _size++;

  while(iterator){

    if(iterator->key == key){
      iterator->val = value;
      return;
    }

    if(iterator->key > key && !iterator->left){

      newNode->parent = iterator;
      iterator->left = newNode;
      return;
    }

    if(iterator->key < key && !iterator->right){

      newNode->parent = iterator;
      iterator->right = newNode;
      return;
    }

    if(iterator->key > key)
      iterator = iterator->left;
    else
      iterator = iterator->right;
  }
}

template<class Key, class Value>
Key BSTree<Key, Value>::minimum(){

  BinaryNode<Key, Value> *iterator = this->root;

  while(iterator){

    if(!iterator->left)
      return iterator->key;

    iterator = iterator->left;
  }

  throw "Binary search tree is empty.";
}

template<class Key, class Value>
Key BSTree<Key, Value>::maximum(){

  BinaryNode<Key, Value> *iterator = this->root;

  while(iterator){

    if(!iterator->right)
      return iterator->key;

    iterator = iterator->right;
  }

  throw "Binary search tree is empty.";
}

//complexity log(n)
template<class Key, class Value>
Key BSTree<Key, Value>::successor(const Key& key){

  BinaryNode<Key, Value> *iterator = this->root;

  //to find position of given key
  while(iterator){

    if(iterator->key == key)
      break;

    if(iterator->key > key)
      iterator = iterator->left;
    else
      iterator = iterator->right;
  }

  if(!iterator)
    throw "key does not exists.";

  //to find smallest node in right subtree
  if(iterator->right){
    iterator = iterator->right;

    while(iterator){
      if(!iterator->left)
        break;
      iterator = iterator->left;
    }
    
    if(!iterator)
      throw "No successor exists for given key.";

    return iterator->key;
  }//to traverse back if right subtree is empty
  else{

    while(iterator){
      if(iterator->key > key)
        return iterator->key;

      iterator = iterator->parent;
    }

    if(!iterator)
      throw "No successor exists for given key.";
  }
}

//complexity log(n)
template<class Key, class Value>
Key BSTree<Key, Value>::predecessor(const Key& key){

  BinaryNode<Key, Value> *iterator = this->root;

  //to find position of given key
  while(iterator){
    if(iterator->key == key)
      break;

    if(iterator->key > key)
      iterator = iterator->left;
    else
      iterator = iterator->right;
  }

  if(!iterator)
    throw "key does not exists.";

  //to find largest node in left subtree
  if(iterator->left){
    iterator = iterator->left;

    while(iterator){
      if(!iterator->right)
        break;
      iterator = iterator->right;
    }
    
    if(!iterator)
      throw "No predecessor exists for given key.";

    return iterator->key;
  }//to traverse back if left subtree is empty 
  else{

    while(iterator){
      if(iterator->key < key)
        return iterator->key;

      iterator = iterator->parent;
    }

    if(!iterator)
      throw "No predecessor exists for given key.";
  }
}

template<class Key, class Value>
int BSTree<Key, Value>::getHeight(){

  return height(this->root);
}

template<class Key, class Value>
int BSTree<Key, Value>::height(BinaryNode<Key, Value>* rt){
  if(!rt)
    return 0;

  int lHeight = height(rt->left);
  int rHeight = height(rt->right);

  return 1 + (lHeight > rHeight ? lHeight : rHeight); 
}

template<class Key, class Value>
int BSTree<Key, Value>::size(){

  if(!this->root)
    return 0;

  return _size;
}

template<class Key, class Value>
void BSTree<Key, Value>::print(){
  this->print_in_order();
}

#endif /* ifndef BSTREE_HPP */