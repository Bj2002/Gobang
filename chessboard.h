#ifndef chessboard
#define chessboard

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hashchess.h"
#define N 15
#define BLACK 1
#define WHITE (-1)
#define EDGE 2
#define EMPTY 0
#define dN 8
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define actRange 1

typedef int color ;
color playerColor = BLACK ;
color computerColor = WHITE ;
int isPlayerTurn = 0 ;
int A[N + 2][N + 2] ;

const int dX[] = {-1 , -1 , 0 , 1 , 1 , 1 , 0 , -1} ;
const int dY[] = {0 , 1 , 1 , 1 , 0 , -1 , -1 , -1} ;
int act[N + 2][N + 2] ;

void chessInit () {
	memset (A , 0 , sizeof (A)) ;
	memset (act , 0 , sizeof (act)) ;
	for (int i = 0 ; i <= (N + 1) ; ++ i) {
		A[i][0] = A[i][N + 1] = EDGE ;
		A[0][i] = A[N + 1][i] = EDGE ;
	}
}

extern int cnt ;
extern unsigned long long hashVal ;
void show ()  {
//	system ("pause") ;
	system ("CLS") ;
	printf ("   ") ;
	for (int i = 1 ; i <= N; ++ i ) printf ("%2d" , i) ;
	putchar ('\n') ;
	for (int i = 1 ; i <= N; ++ i) {
		printf ("%2d " , i ) ;
		for (int j = 1 ; j <= N ; ++ j) {
			if (A[i][j] == BLACK) printf ("〇") ;
			else if (A[i][j] == WHITE)printf ("●") ;
			else if (A[i][j] == EMPTY) printf ("十") ;
		}
		putchar ('\n') ;
	}
	
	cout << "当前局面哈希值：" << hashVal << endl;
	cout << "搜索局面数：" << cnt << endl;
}

void markPos (int X , int Y , int dlt) {
	for (int i = X - 1 ; i <= X + 1 ; ++ i) {
		for (int j = Y - 1 ; j <= Y + 1 ; ++ j) {
			act[i][j] += dlt ;
		}
	}

}

extern void updHashVal (int X , int Y , color cor) ;

int putChess (int posX , int posY , color cor) {

//	if (A[posX][posY]) return 1 ;
	A[posX][posY] = cor ;
	markPos (posX , posY , 1) ;
	updHashVal (posX , posY , cor) ;

	for (int i = 0 ; i < (dN >> 1) ; ++ i) {
		int lX = posX - dX[i] , lY = posY - dY[i] ;
		int rX = posX + dX[i] , rY = posY + dY[i] ;

		int lRange = 0 , rRange = 0 ;
		while (A[lX][lY] == cor) {
			lX -= dX[i] ;
			lY -= dY[i] ;
			++ lRange ;
		}
		while (A[rX][rY] == cor) {
			rX += dX[i] ;
			rY += dY[i] ;
			++ rRange ;
		}

		int len = rRange + lRange + 1 ;
		if (len >= 5) return 1 ;
	}

	return 0 ;

}

int delChess (int posX , int posY , color cor) {

//	if (A[posX][posY] == EMPTY) return 1 ;
	A[posX][posY] = EMPTY ;
	markPos (posX , posY , -1) ;
	updHashVal (posX , posY , cor) ;
	return 0 ;

}


int getLen (int X , int Y , int d , color cor) {
	int res = 0 ;
	while (A[X][Y] == cor) {
		++ res ;
		X += dX[d] , Y += dY[d] ;
	}
	return res ;
}
#endif
