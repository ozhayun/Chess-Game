#ifndef CHESS_H
#define  CHESS_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

#define SIZEOFBOARD 5
#define MAXNAME 100


/* Struct definition*/
typedef unsigned char BYTE;
typedef char chessPos[2];
typedef struct _treeNode treeNode;
typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _chessPosArray {
	unsigned int size;
	chessPos* positions;
}chessPosArray;

typedef struct _chessPosCell {
	chessPos position;
	struct _chessPosCell* next;
}chessPosCell;

typedef struct _chessPosList {
	chessPosCell* head;
	chessPosCell* tail;
}chessPosList;

typedef struct _treeNode {
	chessPos position;
	treeNodeListCell* next_possible_positions;
}treeNode;

typedef struct _treeNodeListCell {
	treeNode* node;
	struct _treeNodeListCell* next;
}treeNodeListCell;

typedef struct _pathTree {
	treeNode* root;
}pathTree;


/* Functions declarations*/

/*Q1*/
chessPosArray*** validKnightMoves();
int getSizePosibleLocations(int row, int col);
chessPos* getPosibleLocations(unsigned int size, int row, int col);
void checkAllocation(void* ptr);

/*Q2*/
void display(chessPosList* lst);
void removeCellFromList(chessPosList* lst, chessPosCell* prevCell, chessPosCell* cellToRemove);
bool isExist(int board[][SIZEOFBOARD], int row, int col);
void printBoard(int board[][SIZEOFBOARD]);

/*Q3*/
pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
treeNode* buildTreeHelper(chessPosArray*** validKnightMovesArr,
chessPos* startingPosition, int cellsInPathArr[SIZEOFBOARD][SIZEOFBOARD]);

/*Q4*/
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
void findKnightPathCoveringAllBoardHelper(treeNode* root, chessPosList* lst, chessPos* arr, int* index, int* maxIndex);
void buildList(chessPosList* lst, chessPos arr[SIZEOFBOARD * SIZEOFBOARD], int size);
void makeEmptyCPList(chessPosList* lst);
bool isEmptyCPList(chessPosList* lst);
chessPosCell* createCPNewListNode(char row, char col, chessPosCell* next);
void insertDataToEndCPList(chessPosList* lst, char row, char col);
void insertNodeToEndList(chessPosList* lst, chessPosCell* tail);
void freeCPList(chessPosList* lst);

/*Q5*/
void saveListToBinFile(char* file_name, chessPosList* pos_list);
short int getListLength(chessPosList *lst);
void checkOpenFile(FILE* f);

/*Q6*/
int checkAndDisplayPathFromFile(char* file_name);
BYTE bitsToPossition(BYTE* temp, int countBits, int countBytes, FILE* file);
chessPosList* buildListFromFile(FILE* file);
bool isValidPath(chessPosList* lst, bool* allCells);
bool isValidMove(chessPos first, chessPos second);
long int getSizeOfFile(FILE* file);



void buildLocationCPLst(chessPosList* lst, int numOfPosition, BYTE* arr, int arrSize);
int che(char* file_name);



/*Q7*/
void play();
void printMenu();
bool isInBoard(chessPos pos);
void playMenu(int userChose, chessPos pos, pathTree* tr, chessPosList** lst);
void getPos(chessPos pos);

#endif