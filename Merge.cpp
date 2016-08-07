#include <iostream>

void print(int a[], size_t s)
{
  std::cout << "array("<<s << ")=";
  for(int i = 0 ; i <= s; i++) {
    std::cout << a[i] << ",";
  }
  std::cout << std::endl;
}

void merge(int a[], size_t start, size_t mid, size_t end)
{
  int b[end+1];
  size_t max = (end - start); //total number of items  to be processed

  //take two counters i and j (place them at start) for two arrays to be merged
  size_t i = start;
  size_t j = mid+1 ;

  //run for total number of items to be processed and pick the element that is lesser between
  //the two arrays and place it in temporary array
  for(size_t k = 0; k<=max; k++) {
    //pick elements from the first if first array (start <-> mid) has elements left 
    // and the element is lesser than second array OR
    // second array has no elements left in it
    if((j > end) || ((i <= mid) && (a[i] < a[j]))) {
      b[k] = a[i++];
    } else{
      b[k] = a[j++];
    }
  }
  for(i=0; i<=max; i++, start++ ){
    a[start]=b[i];
  }
}

void sort(int a[], size_t start, size_t end)
{
  if(start == end) {
    return;
  }
  
  //calculate middle of array (array subscript pointing to middle of array)
  size_t mid = start + ((end - start) / 2);
  std::cout << "start:" <<start <<", mid:" <<mid<<",end:"<<end <<std::endl;

  sort(a, start, mid);
  sort(a, mid+1, end);
  merge(a, start, mid, end);
}

int main(void)
{
  int a[] = {30, 50, 22, 4, 2, 3, 19, 45, 88, 63, 36, 39, 64, 87, 63, 32, 14, 43, 89, 34, 99, 23};
  size_t as = sizeof(a)/sizeof(int);

  //Its easier to avoid a lot of coding confusion if you pass array index everywhere 
  //(dont mix array index vs array size)
  print(a, as-1);
 
  sort(a, 0, as-1);

  print(a, as-1);
  return 0;
}
