#include "BinarySearch.hpp"
#include <sys/time.h>

std::string get_current_time()
{
  timeval curTime;
  gettimeofday(&curTime, NULL);
  int milli = curTime.tv_usec / 1000;
  
  char buffer [80];
  strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&curTime.tv_sec));
  char currentTime[84] = "";
  sprintf(currentTime, "%s:%d", buffer, milli);

  return std::string(currentTime);
}

void BinarySearchTest()
{
  BinarySearch bst;

  std::cout << "32M Test" << std::endl ;
  std::cout << "BST::Insert starting (" << get_current_time() << ")" << std::endl ;
  srand(time(NULL));
  for(uint64_t i = 0; i < 32000000 ; i++ )
  {
    int random_number = std::rand();
    bst.Insert(random_number);
  }
  bst.Insert(2118671862);

  std::cout << "BST::Search starting (" << get_current_time() << ")" << std::endl ;
  std::cout << "Does it exist? =" << bst.Search(2118671862)<< std::endl;;
  std::cout << "BST::Search ending (" << get_current_time() << ")" << std::endl ;


  std::cout << "32K Test" << std::endl ;
  std::cout << "BST::Insert starting (" << get_current_time() << ")" << std::endl ;
  srand(time(NULL));
  for(uint64_t i = 0; i < 32000 ; i++ )
  {
    int random_number = std::rand();
    bst.Insert(random_number);
  }
  bst.Insert(90);
  //std::cout << "BST::PreOrder starting (" << get_current_time() << ")" << std::endl ;
  //bst.PrintPreOrder();
  std::cout << "BST::Search starting (" << get_current_time() << ")" << std::endl ;
  std::cout << "Does it exist? =" << bst.Search(90)<< std::endl;;
  std::cout << "BST::Search ending (" << get_current_time() << ")" << std::endl ;
}


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
