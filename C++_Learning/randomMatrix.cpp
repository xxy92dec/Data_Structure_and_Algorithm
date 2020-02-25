#include<iostream>
#include<stdlib.h>
#include <math.h>
#include <chrono> 
using namespace std;
using namespace std::chrono;


int** AssignMatrix(int size);
int** Naive(int** MatrixA,int** MatrixB, int size);

int main(){
   int maxnum = 4;
   for (int n = 1; n <= maxnum; n++){
      int** MatrixA;
      int** MatrixB;
      int size = pow(2,n);
      MatrixA = AssignMatrix(size);
      MatrixB = AssignMatrix(size);
      //Naive
      int** MatrixC1;
      MatrixC1 = Naive(MatrixA,MatrixB,size);
   } 
   return 0;  
}
    
int** AssignMatrix(int size){
   int** ObjectMatrix = new int*[size];
   for (int i = 0; i < size; i++) {
      ObjectMatrix[i] = new int[size];
   }
   for (int i = 0; i < size; i++){
      for (int j =0; j < size; j++){
         ObjectMatrix[i][j] = rand() % size + 1;
      }
   }
   return ObjectMatrix;
}

int** Naive(int** MatrixA, int** MatrixB, int size){
   int** ObjectMatrix = new int*[size];
   for (int n = 0; n < size; n++) {
      ObjectMatrix[n] = new int[size];
   }

    for(int i=0; i<size; i++){
        for (int j=0; j<size; j++){
            int solution = 0;
            for (int k=0; k<size; k++){
                solution = solution + MatrixA[i][k]*MatrixB[k][j];
            }
            ObjectMatrix[i][j] = solution;
         }
    }
    return ObjectMatrix;
}

