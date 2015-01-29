//AI test.
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node {
	int b[14];
	struct Node * parent;
	struct Node * child[6];
	int vals[6];
	int value;
	int last_stop;
	int on_move;
};
typedef struct Node Node;

Node * mm(Node*,int,int,int);
int MakeMove(Node*,int,int);

int main(void) {
	Node * root;
	Node * temp;
	int i,q,t,depth=3;

	root=(Node*)malloc(sizeof(Node));
	temp=(Node*)malloc(sizeof(Node));
	root->value=0;
	root->on_move=0;
	root->last_stop=0;
	for(i=0;i<14;i++) {
		if(i==0 || i==7)
			continue;
		root->b[i]=3;
	}
	root = mm(root,depth,-1,0);
for(q=0;q<6;q++) {
	printf("Line %d : ",q);
//	temp=root->child[q];
	for(i=0;i<14;i++)
		printf("%d ",root->child[q]->b[i]);//temp->b[i]);
	printf(" - %d \n",root->child[q]->value);
}
//printf("Best score : %d \n",root->child[1]->child[2]->b[0]);
printf("val :%d\n",root->value);
	return 0;
}

Node * mm(Node * n, int depth, int a,int count) {
	int i,k,m;
	Node * t;
	if(depth == 0) return NULL;
	for(i=8;i<14;i++) {
		count++;
		t=(Node *)malloc(sizeof(Node));
		t->parent = n;
		n->child[i-8]=t;
		memcpy(t->b,n->b,sizeof(int)*14);
		if(t->b[i]==0) {
			continue;
		}
		MakeMove(t,i,0);
		k=t->value;
		t->child[i-8] = mm(t,depth-1,0,count);
	}
	k=0;
	for(i=0;i<6;i++){
		if(n->child[i]->value>k) {
			k=n->child[i]->value;
			n->last_stop=n->child[i]->last_stop;
			m=n->last_stop;
		}
	}
	n->on_move=k;
	printf("val : %d, last : %d, d : %d\n",k,m,depth);
	return t->parent;
}

int MakeMove(Node * n, int move,int b) {
	int i;
	int test=move;
	int count = n->b[move];
	n->b[move] = 0;
	n->last_stop = move;
	move = move + 1;
	while(count--!=0) {
		if(move==14) move = 0;
		if(move==7) {
			move++;
			count++;
		}
		n->b[move++]++;
	}
	move-=1;
	if(move == 0)
		n->value = abs(n->b[7] - n->b[0]) + 2;
	else {
		n->value = abs(n->b[7] - n->b[0]);
//		printf("val : %d , move : %d\n",n->value,test);
	}
}
// *** End :)	

