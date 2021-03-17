#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <time.h>
#include <unistd.h>
#define I 105
#define J 106
#define K 107
#define L 108
#define Esc 27
#define SWAP(x,y) {int temp=x; x=y; y=temp;}

int getch(void) {
    int ch;
    struct termios buf;
    struct termios save;
    tcgetattr(0, &save);
    buf = save;
    buf.c_lflag &= ~(ICANON | ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch=getchar();
    tcsetattr(0, TCSAFLUSH, &save);
    return ch;
}
void print_puzzle(int puzzle[][4]);
void puzzle_1(int puzzle[][4]);
void puzzle_2(int puzzle[][4]);
int is_same(int puzzle[][4],int temp);
int move_puzzle(int puzzle[][4],int *y, int *x,int *move_num);
int game_end(int puzzle[][4],int move_num);

int main(int argc, char * argv[]){
	int x=3,y=3,move_num=0;
	int a;
	int puzzle[4][4]={0};
	if(atoi(argv[1])==1)
		puzzle_1(puzzle);
	else if(atoi(argv[1])==2)
		puzzle_2(puzzle);
	while(game_end(puzzle,move_num)){
		a=move_puzzle(puzzle,&y,&x,&move_num);
		if(a==-1)
			break;
	}
	return 0;
}
void print_puzzle(int puzzle[][4]){
	int x,y;
	printf("\n\n\n\n");
    for(y=0;y<4;y++){
		printf("\n");
		printf("\t\t\t\t");
        for(x=0;x<4;x++){
            if(puzzle[y][x]==0)
                printf("    ");
            else
                printf("%-4d",puzzle[y][x]);
        }
        printf("\n");
    }
}

void puzzle_1(int puzzle[][4]){
	system("clear");
	int x,y,num=1;
	for(y=0;y<4;y++){
		for(x=0;x<4;x++){
			puzzle[y][x]=num++;
			if(puzzle[y][x]==16)
				puzzle[y][x]=0;
		}
	}
	print_puzzle(puzzle);
}
			
void puzzle_2(int puzzle[][4]){
	system("clear");
	srand(time(NULL));
	int x,y,temp;
	for(y=0;y<4;y++){
		for(x=0;x<4;x++){
			if(y==3&&x==3)
				break;
			else{
				temp=rand()%15+1;
				if(is_same(puzzle,temp)==-1){
					puzzle[y][x]=0;
					x--;
				}
				else
				   	puzzle[y][x]=temp;
			}
		}
	}
	print_puzzle(puzzle);
}

int is_same(int puzzle[][4],int temp){
	int x,y;
	for(y=0;y<4;y++){
		for(x=0;x<4;x++){
			if(puzzle[y][x]==temp)
				return -1;
		}
	}
	return 0;
}

int move_puzzle(int puzzle[][4],int *y,int *x,int *move_num){
	int key,temp;
	key=getch();
	switch(key){
		case Esc:
			system("clear");
			return -1;
			break;
		case I:
			if(*y<3){
				system("clear");
				SWAP(puzzle[*y][*x],puzzle[(*y)+1][*x]);
				(*move_num)++;
				(*y)++;
				print_puzzle(puzzle);
			}
			break;
		case J:
			if(*x<3){
            	system("clear");
            	SWAP(puzzle[*y][*x],puzzle[*y][(*x)+1]);
				(*move_num)++;
				(*x)++;
            	print_puzzle(puzzle);
			}
            break;
		case K:
			if(*y>0){
            	system("clear");
            	SWAP(puzzle[*y][*x],puzzle[(*y)-1][*x]);
				(*move_num)++;
				(*y)--;
            	print_puzzle(puzzle);
			}
            break;
		case L:
			if(*x>0){
        		system("clear");
            	SWAP(puzzle[*y][*x],puzzle[*y][(*x)-1]);
				(*move_num)++;
				(*x)--;
            	print_puzzle(puzzle);
			}
            break;
	}
}
int game_end(int puzzle[][4],int move_num){
	int x,y,num=1,end_stack=0;
	int end_puzzle[4][4]={0};
    for(y=0;y<4;y++){
    	for(x=0;x<4;x++){
            end_puzzle[y][x]=num++;
            if(end_puzzle[y][x]==16)
                end_puzzle[y][x]=0;
        }
    }
 	for(y=0;y<4;y++){
		for(x=0;x<4;x++){
			if(puzzle[y][x]==end_puzzle[y][x])
				end_stack++;
		}
	}
	if(end_stack==16 && move_num!=0){
		printf("\n\n");
		printf("\t\t\t\t");
		printf("  축하합니다.\n");
		sleep(3);
		return 0;
	}
	else
		return 1;
}	
