#include<iostream>
#include<stdlib.h>
#include <math.h>
#include <chrono> 
#include <iomanip>
using namespace std;
using namespace std::chrono;

float* AssignArray(int n, float c);
float* AssignQueue(int n);
float* AssignArray_D(int n);
void printarray(float* object_array, int array_size);
void MM1K_T_Cal(float lambda, float rou, float k);
void Simulation(float* LC, float* AT, float C, float k, float miu, float lambda, float* Queue);

int main(){
    
    int n = 2000;
    float miu = 1;
    float C = 1000;
    float k = 100;
    float one_d_miu = 1;
    float* LC = AssignArray(n, one_d_miu);
    float* AT = AssignArray(n, 1);
    float* LCD = AssignArray_D(n);
    float* Queue = AssignQueue(n);
    cout<<endl;
    cout<< setw(8) << left<< "load" << setw(15) << left<< "MM1K_S"<< setw(15) << left<<"MM1K_T" << setw(15) << left<<"MD1K_S" ;
    for(float lambda = 100; lambda < 1201; lambda +=100){
        float rou =  lambda/(miu * C);
        cout<<endl;
        cout<< setw(8) << left<< rou;
        //MM1K_S
        Simulation(LC, AT, C, k, miu, lambda, Queue);
        //MM1K_T
        MM1K_T_Cal(lambda, rou, k);
        //MD1K_S
        Simulation(LCD, AT, C, k, miu, lambda, Queue);
    }
    return 0;
}

void Simulation(float* LC, float* AT, float C, float k, float miu, float lambda,float* Queue){
    int q = 0;
    float L_Max = k/C;
    float L_Queue = 0;
    float current_load = 0;
    float waiting_time = 0;
    float arr_t = 0;
    float new_load = 0;
    float trans_t =0;
    int i = 0;
    //cout<<L_Max<<endl;
    for(i=0;i<2000;i++){
        new_load = LC[i]/C;
        arr_t = AT[i]/lambda;
        if (current_load + new_load < L_Max/10){
            //cout<<"current_load="<<current_load<<"!"<<endl;
            current_load += new_load;
            i += 1;
            continue;
        } else if (trans_t >= current_load){
            //dequeue
            //cout<<"dequeue"<<endl;
            trans_t =0;
            current_load = 0;
            while (current_load + Queue[0] < L_Max  &&  q>0){
                current_load += Queue[0];
                q -= 1;
                for(int j=0; j<q; j++ ){
                    Queue[j] = Queue[j+1];
                }
                Queue[q] = 0;
            }
            L_Queue -= current_load;
            continue;
        } else {
            //enqueue
            //cout<<"queue";
            Queue[q] = new_load;
            if (i>=1000){
                waiting_time += L_Queue;
            }
            L_Queue += new_load;
            trans_t += arr_t;
            q += 1;
            i += 1;
        }
    }
    cout<< setw(15) << left<< waiting_time/500;
}


void MM1K_T_Cal(float lambda, float rou, float k){
    if (rou == 1){
        rou = 1.0001;
    }
    float p1=pow(rou,k+2);
    float p2=pow(rou,k+1);
    float p3=pow(rou,k);
    float top = rou + k*p1 -(k+1)*p2;
    float bot = lambda * (1-rou)* (1-p3);
    float solution = top/bot;
    cout<< setw(15) << left<< solution;
}

float* AssignArray(int n, float c){
    float* objectArray = new float[n];
    for (int i = 0; i < n; i++){
        objectArray[i] = -c*log(float(rand())/float(RAND_MAX));
    }
    return objectArray;
}

float* AssignQueue(int n){
    float* objectArray = new float[n];
    for (int i = 0; i < n; i++){
        objectArray[i] = 0;
    }
    return objectArray;
}

float* AssignArray_D(int n){
    float* objectArray = new float[n];
        for (int i = 0; i < n; i++){
            objectArray[i] = 1;
        }
    return objectArray; 
}

void printarray(float* object_array, int array_size){
    for (int i = 0; i < array_size; i++){
        cout<<object_array[i]<<" ";
    }
    cout<<endl;
}