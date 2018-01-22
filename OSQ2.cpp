//
//  OSQ2.cpp
//  OSAssignment_1
//
//  Created by Siavash Nazari on 4/16/13.
//  Copyright (c) 2013 Siavash Nazari. All rights reserved.
//


/*
/  Quicksort code found on the internet, on Stackoverflow.com
/  I just added "pthread" part to it, and converted it into some code using threads :)
*/

#include "pthread.h"
#include "iostream"


using namespace std;

#define MAX_n 100000

int arr[MAX_n];
int n;

struct param {
    
    int left;
    int right;
    
};

void *quickSort(void *pp) {
    
    param * p = (param *)(pp);
    int left = p->left, right = p->right;
    int i = left, j = right;
    int tmp;
    int pivot = arr[ abs((left + right) / 2) ];
    
    pthread_t thread_right, thread_left;

    /* partition */
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    
    /* recursion */
    if (left < j) {
        param* left_p = p;
        left_p->left = left;
        left_p->right = j;
        pthread_create(&thread_left, NULL, quickSort, left_p);
        pthread_join(thread_left, NULL);
    }
    
    if (i< right) {
        param* right_p = p;
        right_p->left = i;
        right_p->right = right;
        pthread_create(&thread_right, NULL, quickSort, right_p);
        pthread_join(thread_right, NULL);
    }
    
    pthread_exit(NULL);
}


int main() {

    cin >> n;
    
    for(int i=0; i<n; i++)
        cin >> arr[i];
    
    pthread_t main_thread;
    param * parameter = new param[1];
    parameter->left = 0;
    parameter->right = n-1;
    pthread_create(&main_thread, NULL, quickSort, parameter);
    pthread_join(main_thread, NULL);
    
    for(int i=0; i<n; i++)
        cout << arr[i] << " ";
    cout << endl;
    
    return 0;
}