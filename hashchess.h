#ifndef hashchess
#define hashchess

#include <stdio.h>
#include "chessboard.h"
typedef unsigned long long Ull ;

Ull hashCode[N * N * 2 + 1] ;
void hashInit () {
	FILE* F;
	fopen_s(&F , "RandNumList.dat", "rb");
	fread (hashCode , sizeof (Ull) , 225 * 2 + 1 , F) ;
	fclose(F);
}

Ull hashVal = 0 ;
void updHashVal (int X , int Y , color cor) {

	int index = 0 ;
	if (cor == WHITE) index = 0 ;
	else index = 1 ;
	hashVal ^= (hashCode[(X - 1) * N + Y + index * (N * N)]) ;

}

class hashTable {

#define MaxNode 1000000

		struct Node {
			Ull data ;
			int nextNode ;
		} H[MaxNode + 5];
		
		#define P 500000
		int Head[P + 5] ;
		int nodeCnt = 0 ;
		
		public :
		void init () {
			memset (Head , 0 , sizeof (Head)) ;
			nodeCnt = 0 ;
		}
		
		void addNode (Ull data) {
			if (nodeCnt >= MaxNode) return ;
			++ nodeCnt ;
			
			int Mod = data % P ;
			H[nodeCnt].data = data ;
			H[nodeCnt].nextNode = Head[Mod] ;
			Head[Mod] = nodeCnt ;
		}
		
		int checkNode (Ull data) {
			for (int i = Head[data % P] ; i; i = H[i].nextNode ) {
				if (H[i].data == data) return 1 ;
			}
			return 0 ;
		}
#undef MaxNode
} hashTable;
#endif
