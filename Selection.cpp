#include <iostream>
#include <vector>


void selection_main()
{
    std::vector<int> a = {88, 33, 44, 22, 11, 99, 111, 12, 15, 13, 182, 64, 89, 63, 201}; 
    for(int i = 0; i < a.size(); i++ ) {
        for(int j = i; j < a.size(); j++ ) {
            if(a[i] < a[j]) {
                a[i] = a[i] + a[j];
                a[j] = a[i] - a[j];
                a[i] = a[i] - a[j];
            }
        }
    }
    std::cout << "sorted vector=>";
    for(int i = 0; i < a.size(); i++){
        std::cout << a[i] << ", ";
    }
    std::cout << std::endl;
}

int main()
{
    selection_main();
}
