
#ifndef VALUATION
#define VALUATION

int aliveCnt[dN >> 1][N + 2][N + 2] ;
int len[dN >> 1][N + 2][N + 2] ;
const int chessVal[] = {0 , 10, 100 , 1000 , 10000 ,	100000 , 100000} ;
int Value = 0 ;
void initValue () {
	memset (aliveCnt , 0 , sizeof (aliveCnt)) ;
	memset (len , 0 , sizeof (len)) ;
}

int checkOutRange (int x , int y) {
	return (x < 1 || x > N || y < 1 || y > N ) ;
}

int emptyPosValue (int x , int y , color cor) {

	int delta = 0 ;
	for (int i = 0 ; i < (dN >> 1) ; ++ i) {
		int lX = x - dX[i] , lY = y - dY[i] ;
		int rX = x + dX[i] , rY = y + dY[i] ;

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
		int lEcnt = (A[lX][lY] == EMPTY) , rEcnt = (A[rX][rY] == EMPTY) ;

		int emptyCnt = lEcnt + rEcnt - 1;
		delta +=  chessVal[len + emptyCnt ] ;

		if (lRange)delta -= chessVal[lEcnt + lRange] ;
		if (rRange)delta -= chessVal[rEcnt + rRange] ;

	}

//	cout << delta << endl;
	for (int i = 0 ; i < (dN >> 1); ++ i) {
		int lX = x - dX[i] , lY = y - dY[i] ;
		int rX = x + dX[i] , rY = y + dY[i] ;

		int lRange = 0 , rRange = 0 ;
		while (A[lX][lY] == -cor) {
			lX -= dX[i] ;
			lY -= dY[i] ;
			++ lRange ;
		}
		while (A[rX][rY] == -cor) {
			rX += dX[i] ;
			rY += dY[i] ;
			++ rRange ;
		}

		int lEcnt = (A[lX][lY] == EMPTY) , rEcnt = (A[rX][rY] == EMPTY) ;

		if (lRange)delta += chessVal[lEcnt + lRange] - chessVal [lEcnt];
		if (rRange)delta += chessVal[rEcnt + rRange] - chessVal [rEcnt];

	}
	return delta ;

}

void markPosValue (int x , int y , color cor) {

	int delta = emptyPosValue (x , y , cor) ;
	if (cor == computerColor)Value += delta ;
	else Value -= delta ;
//	cout << delta <<' ' << Value << endl;
}



#endif
