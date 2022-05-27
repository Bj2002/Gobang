#ifndef LOG
	#define LOG
#include "chessboard.h"
struct Log {
	int turn;
	int data[N + 1][N + 1];
} l;

extern void setPlayerColor(color);
extern int A[N + 2][N + 2];
void readLog() {
	FILE* F;
	fopen_s(&F, "log.dat", "rb");
	
	fread(&l, sizeof(Log), 1, F);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			A[i][j] = l.data[i][j];
			if (A[i][j]) {
				putChess(i, j, A[i][j]);
			}
		}
	}

	setPlayerColor(l.turn);

	fclose(F);
}

void writeLog() {
	FILE* F;
	fopen_s(&F, "log.dat", "wb");

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			l.data[i][j] = A[i][j];
		}
	}
	l.turn = playerColor;
	fwrite(&l, sizeof(Log), 1, F);
	fclose(F);
}

#endif