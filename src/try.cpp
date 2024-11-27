#include <iostream>


int main(){
    using namespace std;
    
    int **matrix=nullptr;
    int rows=0, columns=0;
    cin>>rows;
    cin>>columns;
    matrix = new int*[rows];
    for (int i=0;i<rows;i++){
        matrix[i]=new int[columns];
    }
    for (int i=0;i<rows;i++){
        for (int j=0;j<columns;j++){
            cin>>matrix[i][j];
        }
    }
    for (int i=0;i<rows;i++){
        for (int j=0;j<columns;j++){
            cout<<matrix[i][j]<<" ";
        }
    cout<<endl;
    }
    for (int i=0;i<rows;i++){
        delete matrix[i];
    }
    delete matrix;
    return 0;
}