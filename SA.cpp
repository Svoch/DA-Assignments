//
//  SA.cpp
//  AIAssignment_2
//
//  Created by Siavash Nazari on 4/8/13.
//  Copyright (c) 2013 Siavash Nazari. All rights reserved.
//

#include <iostream>
#include <vector>
#include <utility>
#include <time.h>
#include <set>
#include <cstdlib>
#include <cmath>


using namespace std;

// input variables
int n,m,k;

// random number generator function
int random(int a, int b) {
    return rand() % (b-a) + a;
}

// function for calculating distance of two people
double distance(pair<int,int> a, pair<int,int> b) {
    double result = (a.first - b.first)*(a.first - b.first) + (a.second - b.second)*(a.second - b.second);
    return sqrt(result);
}

/*
 * the State class
 */
class State {
    
public:
    
    // vectors for holding where each professor or each student sits
    vector< pair<int,int> > professor;
    vector< pair<int,int> > student;
    
    // double value for holding total amount of dissatisfaction
    double val;
    
    // sets 'val' in a state
    void copmute() {
        
        double result = 0;
        
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                result += 1 / ::distance(professor[j],student[i]);
        for(int i=0; i<m; i++)
            for(int j=i+1; j<m; j++)
                result += 1 / ::distance(professor[j],professor[i]);
        
        val = result;
        
    }
    
    // generates a random state
    // guarantees there would be no two people on a same sit :D
    State* getRandomState() {
        
        State* s = new State();
        set< pair<int,int> > pairs;
        
        // first setting students in their places
        for(int i=0; i<n; i++) {
            pair<int,int> temp(random(0, k),random(0, k));
            while( pairs.find(temp) != pairs.end() ) {
                temp = pair<int,int>(random(0, k),random(0, k));
            }
            s->student.push_back(temp);
            pairs.insert(temp);
        }
        
        // then setting professors in their places
        for(int i=0; i<m; i++) {
            pair<int,int> temp(random(0, k),random(0, k));
            while( pairs.find(temp) != pairs.end() ) {
                temp = pair<int,int>(random(0, k),random(0, k));
            }
            s->professor.push_back(temp);
            pairs.insert(temp);
            
        }
        
        s->copmute();
        return s;
        
    }
    
    // form a given state, generates possible next states, and returns the best one
    // best one is the one with the least dissatisfaction value
    State* getRandomSuccessorState(State* s) {
        State* next = new State();
        int rand = random(0,n+m);
        
        set< pair<int,int> > pairs;
        // adding current state student positons to next state
        for(int i=0; i<n; i++) {
            pairs.insert(s->student[i]);
            next->student.push_back(s->student[i]);
        }
        // adding current state professor positons to next state
        for(int i=0; i<m; i++) {
            pairs.insert(s->professor[i]);
            next->professor.push_back(s->professor[i]);
        }
        next->val = s->val;
        
        // changing a studetn's position
        if( rand < n ) {
            pair<int,int> temp(random(0, k),random(0, k));
            while( pairs.find(temp) != pairs.end() ) {
                temp = pair<int,int>(random(0, k),random(0, k));
            }
            
            // recalculating 'val' for new state
            double diff = 0;
            for(int j=0; j<m; j++)
                diff += 1 / ::distance(s->professor[j],next->student[rand]);
            next->val -= diff;
            
            pairs.erase(temp);
            next->student[rand].first = temp.first;
            next->student[rand].second = temp.second;
            pairs.insert(temp);
            
            diff = 0;
            for(int j=0; j<m; j++)
                diff += 1 / ::distance(s->professor[j],next->student[rand]);
            next->val += diff;
            
        }
        // changing a professor's position
        else {
            pair<int,int> temp(random(0, k),random(0, k));
            while( pairs.find(temp) != pairs.end() ) {
                temp = pair<int,int>(random(0, k),random(0, k));
            }
            
            // recalculating 'val' for new state
            double diff = 0;
            for(int j=0; j<m; j++)
                if(j != rand-n)
                    diff += 1 / ::distance(s->professor[j],s->professor[rand-n]);
            for(int j=0; j<n; j++)
                diff += 1 / ::distance(s->student[j],s->professor[rand-n]);
            next->val -= diff;
            
            pairs.erase(temp);
            next->professor[rand-n].first = temp.first;
            next->professor[rand-n].second = temp.second;
            pairs.insert(temp);
            
            diff = 0;
            for(int j=0; j<m; j++)
                if(j!=rand-n)
                    diff += 1 / ::distance(s->professor[j],next->professor[rand-n]);
            for(int j=0; j<n; j++)
                diff += 1 / ::distance(s->student[j],next->professor[rand-n]);
            next->val += diff;
            
        }
        
        return next;
        
    }
    
    // schedule function
    double schedule(int time) {
        if( 1 / time < 0.00001 )
            return 1 / time;
        return 0.00001;
    }
    
    // unused function, for calculating value of a given state
    // previously this function was used for debugging 
    double value(State* s) {
        double result = 0;
        
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                result += 1 / ::distance(s->professor[j],s->student[i]);
        
        for(int i=0; i<m; i++)
            for(int j=i+1; j<m; j++)
                result += 1 / ::distance(s->professor[j],s->professor[i]);
        
        return result;
    }
    
    
    // main function in the code
    // Simulated Annealing for states
    // it keeps a 'best state' in mind, in order to pass it as the result of computation
    State* SA() {
        State* current = getRandomState();
        current->copmute();
        State* next;
        double T;
        State* best = current;
        int halt = 1;
        double startTime = time(0);
        while( time(0) - startTime < 5 ) {
            T = schedule(halt);
            next = getRandomSuccessorState(current);
            double e = - next->val + current->val;
            if( e > 0 ) {
                delete current;
                current = next;
            }
            else
                if( (double)rand()/RAND_MAX <= exp(e/T) ){
                    if( best == 0 || best->val > current->val)
                        best = current;
                    else
                        delete current;
                    current = next;
                }
            halt++;
        }
        
        //cout << "halt is " << halt << endl;

        if( best->val < current->val )
            return best;
        else
            return current;
    }
    
    // function used for printing a state
    void print(State* s) {
        cout << s->value(s) << endl;
        for(int i=0; i<n; i++)
            cout << s->student[i].first + 1 << " " << s->student[i].second + 1 << endl;
        for(int j=0; j<m; j++)
            cout << s->professor[j].first + 1 << " " << s->professor[j].second + 1 << endl;
    }
    
};

int main() {
    
    cin >> k >> m >> n;
    State* s;
    s = s->SA();
    
    s->print(s);
    
    return 0;
}
