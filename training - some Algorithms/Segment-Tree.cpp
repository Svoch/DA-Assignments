#include <iostream>
#include <algorithm>

using namespace std;

#define N 100*1000

struct Interval{
	int begin,end;
	Interval(int a = 0 ,int b = 0){
		begin = a;
		end = b;
	}
	Interval getInter(Interval temp){// if doesn't have intersection the begin is bigger than end;
		Interval a(max(temp.begin,begin) , min(temp.end,end));
		return a;
	} 

	bool operator == (Interval temp) const{
		return ( this->begin == temp.begin && this->end == temp.end ) ;
	}

	int length(){
		return (end-begin);
	}
};

struct Node{
	
	Interval inter;
	Node* left;
	Node* right;
	Node* parent;
	int count;
	int len;
	
	Node(){
		left = NULL ;
		right = NULL ;
		parent = NULL ;
		count = 0 ;
		len = 0 ;
	}
};

struct SegmentTree{

	Node* root;
	SegmentTree(int bound[],int begin,int end){
		root = createNode(bound,begin,end);
		root->parent = NULL;
	}
	Node* createNode(int bound[],int begin,int end){
		Node* node = new Node();
		Interval inter(bound[begin],bound[end]);
		node->inter= inter;		
		if ( end - begin > 1 ){
			int mid = (begin+end)/2;
			node->left = createNode(bound,begin,mid);
			node->left->parent = node ; 
			node->right = createNode(bound,mid,end);
			node->right->parent = node ;
		}
		return node;
	}
	static int length(Node* node){
		if ( node == NULL )
			return 0 ;
		if (node->count != 0 )
			return node->inter.length();
		else
			return node->len;
	}
	static void update_length(Node* node){
		Node* temp = node ;
		while ( temp != NULL ){
			temp->len = length(temp->left) + length(temp->right);
			temp = temp->parent;
		}
	}
	
	static void insert_inter(Node* node,Interval temp){
		if ( temp.begin >= temp.end)
			return;
		if ( node->inter == temp){
			node->count++;
			if ( node->count == 1 )
				update_length(node->parent);
			return;
		}
			insert_inter(node->right,temp.getInter(node->right->inter));
			insert_inter(node->left,temp.getInter(node->left->inter));
	}
	static void delete_inter(Node* node,Interval temp){
		if ( temp.begin >= temp.end)
			return;
		if ( node->inter == temp){
			node->count--;
			if ( node->count == 0 )
				update_length(node->parent);
			return;
		}
			delete_inter(node->right,temp.getInter(node->right->inter));
			delete_inter(node->left,temp.getInter(node->left->inter));
	
	}
};
int main(){
	return 0;
}

