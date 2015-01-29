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
printf("Ogo 5?: %d\n",root->child[0]->child[2]->b[0]);
/*t=0;
temp=root;
for(q=0;q<depth;q++) {
	root=root->child[0];
	printf(" Node %d\n",q);
	for(t=0;t<6;t++) {
	root=root->parent->child[t];
	if(root!=NULL) {
		printf("Line %d : ",t);
		for(i=0;i<14;i++)
			printf("%d ",root->b[i]);
	}
	else break;
	printf("\n");
	}
}
*/	return 0;
}

Node * mm(Node * n, int depth, int a,int count) {
	int i,k;
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
		t->child[i-8] = mm(t,depth-1,0,count);
	}
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
		printf("val : %d , move : %d\n",n->value,test);
	}
}
	

