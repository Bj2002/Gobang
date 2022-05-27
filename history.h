#ifndef HISTORY

#include <stdlib.h>
#include <stdio.h>

typedef unsigned long long Ull;
class historyHashTable {

#define SIZE 10000000

public:
	struct Node {
		Ull hashVal;
		int X, Y;
		Node* nextNode;
	};


	Node* Head[SIZE];
	Node * askhashVal(Ull hashVal) {
		for (Node * i = Head[hashVal % SIZE]; i != NULL; i = i->nextNode) {
			if (i->hashVal == hashVal) {
				return i;
			}
		}
		return NULL;
	}

	void addhashVal(Ull hashVal , int X , int Y) {
		Node* p = (Node*)malloc(sizeof(Node));
		p->hashVal = hashVal;
		p->X = X;
		p->Y = Y;
		p->nextNode = Head[hashVal % SIZE];
		Head[hashVal % SIZE] = p;
	}

	void getHis() {

		FILE* F;
		fopen_s(&F, "DecisionMaking.dat", "rb");

		int x, y;

		int now = 1;
		while (fscanf_s(F , "%d%d", &x, &y) != EOF) {

			if (x == -1) {
				now = 1;
				hashVal = 0;
			}
			else {

				addhashVal(hashVal, x, y);
				updHashVal(x, y, now);
				now = -now;
			}

		}

		hashVal = 0;
	}
} H;
#endif
