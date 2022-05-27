/*
	Name: bangGo
	Copyright: OPEN SOURCE
	Author: Baihua2002
	Date: 07/05/22 23:41
	Description: I'm so tired.
*/
#include <iostream>
#include <algorithm>
using namespace std ;

#include <string.h>
#include "hashchess.h"
#include "chessboard.h"
#include "valuation.h"
//#include "trie.h"

#define INF 2147483647

void Init () ;
void setPlayerColor (color C) ;

struct Sol {
	int X , Y ;
	int val ;
};

int cnt = 0 ;
int maxDeep = 10 ;
#define maxDeepMem 10
#define maxCnt 400000
Sol solList[maxDeepMem + 5][N * N + 1] ;
bool cmpForSol (const Sol&A , const Sol &B) {
	return A.val > B.val ;
}

int solX = 0, solY = 0;

int sol (int dep , color cor ) {

	int solCnt = 0 ;

	int fl = 1 ;

	for (int i = 1 ; i <= N ; ++ i) {
		for (int j = 1 ; j <= N ; ++ j) {
			for (int d = 0 ; d < (dN >> 1) ; ++ d) {

				if (A[i][j] == EMPTY) {
					int lLen = getLen (i - dX[d] , j - dY[d] , d + 4, -cor) ;
					int rLen = getLen (i + dX[d] , j + dY[d] , d  , -cor) ;
					int eCnt = (A[i - (lLen + 1) * dX[d]][j - (lLen + 1) * dY[d]] == EMPTY) + (A[i + (rLen + 1) * dX[d]][j + (rLen + 1) * dY[d]] == EMPTY) ;

					if ((lLen + rLen + 1 >= 4 && eCnt >= 1 ) || (lLen + rLen + 1>= 5 )) {


						fl = 0 ;
						++ solCnt ;
						solList[dep][solCnt].X = i ;
						solList[dep][solCnt].Y = j ;
						solList[dep][solCnt].val = emptyPosValue (i , j  , cor) ;
					}
				}

			}

		}
	}

	if (fl) {

		for (int i = 1 ; i <= N ; ++ i) {
			for (int j = 1 ; j <= N ; ++ j) {
				for (int d = 0 ; d < (dN >> 1) ; ++ d) {

					if (A[i][j] == EMPTY) {
						int lLen = getLen (i - dX[d] , j - dY[d] , d + 4, cor) ;
						int rLen = getLen (i + dX[d] , j + dY[d] , d  , cor) ;
						int eCnt = (A[i - (lLen + 1) * dX[d]][j - (lLen + 1) * dY[d]] == EMPTY) + (A[i + (rLen + 1) * dX[d]][j + (rLen + 1) * dY[d]] == EMPTY) ;

						if ((lLen + rLen + 1 >= 4 && eCnt >= 1 ) || (lLen + rLen + 1>= 5 )) {


							fl = 0 ;
							++ solCnt ;
							solList[dep][solCnt].X = i ;
							solList[dep][solCnt].Y = j ;
							solList[dep][solCnt].val = emptyPosValue (i , j  , cor) ;
						}
					}

				}

			}
		}
	}
	if (fl) {
		for (int i = 1 ; i <= N ; ++ i) {
			for (int j = 1 ; j <= N ; ++ j) {

				if (act[i][j] && (A[i][j] == EMPTY)) {
					++ solCnt ;
					solList[dep][solCnt].X = i ;
					solList[dep][solCnt].Y = j ;
					solList[dep][solCnt].val = emptyPosValue (i , j , cor) ;
				}

			}
		}
	}


	sort (solList[dep] + 1 , solList[dep] + 1 + solCnt , cmpForSol) ;
	return solCnt ;

}

