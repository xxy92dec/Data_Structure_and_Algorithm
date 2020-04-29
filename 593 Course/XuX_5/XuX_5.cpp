#include<iostream>
#include<stdlib.h>
#include <math.h>
#include <chrono> 
#include <iomanip>
#include <vector>
using namespace std;
using namespace std::chrono;

int* AssignArray(int n);
void printarray(int* object_array, int array_size);
void assignment(int n);
int RandomSelect(int* A, int p, int r, int i);
int RandomPartition(int* A, int p, int r);
int Partition(int*A, int p, int r);
int* CountingSort(int* A);
void printlucky(int* object_array, int lucky, int unlucky, int n);
int** BucketSort(int* A, int n);

int main(){
    cout<<"For 0 based arrays, ignore A[0]."<<endl;
    cout << setw(8) << left << "#n" << setw(8) << left << "RandomS_t";
    cout << setw(8) << left << "CountingS_t" << setw(8) << left << "BucketS_t"<<endl;
    int A[4] = {10,100,500,1000};
    for (int i=0; i<4; i++){
        assignment(A[i]);
        cout<<endl;
    }
    return 0;
}

void assignment(int n){
    int* A = AssignArray(n);
    int* AO = new int[14]; 

    for (int i = 0; i<14; i++){
        AO[i] = A[i];
    }
    //cout<<"Print assigned Array"<<endl;
    //printarray(A,14);
    //3a
    cout<<"RandomSelect"<<endl;
    auto start = high_resolution_clock::now(); 
    int unlucky = RandomSelect(A,1,13,1);
    int lucky = RandomSelect(A,1,13,13);
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<nanoseconds>(stop - start);
    printlucky(AO, lucky, unlucky, n);
    //3b
    cout<<"CountingSort"<<endl;
    auto start1 = high_resolution_clock::now(); 
    int* D = CountingSort(AO);
    auto stop1 = high_resolution_clock::now(); 
    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);

    unlucky = D[1];
    lucky = D[13];
    printlucky(AO, lucky, unlucky, n);
    //3c
    cout<<"BucketSort"<<endl;
    auto start2 = high_resolution_clock::now(); 
    int** E = BucketSort(A,14);
    auto stop2 = high_resolution_clock::now(); 
    auto duration2 = duration_cast<nanoseconds>(stop2 - start2);

    for (int i=0; i<10; i++){
        for (int j = 0; E[i][j]>=0; j++){
            lucky = E[i][j];
        }
    }
    unlucky = -1;
    for (int i=0; unlucky<0; i++){
        for (int j = 0; E[i][j]>=0; j++){
            unlucky = E[i][j];
            break;
        }
    }
    printlucky(AO, lucky, unlucky, n);
    cout << setw(8) << left << n << setw(8) << left << duration.count();
    cout << setw(8) << left << duration1.count() << setw(8) << left << duration2.count()<<endl;
}
// c1
int RandomSelect(int* A, int p, int r, int i){
    if (p == r){
        return A[p];
    }
    int q = RandomPartition(A,p,r);
    int k = q - p + 1;
    if (i==k){
        return A[q];
    }
    else if(i<k){
        return RandomSelect(A,p,q-1,i);
    }
    else{
        return RandomSelect(A,q+1,r,i-k);
    }

}
int RandomPartition(int* A, int p, int r){
    int r1 = r - p;
    int i = rand()%p + r1+1;
    int A0 = A[i];
    A[i] = A[r];
    A[r] = A0;
    return Partition(A, p, r);
}
int Partition(int*A, int p, int r){
    int x = A[r];
    int i = p - 1;
    for(int j = p; j< r; j++){
        if (A[j]<=x){
            i += 1;
            int A0 = A[i];
            A[i]=A[j];
            A[j]=A0;
        }
    }
    int A1 = A[i+1];
    A[i+1] = A[r];
    A[r] = A1;
    return i+1;
}

//C2
int* CountingSort(int* A){
    int* objectArray = new int[14];
    int maxnum = 0;
    for (int i = 0; i<14; i++){
        if (A[i] > maxnum){
            maxnum = A[i];
        }
    }

    int* CountingArray = new int[maxnum+1];
    for (int i = 0; i<=maxnum; i++){
        CountingArray[i] = 0;
    }
    //printarray(CountingArray,maxnum+1);

    for (int i = 0; i<14; i++){
        int j = A[i];
        CountingArray[j] += 1;
    }

    int j = 0;
    for (int i = 0; i<=maxnum; i++){
        if (CountingArray[i] >0){
            for(int k=0; k<CountingArray[i];k++){
                objectArray[j] = i;
                j +=1;
            }
        }
    }
    //printarray(CountingArray,maxnum+1);
    //printarray(objectArray,13);
    return objectArray;
}

//C3
int** BucketSort(int* A, int n){
    int** BucketMatrix = new int*[10];
    for (int i = 0; i < 10; i++) {
        BucketMatrix[i] = new int[n];
    }
    for (int i = 0; i < 10; i++){
        for (int j =0; j < n; j++){
            BucketMatrix[i][j] = -1;
        }
    }
    // insert A to B
    for(int i = 1; i<=13; i++){

        int l = A[i]/10;
        int timer = 0;
        if (l > 9){
            l = 9;
        }

        for(int j=0; timer < 1; j++){
            if (BucketMatrix[l][j] == -1){
                BucketMatrix[l][j] = A[i];
                timer += 1;
            } 
        }
    }

    // sort B
    for (int i = 0; i <10; i++){
        for (int j = 1; BucketMatrix[i][j] >= 0; j++){
            int t = -1;
            for (int k = 0; k<j; k -= 1){
                if (BucketMatrix[i][k] > BucketMatrix[i][j]) {
                    t = k;
                    break;
                }
            }
            if (t >= 0){
                int number = BucketMatrix[i][j];
                for (int l=t ; l<j; l++ ){
                    BucketMatrix[i][l+1] =  BucketMatrix[i][l+1];
                }
                BucketMatrix[i][t] = number;
            }
        }
    }
    return BucketMatrix;
}






int* AssignArray(int n){
    int* objectArray = new int[14];
    int* Array0 = new int[n];
    for (int i = 0; i < 14; i++){
        objectArray[i] = 0;
    }

    for (int i = 0; i < n; i++){
        Array0[i] = rand()%13;
        int j = Array0[i]+1;
        objectArray[j] += 1;
    }
    return objectArray;
}

void printarray(int* object_array, int array_size){
    for (int i = 0; i < array_size; i++){
        cout<<object_array[i]<<" ";
    }
    cout<<endl;
}

void printlucky(int* object_array, int lucky, int unlucky, int n){
    int ln = 0;
    int un = 0;
    int* lna = new int[13];
    int* una = new int[13];
    for(int i=1;i<14;i++){
        if (object_array[i] == lucky){
            lna[ln] = i;
            ln += 1;
        }
        if (object_array[i] == unlucky){
            una[un] = i;
            un += 1;
        }
    }

    cout<<"lucky number is ";
    for (int i=0; i<ln; i++){
        cout<<lna[i]<<" ";
    }
    cout<<"; ";
    cout<<"unlucky number is ";
    for (int i=0; i<un; i++){
        cout<<una[i]<<" ";
    }
    cout<<"."<<endl;

    float lnn = lucky;
    float unn = unlucky;
    float nn = n;
    float lp = lnn*100/nn;
    float up = unn*100/nn;
    cout<<"probabilities of a lucky winner is "<<lp<<"%; probabilities of a unlucky winner is "<<up<<"%."<<endl;

}

