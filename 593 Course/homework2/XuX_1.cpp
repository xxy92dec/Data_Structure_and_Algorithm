#include<iostream>
#include<stdlib.h>
#include <math.h>
#include <chrono> 
#include <iomanip>
using namespace std;
using namespace std::chrono;


int** AssignMatrix(int size);
int** Naive(int** MatrixA,int** MatrixB, int size);
void printmatrix(int** MatrixC, int size);
int** Strassen(int** MatrixA, int** MatrixB,int size);

int main(){
    int maxnum = 10;
    cout << "\n\n";
    cout << setw(8) << left << "#n" << setw(8) << left << "Runtime_SQUARE_MATRIX";
    cout << setw(8) << left << "Bound_SQUARE_MATRIX" << setw(8) << left << "Runtime_STRASSEN’S_METHOD";
    cout << setw(8) << left << "Bound_STRASSEN’S_METHOD\n" <<endl;
    float total_time_per_item_n = 0;
    float total_time_per_item_s = 0;

    for (int n = 1; n <= maxnum; n++){
        int** MatrixA;
        int** MatrixB;
        int size = pow(2,n);
        MatrixA = AssignMatrix(size);
        MatrixB = AssignMatrix(size);
        int DividePara = size * size;
        //n, Runtime_SQUARE_MATRIX, Bound_SQUARE_MATRIX, Runtime_STRASSEN’S_METHOD, Bound_STRASSEN’S_METHOD
        
        //Naive
        int** MatrixC1;
        auto start = high_resolution_clock::now(); 
        MatrixC1 = Naive(MatrixA,MatrixB,size);
        auto stop = high_resolution_clock::now(); 
        auto duration = duration_cast<microseconds>(stop - start);
        float DivideTime_n = duration.count()/DividePara;
        total_time_per_item_n += DivideTime_n;
        float Bound_time_n = total_time_per_item_n * size;
       
        
        //Strassen
        int** MatrixC2;
        auto start1 = high_resolution_clock::now();
        MatrixC2 = Strassen(MatrixA,MatrixB,size);
        auto stop1 = high_resolution_clock::now(); 
        auto duration1 = duration_cast<microseconds>(stop1 - start1);
        float DivideTime_s = duration1.count()/DividePara;
        total_time_per_item_s += DivideTime_s;
        float Bound_time_s = total_time_per_item_s * size;
        
        if (size == 4){
            cout<<"Naive Method Solution"<<endl;
            printmatrix(MatrixC1, size);
            cout<<"Strassen Method Solution"<<endl;
            printmatrix(MatrixC2, size);
        }
        
        cout << setw(8) << left << size << setw(8) << left << duration.count();
        cout << setw(8) << left << Bound_time_n << setw(8) << left << duration1.count();
        cout << setw(8) << left << Bound_time_s <<endl;
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
                solution += MatrixA[i][k]*MatrixB[k][j];
            }
            ObjectMatrix[i][j] = solution;
         }
    }
    return ObjectMatrix;
}

void printmatrix(int** MatrixC,int size){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            cout<<MatrixC[i][j]<<"  ";
        }
        cout<<endl;
    }
    cout<<"Matrix END"<<endl;
}

