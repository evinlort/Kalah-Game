#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node {
	int b[14];
	struct Node * parent;
	struct Node * child[6];
	int value;
	int last_stop;
};
typedef struct Node Node;

int mm(Node*,int,int,int);
int MakeMove(Node*,int,int);

int main(void) {
	Node * root;
	Node * temp;
	int i,q;

	root=(Node*)malloc(sizeof(Node));
	for(i=0;i<14;i++) {
		if(i==0 || i==7)
			continue;
		root->b[i]=3;
	}
	mm(root,1,-1,0);
for(q=0;q<6;q++) {
	printf("Line %d : ",q);
//	temp=root->child[q];
	for(i=0;i<14;i++)
		printf("%d ",root->child[q]->b[i]);//temp->b[i]);
	printf(" - %d \n",root->child[q]->value);
}

printf("val %d\n",root->child[5]->child[2]->value);
	return 0;
}

int mm(Node * n, int depth, int a,int count) {
	int i,k;
	Node * t;
	printf("depth = %d, a = %d\n",depth,a);
	if(a>12) depth-=1;
	if(depth==0) return 0;;
	for(i=8;i<14;i++) {
		count++;
		t=(Node *)malloc(sizeof(Node));
		t->parent = n;
		memcpy(t->b,n->b,sizeof(int)*14);
		if(t->b[i]==0) {
			printf("*********************\n");
			continue;
		}
		if(MakeMove(t,i,0))
			t->value=abs(t->b[7]-t->b[0]) + 2;
		else
			t->value=abs(t->b[7]-t->b[0]);
		n->child[i-8]=t;
		printf("Count = %d\n",count);
		mm(t,depth,i,count);
	}
	depth-=1;
}

int MakeMove(Node * n, int move,int b) {
	int i;
	int count = n->b[move];
	n->b[move] = 0;
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
	n->last_stop=move;
	if(move == 0)
		return 1;
	else
		return 0;
}
	
