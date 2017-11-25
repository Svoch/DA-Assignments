//
//  DAQ3.cpp
//  DAAssignment
//
//  Created by Siavash Nazari on 10/22/12.
//  Copyright (c) 2012 Siavash Nazari. All rights reserved.
//

# include <iostream>
# include <utility>
# include <algorithm>
# include <vector>
# include <set>
# define MAX 10000 + 100

using namespace std;

vector<pair<int,int> > point;
set<pair<int,int> > dot;

void addPoints(int beginIndex, int endIndex) {
    
    /*
     if( endIndex - beginIndex == 1 ) {
     int leftX = point[beginIndex].first;
     int rightX = point[endIndex].first;
     dot.insert(pair<int,int>(leftX,point[endIndex].second));
     point.push_back(pair<int,int> (leftX,point[endIndex].second) );
     dot.insert(pair<int,int>(rightX,point[beginIndex].second));
     point.push_back(pair<int,int> (rightX,point[beginIndex].second) );
     }
     
     
     else */ if ( endIndex > beginIndex ) {
         
         int midIndex = ( beginIndex + endIndex ) / 2 ;
         
         /*
          cout << "begin index is: " << beginIndex << endl;
          cout << "mid index is: " << midIndex << endl;
          cout << "end index is: " << endIndex << endl;
          */
         
         addPoints(beginIndex, midIndex);
         addPoints(midIndex+1, endIndex);
         
         int leftX = point[midIndex].first;
         int rightX = point[midIndex+1].first;
         
         // cout << "left and right X : " << leftX << " " << rightX << endl;
         
         for(int i=beginIndex; i<endIndex+1; i++) {
             dot.insert(pair<int,int>(leftX,point[i].second));
             point.push_back(pair<int,int> (leftX,point[i].second) );
         }
         
         for(int i=beginIndex; i<endIndex+1; i++) {
             dot.insert(pair<int,int>(rightX,point[i].second));
             point.push_back(pair<int,int> (rightX,point[i].second) );
         }
         
     }
    
    /*
     int leftX = point[midIndex].first;
     int rightX = point[midIndex+1].first;
     
     // cout << "left and right X : " << leftX << " " << rightX << endl;
     
     for(int i=beginIndex; i<endIndex; i++) {
     dot.insert(pair<int,int>(leftX,point[i].second));
     point.push_back(pair<int,int> (leftX,point[i].second) );
     }
     
     for(int i=beginIndex; i<endIndex; i++) {
     dot.insert(pair<int,int>(rightX,point[i].second));
     point.push_back(pair<int,int> (rightX,point[i].second) );
     }
     */
    /*
     for(int i=midIndex; i<endIndex; i++) {
     dot.insert(pair<int,int>(leftX,point[i].second));
     point.push_back(pair<int,int> (leftX,point[i].second) );
     }
     
     for(int i=beginIndex; i<midIndex; i++) {
     dot.insert(pair<int,int>(rightX,point[i].second));
     point.push_back(pair<int,int> (rightX,point[i].second) );
     }
     */
    
    /*
     int midX = ( leftX + rightX ) / 2;
     for(int i=beginIndex; i<endIndex; i++) {
     dot.insert(pair<int,int>(midX,point[i].second));
     point.push_back(pair<int,int> (midX,point[i].second) );
     }
     */
    
    
    
}

bool x_compare(pair<int,int> first, pair<int,int> second) {
    if (first.first < second.first )
        return true;
    return false;
}


int main() {
    
    //-- number of points
    int n;
    cin >> n;
    
    for(int i=0; i<n; i++) {
        
        int x,y;
        cin >> x >> y;
        point.push_back(pair<int,int>(x,y));
        dot.insert(pair<int,int>(x,y));
        //cout << "point " << i << " is: (" << point[i].first << " , " << point[i].second << " ) \n" ;
        
    }
    
    //-- sort the shit by their x
    
    sort(point.begin(), point.end(), x_compare);
    
    addPoints(0,n-1);
    
    /*
     
     for(int i=0; i<n; i++) {
     
     cout << "point " << i << " is: (" << point[i].first << " , " << point[i].second << " ) \n" ;
     
     }
     
     
     
     cout << "added points..." << endl;
     
     for(int i=n; i<point.size(); i++)
     cout << "point " << i << " that is: (" << point[i].first << " , " << point[i].second << " ) \n" ;
     
     
     */
    
    cout << dot.size() << endl;
    for(set<pair<int,int> > ::iterator i=dot.begin(); i!=dot.end(); i++)
        cout << (*i).first << " " << (*i).second << endl ;
    
    
    return 0;
}