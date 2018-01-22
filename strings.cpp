//
//  DAQ2.cpp
//  DAAssignment_4
//
//  Created by Siavash Nazari on 1/27/13.
//  Copyright (c) 2013 Siavash Nazari. All rights reserved.
//

#include <iostream>
#include <utility>
#include <queue>
#include <vector>

#define INF 100000000
#define MAX_n  28

using namespace std;

int n,s,t;
int residual[MAX_n][MAX_n];      // it's getting bad :|
int true_capacity[MAX_n][MAX_n]; // god damn it!...
int capacity[MAX_n][MAX_n];      // capacity matrix
int fullgraph[MAX_n][MAX_n];     // full, input graph
int flow[MAX_n][MAX_n];          // flow matrix
queue<int> Q;

int dist_from_s[MAX_n];

#define WHITE 0
#define GRAY 1
#define BLACK 2

int color[MAX_n]; // needed for breadth-first search
int pred[MAX_n];  // array to store augmenting path

int cut[MAX_n];

int bfs (int start, int target) {
    int u,v;
    for (u=0; u<n; u++) {
        color[u] = WHITE;
        pred[u] = -1;
    }
    
    Q.push(start);
    color[start] = GRAY;
    pred[start] = -1;
    
    while(!Q.empty()) {
        u = Q.front();
        Q.pop();
        color[u] = BLACK;
        // Search all adjacent white nodes v. If the capacity from u to v in the residual network is positive, enqueue v.
        for (v=0; v<n; v++) {
            if (color[v]==WHITE && residual[u][v]>0 ) {
                
                Q.push(v);
                color[v] = GRAY;
                pred[v] = u;
            }
            
        }
        
    }
    // If the color of the target node is black now, it means that we reached it.
    return color[target]==BLACK;
}

void max_flow (int source, int sink) {
    /*
     int max_flow = 0;
     // While there exists an augmenting path, increment the flow along this path.
     while (bfs(source,sink)) {
     // Determine the amount by which we can increment the flow.
     int increment = INF;
     for (int u=n-1; pred[u]>=0; u=pred[u]) {
     increment = min(increment,true_capacity[pred[u]][u]-flow[pred[u]][u]);
     }
     
     // Now increment the flow.
     for (int u=n-1; pred[u]>=0; u=pred[u]) {
     flow[pred[u]][u] += increment;
     flow[u][pred[u]] -= increment;
     
     }
     max_flow += increment;
     }
     // No augmenting path anymore. We are done.
     return max_flow;
     */
    
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            residual[i][j] = true_capacity[i][j];
    
    while( bfs(source,sink) ) {
        int u = t-1;
        //int father = pred[u];
        while( pred[u] != -1 ) {
            residual[pred[u]][u]--;
            residual[u][pred[u]]++;
            u = pred[u];
            
        }
    }
    
}


void directing_bfs() {
    int u,v;
    int start = s-1;
    Q.push(start);
    color[start] = GRAY;
    dist_from_s[start] = 0;
    while(!Q.empty()) {
        u = Q.front();
        Q.pop();
        color[u] = BLACK;
        // Search all adjacent white nodes v. If the capacity from u to v in the residual network is positive, enqueue v.
        for (v=0; v<n; v++) {
            if ( (color[v]==WHITE || color[v]==GRAY) && (fullgraph[v][u] == 1 || fullgraph[u][v] == 1) ) {
                if( color[v]==WHITE )
                    dist_from_s[v] =  dist_from_s[u] + 1;
                Q.push(v);
                color[v] = GRAY;
                capacity[v][u] = 1;
                capacity[u][v] = 0;
            }
        }
    }
    
}

void removing_bfs() {
    int u,v;
    int start = t-1;
    Q.push(start);
    while(!Q.empty()) {
        u = Q.front();
        Q.pop();
        // Search all adjacent white nodes v. If the capacity from u to v in the residual network is positive, enqueue v.
        for (v=0; v<n; v++) {
            if ( (capacity[u][v] == 1 || capacity[v][u] == 1) && ( dist_from_s[u]-dist_from_s[v]==1 ) ) {
                Q.push(v);
                true_capacity[v][u] = 1;
                true_capacity[u][v] = 0;
            }
            /*
             else {
             true_capacity[v][u] = 0;
             true_capacity[u][v] = 0;
             }
             */
        }
    }
}


void sad(vector<int> p[MAX_n], int d[MAX_n]){
    
    int u,v;
    int start = t-1;
    for (int i =0 ; i<n; i++) {
        color[i] = WHITE;
    }
    Q.push(start);
    while(!Q.empty()) {
        u = Q.front();
        Q.pop();
        // Search all adjacent white nodes v. If the capacity from u to v in the residual network is positive, enqueue v.
        for (v=0; v<p[u].size(); v++) {
            Q.push(p[u][v]);
            if(d[u] == d[p[u][v]] + 1)
                true_capacity[p[u][v]][u] = 1;
            color[v] = GRAY;
        }
        
        color[u]  =BLACK;
    }
    
}

void worse(int r, vector<int> parent[MAX_n], int d[MAX_n]){
    for (int i = 0; i < parent[r].size(); i++) {
        if(d[r] == d[parent[r][i]] + 1){
            true_capacity[parent[r][i]][r] = 1;
            worse(parent[r][i], parent, d);
        }
    }
}

