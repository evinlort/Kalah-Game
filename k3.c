#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "minmax.c"



int main(void) {

Node * root;
int move;
int player_move;
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
//	do {
		print(root->board);
		if(move) {
			player_move = AImove(root);
			//scatter_stops = minmax(root);
		}
		else {
			player_move = Hmove(root);		
			//scatter_stops = scatter_rocks(root,human_move,move);
		}
//	} while(stop_at_current_player_kalah(root,move,scatter_stops));
	move=move?0:1;
	printf("Move is %s - %d\n",move?"AI":"H",player_move);
}
print(root->board);
printf("Winner is '%s'\n",root->board[0]>root->board[7]?"AI":"Human");
return 0;
}
//TODO AImove and Hmove
