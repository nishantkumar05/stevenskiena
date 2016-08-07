#include <iostream>
#include <vector>
#include "common.h"

/*
Syntax:
- function signature incorrect

Semantic:
- int &x = i; x = b; expected b to change reference but it changes value of i instead
- Scope resolution within template class => Heap<int>::HeapType::minHeap. Template is not a class, template-specialization class is
   $ g++ -std=c++11 HeapSort.cpp                                                                                                                                            
   HeapSort.cpp:132:18: error: 'Heap' is not a class, namespace, or scoped enumeration
   Heap<int> h(a, Heap::HeapType::minHeap);
                 ^

- Heapify logic totally incorrect 
*/

/*Time-to-develop from scratch = 6hrs (max heapify logic)*/

/*
Max Heapify
i/p = 30, 50, 22, 4, 2, 3, 19, 45, 88, 66, 36, 39, 64, 87, 63, 32, 14, 43, 89, 34, 99
o/p = 99, 89, 87, 66, 88, 39, 64, 32, 45, 50, 36, 22, 3, 19, 63, 30, 14, 43, 4, 34, 2, 
*/

/*
LOGIC NOTES:
  Most important logic is to find left-child and right child element in array.
  left-child = 2i+1, where i= current element 
  e.g. in following array index for 50 is 1 so next left-tree root node index for 50 = 2 * 1 + 1 = 3 
    int a[] = {30, 50, 22, 4, 2, 3, 19, 45, 88, 66, 36, 39, 64, 87, 63, 32, 14, 43, 89, 34, 99};
              { 0,  1,  2, 3, 4, 5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  Therefore array index for root node of any element = (current element index - 1) / 2
*/

template<typename T>
class Heap
{
public:
  enum class HeapType
  {
    maxHeap,
    minHeap
  };

  Heap(const std::vector<T> &b, HeapType t = HeapType::maxHeap) : a(b), type(t)
  {
    Heapify();
  }


  //Get highest(or lowest) priority job from the printer spool
  T Pop()
  {
    T m = a[0]; 
    DeleteFromHeap(0);
    return m;
  }
  
  //Add printer job with priority p in spool
  void Push(T b)
  {
    a.push(a);
    Heapify();
  }


  void Sort()
  {
    Heapify();
  }

  void p()
  {
    Print(a);
  }
  
  
private:
  //Floyd heapify method
  void Heapify()
  {
    for(unsigned int i = 0; ((2*i)+1) < a.size(); i++) {
      unsigned int leftChild = ((2*i)+1); //see notes
      int *x = &a[leftChild];
      if(leftChild < a.size()-1) { //only one child?
        x = Compare(a[leftChild], a[leftChild+1]) ? &a[leftChild] : &a[leftChild+1];
      }
      if(Compare(*x, a[i])) {
        swap(*x, a[i]);
        //Bubble-up from here
        for(unsigned int j = i; j != 0;  ) {
          unsigned int root = (j <= 2) ? 0 : (j-1)/2;
          if(Compare(a[j], a[root])){
            swap(a[j], a[root]);
          }
          if(root == 0) {
            break;
          } else {
            j = root;
          }
        }
        i--;//After bubble-up you must start from same element again
      }
    }
  }

  bool Compare(T a, T b)
  {
    if( HeapType::minHeap == type) {
      return a < b;
    }
    //max heap default
    return a > b;
  }
  
  void DeleteFromHeap(int deleteIndex)
  {
    if(deleteIndex < a.size()) {
      a.erase(a.begin()+deleteIndex);
      Heapify();
    }
  }

private:
  std::vector<T> a;
  HeapType type;
};

int main(void)
{
  std::vector<int> a =  {30, 50, 22, 4, 2, 3, 19, 45, 88, 66, 36, 39, 64, 87, 63, 32, 14, 43, 89, 34, 99, 23};
  //std::vector<int> a =   {30, 50, 22, 4, 2, 3, 19, 45, 88, 66, 36, 39, 64, 87, 63, 32, 14, 43, 89, 34, 99};
  //subscript { 0,  1,  2, 3, 4, 5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  Print(a);
  Heap<int> h(a, Heap<int>::HeapType::minHeap);

  std::cout<< "Heapified()\n";
  h.p();

  h.Pop();
  std::cout << "Pop()\n";
  h.p();
}
