#include <iostream>
#include <cmath>
#include <iomanip>

namespace sides {
    double x, y, z;

}

void child_1(int n[]){
    for (int i=0; i<5;i++){
        std::cout<<n[i]<<std::endl; 

    }
}
void child_2(int* n){
    for (int i=0; i<5;i++){
        std::cout<<n[i]<<std::endl; 

    }
}

int main(){
    using namespace std;
    int n[5]={2, 3, 4, 5, 10};

    child_1(n);
    child_2(n);



    return 0;
}