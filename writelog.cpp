#include <stdio.h>
#include <string.h>
#include <iostream>
#include <graphics.h>
using namespace std;

#define N 15
typedef int color;
#define WHITE (-1)
#define BLACK 1
#define EMPTY 0
typedef unsigned long long Ull;

int A[N + 1][N + 1] ;

#define blockSize 40
#define chessSize 35
void graphInit () {
	initgraph ((N + 2) * blockSize, (N ) * blockSize) ;
	setbkcolor (LIGHTGRAY) ;
	setcolor (BLACK) ;
	for (int i = 0 ; i < N ; ++ i) {
		line (blockSize * i  + (blockSize >> 1), blockSize >> 1, blockSize * i + (blockSize >> 1), (N ) * blockSize - (blockSize >> 1)) ;
		line (blockSize >> 1, blockSize * i + (blockSize >> 1), (N ) * blockSize - (blockSize >> 1), blockSize * i + (blockSize >> 1)) ;
	}
	
	setcaption ("Ð´ÈëÆåÆ×") ;
	
	outtextxy(blockSize * N, 100 , "EXIT") ;
}

void putChess (int x , int y , int cor) {
	if (cor == -1) setfillcolor (WHITE) ;
	else setfillcolor (BLACK ) ;
	
	fillellipse (y * blockSize - (blockSize >> 1) , x * blockSize - (blockSize >> 1) , chessSize >> 1, chessSize >> 1) ;
}
int main() {
//	readLog () ;

	FILE *F = fopen ("DecisionMaking.dat", "ab+") ;
	int c = 1 ;

	graphInit () ;
	while (1) {

		int x = 0, y = 0;
		mouse_msg m = getmouse () ;
		if (m.is_down ()) {
			x = m.x / blockSize ;
			y = m.y / blockSize ;
			swap (x , y) ;
			++ x ;
			++ y ;
			if (x >= 3 && x <= 4 && y > 15) {
				fprintf (F, "%d %d\n", -1, -1) ;
				fclose (F) ;
				return 0 ;
			}
		
			if (!A[x][y]) {
				A[x][y] = c;
				putChess( x , y , c) ;
				c = -c;
				fprintf (F, "%d %d\n", x, y) ;
				cout << x << ' ' << y << endl;
			}

		}
	}

	return 0;
}
