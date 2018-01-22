//
//  OSQ1.cpp
//  OSAssignment_1
//
//  Created by Siavash Nazari on 4/16/13.
//  Copyright (c) 2013 Siavash Nazari. All rights reserved.
//

#include "pthread.h"
#include "iostream"
#include "unistd.h"

using namespace std;

#define MAX_A 1000
#define MAX_B 500
#define MAX_C 800
#define MAX_D 500
#define MAX_E 5000

#define RATE_A 10
#define RATE_B 5
#define RATE_C 3
#define RATE_D 4
#define RATE_E 5

#define delay 0.001

int a = 0, b = 0, c = 0;
int d = 0, e = 0;

bool full_warehouse = false;
int declare_d = 0, declare_e = 0;

pthread_t thread_A, thread_B, thread_C;
pthread_t thread_D;
pthread_t thread_E;

/*
pthread_mutex_t mutex_a, mutex_b, mutex_c;
pthread_mutex_t mutex_d;
pthread_mutex_t mutex_e;
*/

pthread_mutex_t mutex_a = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_b = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_c = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_d = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_e = PTHREAD_MUTEX_INITIALIZER;


void *build_A(void *threadID) {
    //long tid = (long)threadID;
    while( !full_warehouse ) {
        sleep(delay);
        pthread_mutex_lock(&mutex_a);
        if ( a <= MAX_A ) {
            a += RATE_A;
        }
        if( a > MAX_A )
            a = MAX_A;
        pthread_mutex_unlock(&mutex_a);
    }
    //cout << "created (" << a << ") products of type(A)" << endl;
    pthread_exit(NULL);
}

void *build_B(void *threadID) {
    //long tid = (long)threadID;
    while( !full_warehouse ) {
        sleep(delay);
        pthread_mutex_lock(&mutex_b);
        if ( b <= MAX_B ) {
            b += RATE_B;
        }
        if( b > MAX_B )
            b = MAX_B;
        pthread_mutex_unlock(&mutex_b);
    }
    //cout << "created (" << b << ") products of type(B)" << endl;
    pthread_exit(NULL);
}

void *build_C(void *threadID) {
    //long tid = (long)threadID;
    while( !full_warehouse ) {
        sleep(delay);
        pthread_mutex_lock(&mutex_c);
        if ( c <= MAX_C ) {
            c += RATE_C;
        }
        if( c > MAX_C )
            c = MAX_C;
        pthread_mutex_unlock(&mutex_c);
    }
    //cout << "created (" << c << ") products of type(C)" << endl;
    pthread_exit(NULL);
}

void *build_D(void *threadID) {
    //long tid = (long)threadID;
    while ( !full_warehouse ) {
        sleep(delay);
        
        pthread_mutex_lock(&mutex_d);
        pthread_mutex_lock(&mutex_b);
        pthread_mutex_lock(&mutex_a);

        declare_d = 0;
        for(int i=0; i<2; i++) {
            if( a >= 4 && b >= 3 && d <= MAX_D) {
                a -= 4;
                b -= 3;
                d += 2;
                declare_d += 2;
            }
            cout << "created (" << declare_d << ") products of type(D)" << endl;
        }
        if( d > MAX_D )
            d = MAX_D;
        
        pthread_mutex_unlock(&mutex_a);
        pthread_mutex_unlock(&mutex_b);
        pthread_mutex_unlock(&mutex_d);
    }
    pthread_exit(NULL);

}

void *build_E(void *threadID) {
    //long tid = (long)threadID;
    while ( !full_warehouse ) {
        sleep(delay);
        
        pthread_mutex_lock(&mutex_e);
        pthread_mutex_lock(&mutex_d);
        pthread_mutex_lock(&mutex_c);

        declare_e = 0;
        for(int i=0; i<5; i++) {
            if( c >= 1 && d >= 3 && e <= MAX_E ) {
                d -= 3;
                c -= 1;
                e += 1;
                declare_e += 1;
            }
            cout << "created (" << declare_e << ") products of type(E)" << endl;
        }
        if( e > MAX_E )
            e = MAX_E;
        if( e == MAX_E ) {
            full_warehouse = true;
        }
        
        pthread_mutex_unlock(&mutex_c);
        pthread_mutex_unlock(&mutex_d);
        pthread_mutex_unlock(&mutex_e);
        
        
    }
    
    pthread_mutex_lock(&mutex_d);
    cout << "Warehouse is now full!!!" << endl;
    pthread_mutex_unlock(&mutex_d);

    pthread_exit(NULL);


}

int main() {
    
    /*
    pthread_t threads[4];
    int rc[4];
    */
    
    int rc_a, rc_b, rc_c;
    int rc_d, rc_e;
    
    rc_a = pthread_create(&thread_A, NULL, build_A, (void* ) 1);
    rc_b = pthread_create(&thread_B, NULL, build_B, (void* ) 2);
    rc_c = pthread_create(&thread_C, NULL, build_C, (void* ) 3);
    
    rc_d = pthread_create(&thread_D, NULL, build_D, (void* ) 4);
    rc_e = pthread_create(&thread_E, NULL, build_E, (void* ) 5);

    
    pthread_join(thread_A, NULL);
    pthread_join(thread_B, NULL);
    pthread_join(thread_C, NULL);
    pthread_join(thread_D, NULL);
    pthread_join(thread_E, NULL);
    
    //cout << "Warehouse is now full!!!" << endl;

    //cout << "completed thread E" << endl;
    
    
    cout << "a is " << a << endl;
    cout << "b is " << b << endl;
    cout << "c is " << c << endl;
    cout << "d is " << d << endl;
    cout << "e is " << e << endl;
    
    
    return 0;
}