//--------------------
void directing_true(){
    int color[MAX_n];
    int distance[MAX_n];
    vector<int> p[MAX_n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            true_capacity[i][j] = 0;
    
    for(int i = 0;i<n;i++){
        color[i] = WHITE;
        distance[i] = -1;
    }
    
    queue<int> Q;
    distance[s-1] = 0;
    color[s-1] = GRAY;
    Q.push(s-1);
    while(!Q.empty()){
        int x = Q.front();
        Q.pop();
        color[x] = BLACK;
        for (int i = 0; i < n; i++) {
            if(fullgraph[x][i] && color[i] != BLACK){
                p[i].push_back(x);
            }
            
            if(color[i] != WHITE)
                continue;
            if(fullgraph[x][i]){
                Q.push(i);
                color[i] = GRAY;
                distance[i] = distance[x] + 1;
            }
            
        }
        
    }
    
    worse(t-1,p,distance);
}

vector<int> R;
vector<int> S;
void printing_bfs() {
    int u,v;
    int start = s-1;
    R.push_back(s-1);
    Q.push(start);
    for (int i =0 ; i<n; i++) {
        color[i] = WHITE;
    }
    while(!Q.empty()) {
        u = Q.front();
        Q.pop();
        // Search all adjacent white nodes v. If the capacity from u to v in the residual network is positive, enqueue v.
        for (v=0; v<n; v++) {
            if ( color[v] != BLACK && (residual[u][v] > 0) ) {
                Q.push(v);
                R.push_back(v);
                color[v] = GRAY;
            }
        }
        color[u]  =BLACK;
    }
    S.push_back(t-1);
    for (int i = 0; i<n; i++) {
        bool b = false;
        for (int j = 0; j<n; j++) {
            if(true_capacity[i][j] >0 || true_capacity[j][i] > 0)
                b = true;
        }
        if(b){
            for (int j = 0; j<R.size(); j++) {
                if(R[j] == i)
                    b = false;
            }
            if(b){
                S.push_back(i);
            }
        }
    }
    
}


bool contains(vector<int> F, int h) {
    for(int i=0; i<F.size(); i++)
        if(F[i]==h)
            return true;
    return false;
}

#define MAX_length 100000

string first, second;
int length;

bool use[26];

int main() {
    
    cin >> length ;
    cin >> first  ;
    cin >> second ;
    n = MAX_n  ;
    // Initializing edge capacities
    for(int i=0; i<n; i++) {
        for(int j=0; j<i+1; j++) {
            capacity[i][j] = 0;
            capacity[j][i] = capacity[i][j];
            fullgraph[i][j] = 0;
            fullgraph[j][i] = fullgraph[i][j];
            true_capacity[i][j] = 0;
            true_capacity[j][i] = true_capacity[i][j];
        }
    }
    for(int i=0; i<26; i++)
        use[i]=false;
    // Setting capacities of "true" edges
    for(int i=0; i<length; i++) {
        int x,y;
        if( first[i]=='0' )
            x = 26;
        else if( first[i]=='1' )
            x = 27;
        else
            x = first[i] - 'a';
        if( second[i]=='0' )
            y = 26;
        else if( second[i]=='1' )
            y = 27;
        else
            y = second[i] - 'a';
        if( x != y ) {
            fullgraph[x][y]++;
            use[x] = true;
            use[y] = true;
            fullgraph[y][x]++;
        }
    }
    /*
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++)
            cout << fullgraph[i][j] << " ";
        cout << endl;
    }
    
    */
    
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++)
            true_capacity[i][j] = fullgraph[i][j] ;
    }
    
    /*
     
     cout << "initial graph... " << endl;
     for(int i=0; i<n; i++) {
     for(int j=0; j<n; j++)
     cout << fullgraph[i][j] << " ";
     cout << endl;
     }
     
     */
    
    for(int u=0; u<n; u++) {
        color[u] = WHITE;
    }
    
    for(int i=0; i<n; i++)
        dist_from_s[i] = INF;
    
    // directing_true();
    
    
    /*
     for(int i=0; i<n; i++)
     cout << "dist_from_s[ " << i+1 << " ] = " << dist_from_s[i] << endl;
     cout << "after removing bfs... " << endl;
     for(int i=0; i<n; i++) {
     for(int j=0; j<n; j++)
     cout << true_capacity[i][j] << " ";
     cout << endl;
     }
     */
    
    
    //removing_bfs();
    
    
    
    // Initial flow is zero in whole graph
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            flow[i][j] = 0;
        }
    }
    
    s = 27;
    t = 28;
    max_flow(s-1,t-1);
    printing_bfs();
    
    /*
     cout << "******" << endl;
     cout<<R.size()<<endl;
     
     for(int i=0; i<R.size(); i++) {
     cout << R[i] << " ";
     }
     cout << endl;
     cout <<"S:"<<endl;
     for(int i=0; i<S.size(); i++) {
     cout << S[i] << " ";
     }
     cout << endl;
     
     cout << "residual... " << endl;
     for(int i=0; i<n; i++) {
     for(int j=0; j<n; j++)
     cout << residual[i][j] << " ";
     cout << endl;
     }
     */
    
    /*
    int counter = 0;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if( fullgraph[i][j] == 1 && contains(R, i) && contains(S, j) )
                counter++;
    
    cout << counter << endl;
    */
    
    
    for(int i=0; i<n-2; i++) {
            if( use[i] && contains(R, i) )
                cout << (char)('a'+i) << " " << 0 << endl;
            if( use[i] && contains(S, i) )
                cout << (char)('a'+i) << " " << 1 << endl;
    }
    
    
    /*
     for(int u=n-1; pred[u]>=0; u=pred[u]) {
     cout<< u+1 << " " << pred[u]+1 << endl;
     }
     */
    
    return 0;
}
