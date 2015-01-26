
struct Node {
	int board[14];
	struct Node * parent;
	struct Node * child[6];
	int value;
	int next_turn;
	int next_move;
};

typedef struct Node Node;

Node * init(void);
int game_is_not_finished();
int minmax(Node*);
int scatter_rocks(Node *,int,int);
int stop_at_current_player_kalah(int,int);
void need_to_grab(int,int,Node*);
void grab(int,int,Node*);
void print(int*);
int legal_move(Node*,int);
