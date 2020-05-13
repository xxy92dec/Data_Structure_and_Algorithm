#include<iostream>
#include<stdlib.h>
#include <math.h>
#include <chrono> 
#include <iomanip>
using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[])
{
    float a = 5.0;
    for (int i=0;i<20;i++)
        printf("%f\n", ((float)rand()/(float)(RAND_MAX)) * a);
    return 0;
}