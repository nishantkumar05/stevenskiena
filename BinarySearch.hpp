#pragma once
#include <iostream>
#include <memory>

/*
* 
*           Avg      Worst
* -------------------------
* Search    O(log n)   O(n)
* Insert    O(log n)   O(n) 
* Delete    O(log n)   O(n)
*
* - Worst case is for already sorted data (should use balanced trees in that case)
*/

using Data = uint64_t;


class BinarySearch
{
public:
  struct node
  {
    node() : left(nullptr), right(nullptr), key(0), instances(0) {}
    node* left;
    node* right;
    Data  key;
    uint64_t instances;
  };
  node* root;

private:
  node* Search(const Data key, node* node);
  void InsertRecursive(const Data key, node* l, node* n);
  void DeleteRecursive(const Data key, node* l, node* n);
  void PrintPreOrderRecursive(node* node);
  void PrintPostOrderRecursive(node* node);
  void Delete(node* node);

public:
  BinarySearch()
  {
    root = nullptr;
  }
  ~BinarySearch()
  {
     Delete(root);
  }
  bool Search(const Data key);
  void Insert(const Data key);
  void Insert2(const Data key);
  void Delete(const Data key);
  void PrintPreOrder();
  void PrintPostOrder();
//  void PrintInOrder();
};

void BinarySearchTest();