int DFS (int depth , int nowVal , int K , int fat ) {
	if (depth > maxDeep) {
		return nowVal;
	}

	if (++ cnt > maxCnt) return 0 ;
	if (K != playerColor ) {
		if (hashTable.checkNode (hashVal))return -INF  ;
		hashTable.addNode (hashVal) ;
		int n = sol (depth , K) ;
		int maxi = 0 , maxj = 0, maxVal = - INF ;

		for (int i = 1 ; i <= n ; ++ i) {
			int X = solList[depth][i].X  , Y = solList[depth][i].Y , V = solList[depth][i].val ;
			putChess (X , Y , K) ;
			int res = DFS (depth + 1 , nowVal + V , -K , maxVal) ;
			delChess (X , Y , K) ;
			if (res > maxVal) {
				maxi = X ;
				maxj = Y ;
				maxVal = res ;
			}

			if (depth && res > fat ) {
				return INF ;
			}
		}

		if (depth == 0 && cnt < maxCnt )	{
			solX = maxi ;
			solY = maxj ;
		}

		return maxVal ;

	} else {

		if (hashTable.checkNode (hashVal)) return INF  ;
		hashTable.addNode (hashVal) ;
		int minVal =  INF ;
		int n = sol (depth , K) ;

		for (int i = 1 ; i <= n ; ++ i) {

			int X = solList[depth][i].X  , Y = solList[depth][i].Y , V = solList[depth][i].val ;

			putChess (X , Y , K) ;
			int res = DFS (depth + 1 , nowVal - V , -K , minVal) ;

			delChess (X , Y , K ) ;
			if (res < minVal) {
				minVal = res ;
			}

			if (res < fat ) return -INF ;

		}

		return minVal ;
	}

}

int fst = 1 ;
void getMet (color cor) {
//	T.TRIEinit () ;
solX = 0 ;solY = 0 ;
	cnt = 0 ;
	for (maxDeep = 0 ; maxDeep < 10 ; ++ maxDeep) {
	
		hashTable.init() ;
		DFS (0 , 0 , computerColor , INF) ;
//		cout << maxDeep << ' ' << cnt << endl;
	}

//	system ("pause") ;
	if (solX == 0 && solY == 0) {
		sol (0 , computerColor) ;
		solX = solList[0][1].X , solY = solList[0][1].Y ;
	}

}

int checkComputerWin () {

	for (int i = 1 ; i <= N ; ++ i) {
		for (int j = 1 ; j <= N ; ++ j) {

			if (A[i][j] != computerColor) continue ;
			for (int d = 0 ; d < (dN >> 1) ; ++ d) {
				if (A[i - dX[d]][j - dY[d]] != computerColor) {
					int len = getLen (i , j , d , computerColor) ;
					int eCnt = (A[i - dX[d]][j - dY[d]] == EMPTY) + (A[i + len * dX[d]][j + len * dY[d]] == EMPTY) ;

					if (len >= 4 && eCnt >= 1) {
						if (A[i - dX[d]][j - dY[d]] == EMPTY) {
							putChess (i - dX[d] , j - dY[d] , computerColor ) ;
						} else {
							putChess (i + len * dX[d] , j + len * dY[d] , computerColor ) ;
						}
						show () ;

						return 1 ;
					}
				}
			}
		}
	}

	return 0 ;
}

int main () {

	Init () ;
	setPlayerColor (BLACK) ;

	while (1) {

		int X = 0 , Y = 0 ;
		scanf("%d%d" , &X , &Y) ;
		int res = putChess (X , Y , playerColor) ;
		isPlayerTurn ^= 1 ;
		show () ;
		if (res) {
			puts ("YOU WON") ;
			return 0 ;
		}
		if (checkComputerWin ()) {
			puts ("YOU LOSS") ;
			return 0 ;
		}

		getMet (computerColor) ;


		putChess (solX , solY , computerColor) ;

		isPlayerTurn ^= 1 ;
		show () ;

	}
	return 0 ;
}

void Init () {

	hashInit () ;
	chessInit () ;
	initValue () ;
}

void setPlayerColor (color C) {
	playerColor = C ;
	computerColor = -C ;
	if (playerColor == WHITE) {
		isPlayerTurn = 0 ;
		putChess ((N + 1) >> 1 , (N + 1) >> 1 , BLACK) ;
	}

	show () ;
}

