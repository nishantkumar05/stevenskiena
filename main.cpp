#include <iostream>
#include <cstdlib>
#include <ctime>
#include "BinarySearch.hpp"

int main()
{
  BinarySearch bst;
  bst.Insert(20);
  bst.Insert(30);
  bst.Insert(15);
  bst.Insert(19);
  bst.Insert(8);
  bst.Insert(9);
  bst.Insert(25);
  bst.Insert(22);
  bst.Insert(26);
  bst.Insert(27);
  bst.Insert(6);
  bst.Insert(5);

//          20
//      15       30
//    8   19   25
//   6 9     22  26
//  5              27

// PreOrder =  5,6,8,9,15,19,20,22,25,26,27,30
  bst.PrintPreOrder();
// PostOrder = 20,15,8,6,5,9,19,30,25,22,26,27
  bst.PrintPostOrder();

 //Really loooong test
  srand(time(NULL));
  for(uint64_t i = 0; i < 32000 ; i++ )
  {
    int random_number = std::rand();
    bst.Insert(random_number);
  }
  bst.PrintPreOrder();
}
