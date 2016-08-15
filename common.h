#pragma once

using uint = unsigned int;

inline void Print(int a[], size_t as)
{
  std::cout << "array=> ";
  for(size_t i = 0; i <= as; i++ ) {
    std::cout<< a[i] <<", ";
  }
  std::cout << std::endl;
}


inline void Print(const std::vector<int> &a)
{
  std::cout << "elements=> ";
  for(auto i : a) {
    std::cout<< i <<", ";
  }
  std::cout << std::endl;
}


inline void swap(int &a, int &b)
{
 a = a + b;
 b = a - b;
 a = a - b;
}


