#include "BinarySearch.hpp"

BinarySearch::node* BinarySearch::Search(const Data key, node* n)
{
  if( nullptr == n || key == n->key ) {
    return n;
  }
  if( key < n->key ) {
    return Search(key, n->left);
  }
  return Search(key,n->right);
}

bool BinarySearch::Search(const Data key)
{
  return !(Search(key,root) == nullptr);    
}

void BinarySearch::Insert2(const Data key)
{
  node* n = root;
  node* l = nullptr;

  while(n) {
    l = n;
    if(key == n->key ) {
      n->instances++;
      return;
    } else if( key < n->key ){
       n = n->left;
    }
    n = n->right;
  }
  n = new node;
  n->key = key;

  if( n->key < l->key ) l->left = n;
  else l->right = n;
}

void BinarySearch::InsertRecursive(const Data key, node* l, node* n)
{
  if( nullptr == n ) {
    n = new node;
    n->key = key;
    if( n->key < l->key ) l->left = n;
    else l->right = n;
    return;
  }
  if( key == n->key ) {
    n->instances++;
    return;
  }
  l = n;
  if( key < n->key ) {
    return InsertRecursive(key, l, n->left);
  }
  return InsertRecursive(key, l, n->right);
}

void BinarySearch::Insert(const Data key)
{
  //ITR2 - start1
  if(!root) {
    root = new node;
    root->key = key;
    return;
  }
  //ITR2 - end1
  InsertRecursive(key, root, root);
}

void BinarySearch::DeleteRecursive(const Data key, node* l, node* n)
{
  if( nullptr == n ) {
     return;
  }
  if( key == n->key ) {
    n->instances--;
    if(!n->instances) {
      if( n->key < l->key) {
        l->left = n->right;
      } else {
        l->right = n->right;
      }
      node* tmp = n->right;
      while(tmp->left) {
         tmp = tmp->left;
      }
      delete n;
    }
    return;
  }
  l = n;
  if( key < n->key ) {
    return DeleteRecursive(key, l, n->left);
  }
  return DeleteRecursive(key, l, n->right);
}

void BinarySearch::Delete(const Data key)
{  
  DeleteRecursive(key, root, root);
}

void BinarySearch::Delete(node* node)
{
   if(nullptr == node) {
     return;
   }
   Delete(node->left);
   delete node;
}

void BinarySearch::PrintPreOrderRecursive(node* node)
{
   if(nullptr == node) {
     return;
   }
   PrintPreOrderRecursive(node->left);
   std::cout << node->key << ",";
   PrintPreOrderRecursive(node->right);
}

void BinarySearch::PrintPostOrderRecursive(node* node)
{
   if(nullptr == node) {
     return;
   }
   std::cout << node->key << ",";
   PrintPostOrderRecursive(node->left);
   PrintPostOrderRecursive(node->right);
}

void BinarySearch::PrintPostOrder()
{
  std::cout << "PostOrder Traversal = ";
  PrintPostOrderRecursive(root);
  std::cout << std::endl;
}

void BinarySearch::PrintPreOrder()
{
  std::cout << "PreOrder Traversal = ";
  PrintPreOrderRecursive(root);
  std::cout << std::endl;
}
