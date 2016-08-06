#include <iostream>

// Syntax Errors: none! hurray!!!
// Symantic errors:
// - array size was wrong (used sizeof(a))
// - logical error j counter wasn't used comparison was wrong

void print(int a[], size_t s)
{
  std::cout << "array("<<s << ")=";
  for(int i = 0 ; i < s; i++) {
    std::cout << a[i] << ",";
  }
  std::cout << std::endl;
}

int main(void)
{
  int a[] = {30, 50, 22, 4, 2, 3, 19, 45, 88, 63, 36, 39, 64, 87, 63, 32, 14, 43, 89, 34, 99, 23};
  size_t as = sizeof(a)/sizeof(int);

  print(a, as);
 
  for(int i = 0 ; i < as ; i++) {
    int j = i;
    for(int k = j; k >= 0 ; k-- ) {
      if(a[k] > a[j]) {
         a[k] = a[k] + a[j];
         a[j] = a[k] - a[j];
         a[k] = a[k] - a[j];
         j--;
      }
    }
  }

  print(a, as);
  return 0;
}
