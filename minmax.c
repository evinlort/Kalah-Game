#include "minmax.h"
#include<string.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

Node * init(){
	int number_of_rocks;
	int iterator;
	int i;
	int board[14];
	Node * root=(Node*)malloc(sizeof(Node));
	do {
		printf("Enter number of rocks : _\b");
		while(scanf("%d",&number_of_rocks)!=1) {
			printf("Enter number of rocks : _\b");
			getchar();
		}
	} while(number_of_rocks < 3 || number_of_rocks > 6);
	for(iterator=0;iterator<14;iterator++) {
		if(iterator==0 || iterator==7) {
			board[iterator]=0;
			continue;
		}
		board[iterator]=number_of_rocks;
	}
	memcpy(root->board,board,sizeof(int)*14);
	return root;
}

int game_is_not_finished(Node * n) {
	int no_moves_for_one_of_players;
	no_moves_for_one_of_players=check_zeros(n);	
	if(no_moves_for_one_of_players)
		return 0;
	else
		return 1;
}

int minmax(Node * r) {
	int m;
/*	int last_rock_pos;
	srand(time(NULL));
//TODO replace check_zeros from here
//	if(!check_zeros(r)) {
	if(!player_zeros(r,1)) { 
		do {
			printf("%d rand\n",rand());
			m=rand() % 6 + 8;
		} while(legal_move(r,m));
	
		last_rock_pos=scatter_rocks(r,m,1);
		return last_rock_pos;
	}
	else
		return -1;					*/
		m = AImove(r);
		return m;
}

int scatter_rocks(Node * scattered,int hole, int move) {
	int count;
	count = scattered->board[hole];
	scattered->board[hole] = 0;
	hole = hole + 1;
	for(;count>0;count--){
		if(hole == 14) {
			hole = 0;
		}
		if(move && hole == 7) {
			hole++;
			count++;
			continue;
		}
		if((!move) && hole == 0) {
			hole++;
			count++;
			continue;
		}
		scattered->board[hole]++;
		hole++;
	}
	need_to_grab(move,hole-1,scattered);
	return hole-1;
}

int stop_at_current_player_kalah(Node * n,int move, int scatter_stop) {
	int zeros;
	//zeros = check_zeros(n);
	zeros = player_zeros(n,move);
	if( ((move && scatter_stop == 0) || (!move && scatter_stop == 7)) && !zeros )
		return 1;
	else
		return 0;
}

void need_to_grab(int move, int pos, Node * sct) {
	if( (move && (pos >= 8 && pos <=13)) || (!move && (pos>=1 && pos <=6)) )
		if(sct->board[pos] == 1 && sct->board[14-pos]!=0)
			grab(move,pos,sct);
}

void grab(int move, int pos, Node * sct) {
	int k;
	k = move?0:7;
	sct->board[k] = sct->board[k] + 1 + sct->board[14-pos];
	sct->board[pos] = 0;
	sct->board[14-pos] = 0;
}

int check_zeros(Node * s) {
	int checkH=1;
	int checkAI=1;
	int i;
	for(i = 1;i < 7;i++)
		if(s->board[i]!=0) {
			checkH = 0;
			break;
		}
	for(i = 8;i < 14;i++)
		if(s->board[i]!=0) {
			checkAI = 0;
			break;
		}
	if( checkH || checkAI ) {
		for(i = 8;i < 14;i++) {
			s->board[0]+=s->board[i];
			s->board[i]=0;
		}
//	if( checkAI )
		for(i = 1;i < 7;i++) {
			s->board[7]+=s->board[i];
			s->board[i]=0;
		}
	}
	if( checkH || checkAI )
		return 1;	//Game end
	else
		return 0;
}
void print(int * d){
	int i;
/*	#ifdef ISWIND
		system("cls");
	#else
*/		system("clear");
//	#endif
	printf("|AI 1   2   3   4   5   6  AI         - Player AI side. | points to AI's kalah.\n\n    ");
	for(i=13;i!=7;i--){
		printf("%d   ",d[i]);
	}
	printf("\n%d",d[0]);
	printf("                           %d\n",d[7]);
	printf("    ");
	for(i=1;i<7;i++){
		printf("%d   ",d[i]);
	}
	printf("\n\n H  1   2   3   4   5   6  H|         - Player H side. | points to H's kalah.\n\n");
}

int legal_move(Node * s, int hmove) {
	if(s->board[hmove]!=0)
		return 0;
	else
		return 1;	
}

int player_zeros(Node * n, int move) {
	int i;
	int till;
	int is_zero = 1;
	i = move?8:1;
	till = move?14:7;
	for(;i<till;i++)
		if(n->board[i]!=0) {
			is_zero = 0;
			break;
		}
	if(is_zero)
		return 1;
	else
		return 0;		//No zeros
}

int AImove(Node * n) {
	int m;
	int last_rock_pos;
	srand(time(NULL));
	
do {
	print(n->board);
	if(!player_zeros(n,1)) { 
		do {
			m=rand() % 6 + 8;
		} while(legal_move(n,m));
		printf("AI move : %d\n",m-7);
		last_rock_pos=scatter_rocks(n,m,1);
	}
	else {
		last_rock_pos =  -1;
		break;
	}
} while(stop_at_current_player_kalah(n,1,last_rock_pos));
	
	return m;
	
}

int Hmove(Node * n) {
	int last_rock_pos;
	int human_move;
do {
	print(n->board);
	do {
		printf("Enter the number of hole (1-6) : _\b");
		while(scanf("%d",&human_move)!=1) {
			printf("Enter the number of hole (1-6) : _\b");
			getchar();
		}
	} while( (human_move<1 || human_move>6) || legal_move(n,human_move) );
	last_rock_pos = scatter_rocks(n,human_move,0);
} while(stop_at_current_player_kalah(n,0,last_rock_pos));
	return human_move;
}
