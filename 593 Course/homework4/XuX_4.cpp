#include<iostream>
#include<stdlib.h>
#include <math.h>
#include <chrono> 
#include <iomanip>
using namespace std;
using namespace std::chrono;

int* AssignArray(int n);
void printarray(int* object_array, int array_size);
int* quicksort(int* input_array, int n);
int* reverseArray(int* input_array, int n);
void assignment(int n);
int waiting_time(int* input_array, int n);
int queue_time(int* input_array, int n);
int avg_queue_time(int* input_array, int n);

int main(){
    cout<< setw(9) << left << "n";
    cout<< setw(9) << left << "A_n/3" << setw(9) << left <<"A_2n/3"<< setw(9) << left <<"A_n";
    cout<< setw(9) << left << "B_n/3" << setw(9) << left <<"B_2n/3"<< setw(9) << left <<"B_n";
    cout<< setw(9) << left << "C_n/3" << setw(9) << left <<"C_2n/3"<< setw(9) << left <<"C_n";
    cout<< setw(9) << left << "A_Avg" << setw(9) << left <<"B_Avg"<< setw(9) << left <<"C_Avg"<<endl;

    for (int i=10; i<1011; i+=100){
        assignment(i);
    }
    return 0;
}

void assignment(int n){
    int* Array_A = AssignArray(n);
    auto start = high_resolution_clock::now();
    int* Array_B = quicksort(Array_A, n);
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    float sorting_time = duration.count()/n;
    int* Array_C = reverseArray(Array_B, n);

    int a = n/3;
    int b = 2*n/3;

    int wtA1 = waiting_time(Array_A,a);
    int wtA2 = waiting_time(Array_A,b);
    int wtA3 = waiting_time(Array_A,n);
    int wtB1 = waiting_time(Array_B,a);
    int wtB2 = waiting_time(Array_B,b);
    int wtB3 = waiting_time(Array_B,n);
    int wtC1 = waiting_time(Array_C,a);
    int wtC2 = waiting_time(Array_C,b);
    int wtC3 = waiting_time(Array_C,n);
    int QtA = avg_queue_time(Array_A,n)+ sorting_time;
    int QtB = avg_queue_time(Array_B,n)+ sorting_time;
    int QtC = avg_queue_time(Array_C,n)+ sorting_time;
    cout<< setw(9) << left << n;
    cout<< setw(9) << left << wtA1 << setw(9) << left <<wtA2<< setw(9) << left <<wtA3;
    cout<< setw(9) << left << wtB1 << setw(9) << left <<wtB2<< setw(9) << left <<wtB3;
    cout<< setw(9) << left << wtC1 << setw(9) << left <<wtC2<< setw(9) << left <<wtC3;
    cout<< setw(9) << left << QtA << setw(9) << left <<QtB<< setw(9) << left <<QtC<<endl;
}

int* AssignArray(int n){
    int* objectArray = new int[n];
    for (int i = 0; i < n; i++){
        objectArray[i] = rand() % 101;
    }
    return objectArray;
}

void printarray(int* object_array, int array_size){
    for (int i = 0; i < array_size; i++){
        cout<<object_array[i]<<" ";
    }
    cout<<endl;
}

int* quicksort(int* input_array, int n){
    int* sorted_array = new int[n];
    int* left_array = new int[n];
    int* right_array= new int[n];
    int left_n=0;
    int right_n=0;
    int reference = input_array[n-1];
    int left_num, right_num;
    // part I
    for (int i = 0; i < n-1; i++){
        if(input_array[i] < reference){
            left_array[left_n] = input_array[i]; 
            left_n += 1;
        }
        else{
            right_array[right_n] = input_array[i]; 
            right_n += 1;
        }
    }

    sorted_array[left_n] = input_array[n-1];

    // part II 
    if (left_n > 1){
        left_array = quicksort(left_array, left_n);
        for (int i = 0; i < left_n; i++){
            sorted_array[i] = left_array[i];
        }
    } else if(left_n == 1 ) {
        sorted_array[0] = left_array[0];
    }

    if (right_n > 1){
        right_array = quicksort(right_array, right_n);
        for (int i = 0; i< right_n; i++){
            sorted_array[left_n+1+i] = right_array[i];
        }
    } else if(right_n == 1 ){
        sorted_array[n-1] = right_array[0];
    }
    return sorted_array;
}

int* reverseArray(int* input_array, int n){
    int* reversedArray= new int[n];
    for (int i = 0; i<n; i++){
        reversedArray[i] = input_array[n-i-1];
    }
    return reversedArray;
}

int waiting_time(int* input_array, int n){
    int total_time=0;
    for (int i=0; i<n; i++){
        total_time += input_array[i];
    }
    int wt = total_time;
    return wt;
}

int queue_time(int* input_array, int n){
    int total_time=0;
    for (int i=0; i<n; i++){
        total_time += input_array[i];
    }
    int wt = total_time;
    int qt = wt + input_array[n-1];
    return qt;
}

int avg_queue_time(int* input_array, int n){
    int total_time = 0;
    
    for (int i=1; i<=n ;i++){
        total_time += queue_time(input_array,i);
        //cout<<queue_time(input_array,i)<<endl;
    }
    int avg_time = total_time/n;
    return avg_time;
}