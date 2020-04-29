#include<iostream>
#include<stdlib.h>
#include <math.h>
#include <chrono> 
#include <iomanip>
using namespace std;
using namespace std::chrono;

int** AssignMatrix(int n);
void printmatrix(int** MatrixC,int rowsize, int colsize);
void deterministicInterviewing(int** ArrayList, int row);
void probabilisticInterviewing(int** ArrayList, int row);

int main(){
    cout << setw(10) << left << "#n" << setw(10) << left << "DetMethod"<< setw(10) << left << "ProMethod"<<endl;
    //Assign ArrayList
    int** ArrayList1 = AssignMatrix(10000);
    int** ArrayList2 = AssignMatrix(1000);
    int** ArrayList3 = AssignMatrix(100);
    int** ArrayList4 = AssignMatrix(10);

    //Size 10
    deterministicInterviewing(ArrayList4, 10);
    probabilisticInterviewing(ArrayList4, 10);
    //Size 100
    deterministicInterviewing(ArrayList3, 100);
    probabilisticInterviewing(ArrayList3, 100);
    //Size 1000
    deterministicInterviewing(ArrayList2, 1000);
    probabilisticInterviewing(ArrayList2, 1000);
    //Size 10000
    deterministicInterviewing(ArrayList1, 10000);
    probabilisticInterviewing(ArrayList1, 10000);
    return 0;
}

int** AssignMatrix(int n){
    int** ObjectMatrix = new int*[n];
    for (int i = 0; i < n; i++) {
      ObjectMatrix[i] = new int[n];
    }
    for (int i = 0; i < n; i++){
        for (int j =0; j < 11; j++){
         ObjectMatrix[i][j] = rand() % 11;
        }
    }
    return ObjectMatrix;
}

void printmatrix(int** Arraylist,int rowsize, int colsize){
    for(int i=0; i<rowsize; i++){
        for(int j=0; j<colsize; j++){
            cout<<Arraylist[i][j]<<"  ";
        }
        cout<<endl;
    }
    cout<<"Matrix END"<<endl;
}

void deterministicInterviewing(int** ArrayList, int row){
    cout<<endl;
    cout<<"n= "<<row<<endl;
    int AG = 0;
    int i = 0;
    for (i; i<row; i++){
        int num = 0;
        for (int j=0; j<10; j++){
            int num0 = ArrayList[i][j];
            num = num + num0;
            if (num >= 70){
                cout<<"Source "<<i<<" reported a malware with maliciousness score of "<<num<<" or higher. The source found after interviewing "<<i+1<<" interviewed candidates."<<endl;
                AG = AG +1;
                break;
            }
        }
        //cout<< num <<endl;
        if (AG == 1){
            cout << setw(10) << left << row << setw(10) << left << i+1;
            break;
        }
    }
    if (AG == 0){
        cout<<"None of the reports met the threat threshold!"<<endl;
        cout << setw(10) << left << row << setw(10) << left << i;
    }
}

void probabilisticInterviewing(int** ArrayList, int row){
    int AG = 0;
    int i = 0;
    for (i ; i<row; i++){
        int num = 0;
        int k = rand() % row;
        for (int j=0; j<10; j++){ 
            int num0 = ArrayList[k][j];
            num = num + num0;
            if (num >= 70){
                cout << setw(10) << left << i+1 <<endl;
                cout<<"Source "<<k<<" reported a malware with maliciousness score of "<<num<<" or higher. The source found after interviewing "<<i+1<<" interviewed candidates."<<endl;
                AG = AG +1;
                break;
            }
        }
        //cout<< num <<endl;
        if (AG == 1){
            break;
        }
        
    }
    if (AG == 0){
        cout << setw(10) << left << i <<endl;
        cout<<"None of the reports met the threat threshold!"<<endl;
    }
}