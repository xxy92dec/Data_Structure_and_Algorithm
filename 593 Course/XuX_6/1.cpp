#include<iostream>
#include<stdlib.h>
#include <math.h>
#include <chrono> 
#include <iomanip>
using namespace std;
using namespace std::chrono;

float* AssignArray(int n, float c);
float* AssignQueue(int n);
void printarray(float* object_array, int array_size);
void assignment(float l, float*AT, float*LC);
void queue_work(float* AT, float* LC,float* Q, float* WQ);

int main(){
    cout<<"Time unit is microsecond."<<endl;
    cout<< setw(10) << left<< "load" << setw(10) << left<< "MM1K_S"<< setw(10) << left<<"MM1K_T" << setw(10) << left<<"MD1K_S" << setw(10) << left<<endl;
    int K = 1100;
    float one_d_miu = 1000;
    float* LC = AssignArray(K, one_d_miu);
    float* AT = AssignArray(K, 1);
    for (int i=100; i<1201; i+=100){
        assignment(i, AT, LC);
    } 
    return 0;
}

void assignment(float l, float*AT, float*LC){
    int K = 1100;
    float one_d_l = 1000000/l;
    float D = 1000;
    float* AT_l = new float[K];
    float* LC_D = new float[K];
    
    for (int i = 0; i<K; i++){
        AT_l[i] = AT[i] * one_d_l;
        LC_D[i] = D;
    }
    cout<< setw(10) << left<<l/1000;
    float* Q = AssignQueue(250);
    float* WQ = AssignQueue(250);
    queue_work(AT_l,LC,Q,WQ);
    float theory = 0;
    cout<< setw(10) << left<< theory;
    queue_work(AT_l,LC_D,Q,WQ);
    cout<<endl;
}

void queue_work(float* AT, float* LC,float* Q, float* WQ){
    float k = 100;
    float C = 1000;
    float max_length = k*1000000/C;
    float length = 0;
    float w_length = 0;
    float q_time_total = 0;
    float timer_in = 0;
    float timer_out = 0;
    int n = 0;
    int i_q = 0;
    int i_wq = 0;
    for(float t = 0; n<1100; t +=10){
        if (Q[199]>1)
        {
            cout<<"q almost full."<<endl;
        }
        if (WQ[199]>1)
        {
            cout<<"wq almost full."<<endl;
        }
        //enqueue waiting queue
        if(timer_in>AT[n]){
            timer_in = 0;
            WQ[i_wq] = LC[n];
            i_wq += 1;
            w_length += LC[n];
            if(n>=1000){
                q_time_total += w_length;
            } 
            n += 1;
        }
        //dequeue
        if(timer_out>Q[0]){
            if (Q[0]<1){
                timer_out = 0;
            }
            if(Q[0]>0){
                length -= Q[0];
                timer_out = timer_out - Q[0];
                for (int j=0; j<i_q-1; j++){
                    Q[j] = Q[j+1];
                }
                Q[i_q-1] = 0;
                i_q -= 1;
            }
        }
        //enqueue
        if(length+ WQ[0] <max_length){
            if(WQ[0]>0){
                Q[i_q] = WQ[0];
                i_q += 1;
                length += WQ[0];
                //dequeue waiting queue
                w_length -= WQ[0];
                for (int j=0; j<i_q-1; j++){
                    WQ[j] = WQ[j+1];
                }
                WQ[i_wq-1] = 0;
                i_wq -= 1;
            }
        }
        timer_in += 10;
        timer_out += 10; 
        
    }
    //cout<<endl;
    float avg_time_total = q_time_total/100;
    cout<< setw(10) << left<<avg_time_total<<" ";
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

void printarray(float* object_array, int array_size){
    for (int i = 0; i < array_size; i++){
        cout<<object_array[i]<<" ";
    }
    cout<<endl;
}