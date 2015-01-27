#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "minmax.c"



int main(void) {

Node * root;
int move;
int human_move;
int scatter_stops;
root = init();

do {
	printf("Choose player, who will start first ( 0 - Human, 1 - AI ) : _\b");
	while(scanf("%d",&move)!=1) {
		printf("Choose player, who will start first ( 0 - Human, 1 - AI ) : _\b");
		getchar();
	}
} while(move<0 || move>1);
while(game_is_not_finished(root)) {
	do {
		print(root->board);
		if(move) {
			scatter_stops = minmax(root);
		}
		else {
			do {
				printf("Enter the number of hole (1-6) : _\b");
				while(scanf("%d",&human_move)!=1) {
					printf("Enter the number of hole (1-6) : _\b");
					getchar();
				}
			} while( (human_move<1 || human_move>6) || legal_move(root,human_move) );
					
			scatter_stops = scatter_rocks(root,human_move,move);
		}
	} while(stop_at_current_player_kalah(root,move,scatter_stops));
	move=move?0:1;
	printf("Move is %d\n",move);
}
print(root->board);
printf("Winner is 'Human/AI'\n");
return 0;
}
