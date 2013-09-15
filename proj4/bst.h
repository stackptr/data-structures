/* bst.h
 * Corey Johns
 * COP4530 Fall 2012
 *
 * Defines a generic AVL tree class.
 */

#ifndef BST_H
#define BST_H

#include <iostream>

template<typename T>
class BST {
public:
  // Constructor, copy constructor, and destructor
  BST(): root (NULL){} // An empty BST has no root
  BST(const BST & rhs): root(NULL){ *this = rhs;}
  ~BST(){ makeEmpty(); }

  // Public functions that call private recursive functions
  const T& findMin() const{ return findMin(root)->data; }
  const T& findMax() const{ return findMax(root)->data; }
  bool contains(const T& x) const{ return contains(x, root);}
  void makeEmpty(){ makeEmpty(root); }
  void insert(const T& x){ insert(x, root); }
  void remove(const T& x){ remove(x, root); }
  void printTree() {
    if (isEmpty() )
      return;
    printTree(root,0);
  }

  bool isEmpty() const{ return root == NULL; }
  
  const BST& operator=(const BST& rhs){
    if( this != &rhs){
      makeEmpty();
      root = clone(rhs.root);
    }
    return *this;
  }

  void printPreorder(int n){
    if(isEmpty())
      return;
    printPreorder(root, n);
  }

private:
  // Define the node structure
  struct Node{
    T data;
    Node *left, *right;
    int height;

    Node(const T& d = T(), Node *lt = NULL, Node *rt = NULL, int h = 0)
    : data(d), left(lt), right(rt), height(h){}
  };

  Node *root;

  // Insert function
  void insert(const T& x, Node *& t) {
    if( t == NULL)
      t = new Node(x, NULL, NULL);
    else if( x < t->data){
      insert(x, t->left);
      if (height(t->left) - height(t->right) == 2){
        if( x < t->left->data)
          rotateWithLeftChild(t);
        else
          doubleWithLeftChild(t);
      }
    }
    else if( t->data < x){
      insert(x, t->right);
      if(height(t->right) - height(t->left) == 2){
        if( t->right->data < x)
          rotateWithRightChild(t);
        else
          doubleWithRightChild(t);
      }
    }
    else
      ;
      t->height = max( height( t->left ), height( t->right ) ) + 1;
  }

  void remove(const T& x, Node *& t){
    if( t == NULL)
      return;
    if( x < t->data)
      remove(x, t->left);
    else if( t-> data < x)
      remove(x, t->right);
    else if( t->left != NULL && t->right != NULL){
      t->data = findMin(t->right)->data;
      remove(t->data, t->right);
    }
    else {
      Node *old = t;
      t = (t->left != NULL) ? t->left : t->right;
      delete old;
    }
  }

  Node* findMin(Node *t) const{
    if(t == NULL)
      return NULL;
    if( t->left == NULL)
      return t;
    return findMin( t->left);
  }

  Node* findMax(Node *t) const{
    if(t == NULL)
      return NULL;
    if( t->right == NULL)
      return t;
    return findMax( t->right);
  }

  bool contains(const T& x, Node *t) const{
    if (t == NULL)
      return false;
    else if( x < t->data)
      return contains(x, t->left);
    else if( t->data < x)
      return contains(x, t->right);
    else
      return true;
  }

  void makeEmpty(Node *& t){
    if( t != NULL){
      makeEmpty(t->left);
      makeEmpty(t->right);
      delete t;
    }
    t = NULL;
  }

  Node* clone(Node *t) const{
    if( t == NULL)
      return NULL;
    
    return new Node(t->data, clone(t->left), clone(t->right), t->height);
  }
  
  int height( Node *t) const{
      return t == NULL ? -1 : t->height;
  }
  
  int max(int p1, int p2){
    return p1 > p2 ? p1 : p2;
  }
  
  void rotateWithLeftChild(Node *& k2){
    Node *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left),height(k2->right))+1;
    k1->height = max(height(k1->left),k2->height)+1;
    k2 = k1;
  }

  void rotateWithRightChild(Node *& k1){
    Node *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->right),height(k1->left))+1;
    k2->height = max(height(k2->right),k1->height)+1;
    k1 = k2;
  }

  void doubleWithLeftChild(Node *& k3){
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
  }

  void doubleWithRightChild(Node *& k1){
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
  }
  
  void padding(int n){
    for(int i = 0; i < n; i++)
      std::cout << "\t";
  }

  void printTree(Node *t, int level){
    if (t != NULL){
      printTree(t->right, level+1);
      padding(level);
      std::cout << t->data << std::endl;
      printTree(t->left, level+1);
    }
  }

  void printPreorder(Node *t, int n){
    if (t == root){
      printptr = n;
      //std::cout << "Pointer set to " << n << "\n";
    }
    //std::cout << "N=" << printptr << "\t";
    if(t != NULL && printptr > 0 ){
      std::cout << t->data << std::endl;
      printPreorder(t->left, --printptr);
      printPreorder(t->right, --printptr);
    }
    else {
      printptr++;
      //std::cout << "CONDITION NOT MET" << std::endl;
    }
  }

// Assignment specific functions
// Remove these for a truly generic BST class!
public:
  // NOTE: Only use when absolute sure x exists in BST!
  // i.e., use contains(x) before get(x)!
  T& get(const T& x){
    return get(x, root);
  }
  
  // Similar to get, but restructures the tree before returning the reference
  T& getAndUpdate(const T& x){
    return getAndUpdate(x, root);
  }

private:
  T& get(const T& x, Node *t){
    if( x < t->data)
      return get(x, t->left);
    else if( t->data < x)
      return get(x, t->right);
    else
      return t->data;
  }
  
  T& getAndUpdate(const T& x, Node *t){
    // Set parent / grandparent nodes
    if ( t == root)
      gparent = parent = NULL;
    else if (t == root->left || t == root->right){
      gparent = NULL;
      parent = root;
    }


    if( x < t->data){
      gparent = parent;
      parent = t;
      return getAndUpdate(x, t->left);
    }
    else if( t->data < x){
      gparent = parent;
      parent = t;
      return getAndUpdate(x, t->right);
    }
    else {
      // Data found, so perform rotations
      if(gparent != NULL && parent != NULL){
        swapNodes(t, parent);
        swapNodes(parent,gparent);
      } else if (parent != NULL){
        swapNodes(t, parent);
      }
      return t->data;
    }
  }
  
  void swapNodes(Node *n1, Node *n2){
    T temp = n1->data;
    n1->data = n2->data;
    n2->data = temp;
  }

  int printptr; // for printing
  Node *gparent, *parent; // for traversal with update


};
#endif
