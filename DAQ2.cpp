//
//  DAQ2.cpp
//  DAAssignment
//
//  Created by Siavash Nazari on 10/22/12.
//  Copyright (c) 2012 Siavash Nazari. All rights reserved.
//

#include <iostream>
#include <vector>
# define MAX 500000

using namespace std;

vector<int> vertices[MAX];
int average;
bool mark [MAX];
int neighbour [MAX];
int answer_size = 0;



void removeVertex( int m ) {
    
    if( mark[m] )
        answer_size--;
    mark[m] = false;
    for(int i=0; i<vertices[m].size(); i++) {
        neighbour[vertices[m].at(i)]--;
        if( neighbour[vertices[m].at(i) ] <= average/2 && mark[vertices[m].at(i)] )
            removeVertex(vertices[m].at(i));
    }
    
}




int main() {
	
	int n,e;
	cin >> n >> e;
    
    average = 2 * e / n;
    for(int i=0; i<e; i++)
	{
		int first, second;
        cin >> first >> second;
		vertices[first].push_back(second);
		vertices[second].push_back(first);
        
	}
    
	for( int i=0; i<n; i++)
        mark[i] =true;
    for( int i=n; i<MAX; i++)
        mark[i] =false;
    
    //-----------------------------------------------
    for(int i=0; i<MAX; i++) {

        if( !vertices[i].empty() ) {
            answer_size++;
            neighbour[i] = (int) vertices[i].size();
            /*
             cout << "\n vertex[ " << i << " ] : ";
             for(int j=0; j<vertices[i].size(); j++)
             cout << vertices[i].at(j) << " ";
             */
        }
    }
    
    
	for(int i=0; i<MAX; i++)
	{
		if( mark[i] && vertices[i].size() <= average / 2 ) {
			removeVertex( i );
		}
		else
			mark[i] = true;
	}
    
    
    
    //-----------------------------------------------
    cout << answer_size << endl;
    for(int i=0; i<MAX; i++) {
        if( !vertices[i].empty() && mark[i] )
            cout << i << " ";
    }
    
    
	return 0;
}


