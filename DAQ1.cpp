//
//  DAQ1.cpp
//  DAAssignment
//
//  Created by Siavash Nazari on 10/25/12.
//  Copyright (c) 2012 Siavash Nazari. All rights reserved.
//

#include <iostream>
#include <vector>
# define MAX 500000

using namespace std;

vector<int> vertices[MAX];
int answer = 0;
bool mark[MAX];

int dapath( int root ) {
    
    int flag;
    mark[root] = true;
    int k = 0;
    
    for(int i=0; i<vertices[root].size(); i++)
        if( !mark[vertices[root].at(i)] )
            k+=dapath( vertices[root].at(i) );
    
    
    if( k < 2 ) {
        flag = 1;
    } else {
        flag = 0;
        answer += k-1;
    }
    
    
    return flag;
    
}

int main() {
	
	int n;
	cin >> n;
    

    for(int i=0; i<n-1; i++) {
		
        int first, second;
        cin >> first >> second;
        vertices[first].push_back(second);
		vertices[second].push_back(first);
        
          
	}
    
    for( int i=0; i<MAX; i++)
        mark[i] = false;
    
    //DFSmarking( &tree[1] );
    
    
    
    /*
    
    int counter=0;
    for(int i=0; i<MAX; i++) {
        if ( mark[i] )
            counter++;
    }
    
    */
    /*
    cout << endl << counter << endl;
    */
    
     
    //cout << vertices[1].at(0) << " " << vertices[1].at(1);
    
    /*
    for(int i=0; i<10; i++) {
        cout << "mark[ " << i << " ] is : " << mark[i] << endl;
     }
     */
    /*
    for(int i=0; i<MAX; i++) {
        
        if( !vertices[i].empty() ) {
             cout << "\n vertex[ " << i << " ] : ";
             for(int j=0; j<vertices[i].size(); j++)
             cout << vertices[i].at(j) << " ";
           }
    }
    */
    if( dapath(1) == 1)
        answer++;
	cout << answer;
    cout << endl;
    
    return 0;
}