int** Strassen(int** MatrixA, int** MatrixB,int size){
    int** ObjectMatrix = new int*[size];
    for (int n = 0; n < size; n++) {
        ObjectMatrix[n] = new int[size];
    }
    
    if (size == 16 ){ //Run Time & Memory Optimize for big matrix
        ObjectMatrix = Naive(MatrixA, MatrixB, size);
    } else if(size == 2) { // 2X2 Calculate
        ObjectMatrix = Naive(MatrixA, MatrixB, size);
    } else {
        //Split
        //cout<<"Strassen Mode"<<endl; 
        int halfsize = size/2;
        int** MA11 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MA11[n] = new int[halfsize];
        }

        int** MA12 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MA12[n] = new int[halfsize];
        }

        int** MA21 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MA21[n] = new int[halfsize];
        }

        int** MA22 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MA22[n] = new int[halfsize];
        }

        int** MB11 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MB11[n] = new int[halfsize];
        }

        int** MB12 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MB12[n] = new int[halfsize];
        }

        int** MB21 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MB21[n] = new int[halfsize];
        }

        int** MB22 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MB22[n] = new int[halfsize];
        }
        for (int i=0; i<halfsize; i++){
            for(int j=0; j<halfsize; j++){
                MA11[i][j] = MatrixA[i][j];
                MB11[i][j] = MatrixB[i][j];
            }
        }
        for (int i=0; i<halfsize; i++){
            for(int j=0; j<halfsize; j++){
                MA12[i][j] = MatrixA[i][j+halfsize];
                MB12[i][j] = MatrixB[i][j+halfsize];
            }
        } 
        for (int i=0; i<halfsize; i++){
            for(int j=0; j<halfsize; j++){
                MA21[i][j] = MatrixA[i+halfsize][j];
                MB21[i][j] = MatrixB[i+halfsize][j];
            }
        }
        for (int i=0; i<halfsize; i++){
            for(int j=0; j<halfsize; j++){
                MA22[i][j] = MatrixA[i+halfsize][j+halfsize];
                MB22[i][j] = MatrixB[i+halfsize][j+halfsize];
            }
        }

        //SMatrix
        int** MS1 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MS1[n] = new int[halfsize];
        }//S1 = B12 - B22
        for (int i=0; i<halfsize; i++){
            for(int j=0; j<halfsize; j++){
                MS1[i][j] = MB12[i][j]-MB22[i][j];
            }
        }

        int** MS2 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MS2[n] = new int[halfsize];
        }//S2 = A11 + A12
        for (int i=0; i<halfsize; i++){
            for(int j=0; j<halfsize; j++){
                MS2[i][j] = MA11[i][j] + MA12[i][j];
            }
        }

        int** MS3 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MS3[n] = new int[halfsize];
        }//S3 = A21 + A22
        for (int i=0; i<halfsize; i++){
            for(int j=0; j<halfsize; j++){
                MS3[i][j] = MA21[i][j] + MA22[i][j];
            }
        }

        int** MS4 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MS4[n] = new int[halfsize];
        }//S4 = B21 - B11
        for (int i=0; i<halfsize; i++){
            for(int j=0; j<halfsize; j++){
                MS4[i][j] = MB21[i][j]-MB11[i][j];
            }
        }

        int** MS5 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MS5[n] = new int[halfsize];
        }//S5 = A11 + A22
        for (int i=0; i<halfsize; i++){
            for(int j=0; j<halfsize; j++){
                MS5[i][j] = MA11[i][j] + MA22[i][j];
            }
        }

        int** MS6 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MS6[n] = new int[halfsize];
        }//S6 = B11 + B22
        for (int i=0; i<halfsize; i++){
            for(int j=0; j<halfsize; j++){
                MS6[i][j] = MB11[i][j] + MB22[i][j];
            }
        }

        int** MS7 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MS7[n] = new int[halfsize];
        }//S7 = A12 - A22
        for (int i=0; i<halfsize; i++){
            for(int j=0; j<halfsize; j++){
                MS7[i][j] = MA12[i][j] - MA22[i][j];
            }
        }
        
        int** MS8 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MS8[n] = new int[halfsize];
        }//S8 = B21 + B22
        for (int i=0; i<halfsize; i++){
            for(int j=0; j<halfsize; j++){
                MS8[i][j] = MB21[i][j] + MB22[i][j];
            }
        }

        int** MS9 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MS9[n] = new int[halfsize];
        }//S9 = A11 - A21
        for (int i=0; i<halfsize; i++){
            for(int j=0; j<halfsize; j++){
                MS9[i][j] = MA11[i][j] - MA21[i][j];
            }
        }

        int** MS10 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MS10[n] = new int[halfsize];
        }//S10 = B11 + B12
        for (int i=0; i<halfsize; i++){
            for(int j=0; j<halfsize; j++){
                MS10[i][j] = MB11[i][j] + MB12[i][j];
            }
        }  
        //PMatrix
        int** P1;
        int** P2;
        int** P3;
        int** P4;
        int** P5;
        int** P6;
        int** P7;
        P1 = Strassen(MA11,MS1,halfsize);
        P2 = Strassen(MS2,MB22,halfsize);
        P3 = Strassen(MS3,MB11,halfsize);
        P4 = Strassen(MA22,MS4,halfsize);
        P5 = Strassen(MS5,MS6,halfsize);
        P6 = Strassen(MS7,MS8,halfsize);
        P7 = Strassen(MS9,MS10,halfsize);
        //CMatrix
        int** MC11 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MC11[n] = new int[halfsize];
        }//C11 = P5 + P4 - P2 + P6
        for (int i=0; i<halfsize; i++){
            for(int j=0; j<halfsize; j++){
                MC11[i][j] = P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j];
            }
        }

        int** MC12 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MC12[n] = new int[halfsize];
        }//C12 = P1 + P2
        for (int i=0; i<halfsize; i++){
            for(int j=0; j<halfsize; j++){
                MC12[i][j] = P1[i][j] + P2[i][j];
            }
        }

        int** MC21 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MC21[n] = new int[halfsize];
        }//C21 = P3 + P4
        for (int i=0; i<halfsize; i++){
            for(int j=0; j<halfsize; j++){
                MC21[i][j] = P3[i][j] + P4[i][j];
            }
        }

        int** MC22 = new int*[halfsize];
        for (int n = 0; n < halfsize; n++) {
            MC22[n] = new int[halfsize];
        }//C22 = P5 + P1 - P3 - P7
        for (int i=0; i<halfsize; i++){
            for(int j=0; j<halfsize; j++){
                MC22[i][j] = P5[i][j] + P1[i][j] - P3[i][j] - P7[i][j];
            }
        }
        //ObjectMatrix MC11,MC12,MC21,MC22.
        for (int i=0; i<halfsize; i++){
            for(int j=0; j<halfsize; j++){
                ObjectMatrix[i][j] = MC11[i][j];
                ObjectMatrix[i][j+halfsize] = MC12[i][j];
                ObjectMatrix[i+halfsize][j] = MC21[i][j];
                ObjectMatrix[i+halfsize][j+halfsize] = MC22[i][j];
            }
        }
                
    }
    return ObjectMatrix;
}