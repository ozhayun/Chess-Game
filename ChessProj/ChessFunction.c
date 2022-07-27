#include "Chess.h"

/*Q1*/
/* This function return all valid moves from every cell in board*/
chessPosArray*** validKnightMoves()
{
	/* Variables definitions*/
	int i, j;

	chessPosArray*** res = (chessPosArray***)malloc((SIZEOFBOARD) * sizeof(chessPosArray**));
	checkAllocation(res);

	for (i = 0; i < SIZEOFBOARD; i++)
	{
		res[i] = (chessPosArray**)malloc((SIZEOFBOARD) * sizeof(chessPosArray*));
		checkAllocation(res[i]);
		for (j = 0; j < SIZEOFBOARD; j++)
		{
			res[i][j] = (chessPosArray*)malloc(sizeof(chessPosArray));
			checkAllocation(res[i][j]);
			res[i][j]->size = getSizePosibleLocations(i, j);
			res[i][j]->positions = getPosibleLocations(res[i][j]->size, i, j);
		}
	}
	return res;
}

/* This function get the number of posibles location from recived cell */
int getSizePosibleLocations(int row, int col)
{
	int size = 0;

	if ((row + 2) < SIZEOFBOARD)
	{
		if ((col + 1) < SIZEOFBOARD)
			size++;
		if ((col - 1) >= 0)
			size++;
	}

	if ((row - 2) >= 0)
	{
		if ((col + 1) < SIZEOFBOARD)
			size++;
		if ((col - 1) >= 0)
			size++;
	}

	if ((col + 2) < SIZEOFBOARD)
	{
		if ((row + 1) < SIZEOFBOARD)
			size++;
		if ((row - 1) >= 0)
			size++;
	}

	if ((col - 2) >= 0)
	{
		if ((row + 1) < SIZEOFBOARD)
			size++;
		if ((row - 1) >= 0)
			size++;
	}
	return size;
}

/* This function get the the posibles location from recived cell */
chessPos* getPosibleLocations(unsigned int size, int row, int col)
{
	chessPos* res = (chessPos*)malloc(size * sizeof(chessPos));
	int resIndex = 0;

	checkAllocation(res);

	if ((row + 2) < SIZEOFBOARD)
	{
		if ((col + 1) < SIZEOFBOARD)
		{
			res[resIndex][0] = (row + 2) + 'A';
			res[resIndex][1] = col + 1 + '0';
			resIndex++;
		}

		if ((col - 1) >= 0)
		{
			res[resIndex][0] = (row + 2) + 'A';
			res[resIndex][1] = col - 1 + '0';
			resIndex++;
		}
	}

	if ((row - 2) >= 0)
	{
		if ((col + 1) < SIZEOFBOARD)
		{
			res[resIndex][0] = (row - 2) + 'A';
			res[resIndex][1] = col + 1 + '0';
			resIndex++;
		}

		if ((col - 1) >= 0)
		{
			res[resIndex][0] = (row - 2) + 'A';
			res[resIndex][1] = col - 1 + '0';
			resIndex++;
		}
	}

	if ((col + 2) < SIZEOFBOARD)
	{
		if ((row + 1) < SIZEOFBOARD)
		{
			res[resIndex][0] = (row + 1) + 'A';
			res[resIndex][1] = col + 2 + '0';
			resIndex++;
		}

		if ((row - 1) >= 0)
		{
			res[resIndex][0] = (row - 1) + 'A';
			res[resIndex][1] = col + 2 + '0';
			resIndex++;
		}
	}

	if ((col - 2) >= 0)
	{
		if ((row + 1) < SIZEOFBOARD)
		{
			res[resIndex][0] = (row + 1) + 'A';
			res[resIndex][1] = col - 2 + '0';
			resIndex++;
		}

		if ((row - 1) >= 0)
		{
			res[resIndex][0] = (row - 1) + 'A';
			res[resIndex][1] = col - 2 + '0';
			resIndex++;
		}
	}
	return res;
}

/* This function check allocation of dynamic array*/
void checkAllocation(void* ptr)
{
	if (ptr == NULL)
	{
		printf("Allocation failed");
		exit(1);
	}
}
/* End of Q1*/


/* Q2*/
/* This function gets list of location and display it on the board*/
void display(chessPosList* lst)
{
	int board[SIZEOFBOARD][SIZEOFBOARD] = { 0 };
	int counter = 1, row, col;

	chessPosCell* currCell = lst->head;
	chessPosCell* prevCell = lst->head;

	while (currCell != NULL)
	{
		row = currCell->position[0] - 'A';
		col = currCell->position[1] - '0';

		/* If cell already in the list remove it*/
		if (isExist(board, row, col))
		{
			removeCellFromList(lst, prevCell, currCell);
			currCell = prevCell;
		}
		else
		{
			board[row][col] = counter;
			counter++;
		}
		prevCell = currCell;
		currCell = currCell->next;
	}
	printBoard(board);
}

/* This function check if cell poss already exist*/
bool isExist(int board[][SIZEOFBOARD], int row, int col)
{
	if (board[row][col] != 0)
		return true;
	else
		return false;
}

/* This function remove cell from list*/
void removeCellFromList(chessPosList* lst, chessPosCell* prevCell, chessPosCell* cellToRemove)
{
	if (lst->head == cellToRemove)
		lst->head = lst->head->next;

	else if (lst->tail == cellToRemove)
	{
		lst->tail = prevCell;
		prevCell->next = NULL;
	}
	else
		prevCell->next = cellToRemove->next;
	free(cellToRemove);
}

/* This function print the board*/
void printBoard(int board[][SIZEOFBOARD])
{
	int row, col, curr;
	char c = 'A';

	printf("  ");
	for (col = 1; col <= SIZEOFBOARD; col++)
		printf("%3d", col);
	printf("\n\n");

	for (row = 0; row < SIZEOFBOARD; row++, c++)
	{
		printf("%c ", c);
		for (col = 0; col < SIZEOFBOARD; col++)
		{
			curr = board[row][col];
			if (curr == 0)
				printf("  ");
			else if (curr / 10 == 0)
				printf("%3d", curr);
			else
				printf("%3d", curr);
		}
		printf("\n\n");
	}
}
/* End of Q2*/


/*Q3*/
/* This function get starting position and return tree of every possible knight moves from this position*/
pathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
	pathTree res;
	chessPosArray*** validKnightMovesArr = validKnightMoves();
	int cellsInPathArr[SIZEOFBOARD][SIZEOFBOARD] = { 0 };
	res.root = buildTreeHelper(validKnightMovesArr, startingPosition, cellsInPathArr);
	return res;
}

/* This recursive function helps us to build the tree paths*/
treeNode* buildTreeHelper(chessPosArray*** validKnightMovesArr, chessPos* startingPosition, int cellsInPathArr[SIZEOFBOARD][SIZEOFBOARD])
{
	/* Variable definition*/
	int row, col, i;
	treeNode* newNode, * currSon;
	treeNodeListCell* currCell;

	row = startingPosition[0][0] - 'A';
	col = startingPosition[0][1] - '0';

	if (cellsInPathArr[row][col] == 1)
		return NULL;

	/* Add myself to cellsInPathArr*/
	cellsInPathArr[row][col] = 1;

	// Create node for myself
	newNode = (treeNode*)malloc(sizeof(treeNode));
	checkAllocation(newNode);
	newNode->position[0] = startingPosition[0][0];
	newNode->position[1] = startingPosition[0][1];
	newNode->next_possible_positions = NULL;

	for (i = 0; i < validKnightMovesArr[row][col]->size; i++)
	{
		currSon = buildTreeHelper(validKnightMovesArr, validKnightMovesArr[row][col]->positions[i], cellsInPathArr);
		if (currSon != NULL)
		{
			currCell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
			checkAllocation(currCell);
			currCell->node = currSon;
			currCell->next = newNode->next_possible_positions;
			newNode->next_possible_positions = currCell;
		}
	}

	// Remove myself from cellsInPathArr
	cellsInPathArr[row][col] = 0;

	return newNode;
}
/*End of Q3*/



/*Q4*/
/* This function check if there is a path in tree that cover all cells in board, 
if yes, it return list of chessPos moves*/
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree)
{
	chessPosList* res = (chessPosList*)malloc(sizeof(chessPosList));
	chessPos arr[SIZEOFBOARD * SIZEOFBOARD];
	int index = 0, maxIndex = 0;

	makeEmptyCPList(res);
	findKnightPathCoveringAllBoardHelper(path_tree->root, res, arr, &index, &maxIndex);

	return res;
}

/* This recurrsive function helps us to build list of path that cover every cells in board, if exist*/
void findKnightPathCoveringAllBoardHelper(treeNode* root, chessPosList* lst, chessPos* arr, int* index, int* maxIndex)
{
	treeNodeListCell* curr;

	if ((root == NULL) || !(isEmptyCPList(lst)))
		return;

	// Add to array
	arr[*index][0] = root->position[0];
	arr[*index][1] = root->position[1];
	(*index)++;
	if (*index > * maxIndex)
		(*maxIndex) = (*index);

	if ((*index) == SIZEOFBOARD * SIZEOFBOARD)
	{
		buildList(lst, arr, *index);
		return;
	}

	curr = root->next_possible_positions;

	// Move on next possible locations
	while (curr != NULL)
	{
		findKnightPathCoveringAllBoardHelper(curr->node, lst, arr, index, maxIndex);
		curr = curr->next;
	}
	(*index)--;
}

/* This function get list and insert cess pos*/
void buildList(chessPosList* lst, chessPos arr[SIZEOFBOARD * SIZEOFBOARD], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		insertDataToEndCPList(lst, arr[i][0], arr[i][1]);
	}
}

/* This function make empty chess pos list*/
void makeEmptyCPList(chessPosList* lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}

/* This function check if lst is empty*/
bool isEmptyCPList(chessPosList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}

/* This function create new chess pos node*/
chessPosCell* createCPNewListNode(char row, char col, chessPosCell* next)
{
	chessPosCell* res;
	res = (chessPosCell*)malloc(sizeof(chessPosCell));
	checkAllocation(res);
	res->position[0] = row;
	res->position[1] = col;
	res->next = next;
	return res;
}

/* This function insert new node to chessPos list*/
void insertDataToEndCPList(chessPosList* lst, char row, char col)
{
	chessPosCell* newTail;
	newTail = createCPNewListNode(row, col, NULL);
	insertNodeToEndList(lst, newTail);
}

/* This function insert node the end of list*/
void insertNodeToEndList(chessPosList* lst, chessPosCell* tail)
{
	if (isEmptyCPList(lst) == true) {
		lst->head = lst->tail = tail;
	}
	else {
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}

/* This function free chessPos list*/
void freeCPList(chessPosList* lst)
{
	chessPosCell* tmp, * curr = lst->head;
	while (curr != NULL)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
}
/*End of Q4*/


/*Q5*/
/* This function save chessPos list to binary file*/
void saveListToBinFile(char* file_name, chessPosList* pos_list)
{
	/*Variable definition*/
	FILE* fb;
	int index = 0;
	short int sizeOfPositions;
	BYTE byte = 0x00, col, row, mask;
	chessPosCell* curr;

	fb = fopen(file_name, "wb");
	checkOpenFile(fb);
	sizeOfPositions = getListLength(pos_list);

	fwrite(&sizeOfPositions, sizeof(short int), 1, fb);
	fflush(fb);

	curr = pos_list->head;

	while (curr != NULL)
	{
		col = curr->position[0] - 'A';
		row = curr->position[1] - '0';

		for (int i = 0; i < 3; i++)
		{
			byte = byte << 1;
			mask = 0x04 >> i;

			if ((col & mask) != 0)
				byte = byte | 0x01;
			index++;

			if (index == 8) 
			{
				fwrite(&byte, sizeof(BYTE), 1, fb);
				byte = 0x00;
				index = 0;
			}
		}

		for (int i = 0; i < 3; i++)
		{
			byte = byte << 1;
			mask = 0x04 >> i;

			if ((row & mask) != 0)
				byte = byte | 0x01;
			index++;

			if (index == 8)
			{
				fwrite(&byte, sizeof(BYTE), 1, fb);
				byte = 0x00;
				index = 0;
			}
		}
		curr = curr->next;
	}

	/* If we didn't finish to fill the byte, fill it we zero*/
	if (index != 0)
	{
		byte = byte << (8 - index);
		fwrite(&byte, sizeof(BYTE), 1, fb);
	}
	fclose(fb);
}

/* This function get chessPos list length*/
short int getListLength(chessPosList* lst)
{
	chessPosCell* curr = lst ->head;
	short int len = 0;

	while (curr != NULL)
	{
		len++;
		curr = curr->next;
	}
	return len;
}

/* This function check that file is opened*/
void checkOpenFile(FILE* f)
{
	if (f == NULL)
	{
		printf("Couldn't open file\n");
		exit(1);
	}
}
/*End of Q5*/


/*Q6*/
/* This function check and display path from binary file*/
int checkAndDisplayPathFromFile(char* file_name)
{
	/* Variable definition*/
	FILE* fb;
	chessPosList* lst;
	bool allCells = false;
	short int numOfPosition;
	int numOfBytes;
	BYTE* tempByteArr;

	fb = fopen(file_name, "rb");
	if (fb == NULL)
		return -1;

	lst = buildListFromFile(fb);

	if (!isValidPath(lst, &allCells))
	{
		return 1;
	}
	else
		display(lst);
	if (allCells)
		return 2;
	else
		return 3;
}

/* This function build chessPos list from binary file*/
chessPosList* buildListFromFile(FILE* file)
{
	/*Variable definition*/
	long int fileSize;
	int countBits = 0, countBytes = 8;
	chessPosList* lst;
	BYTE currByte = 0x0, row, col, mask, bytePosition;
	chessPos currPos;

	fileSize = getSizeOfFile(file);
	fseek(file, 2, SEEK_SET);
	lst = (chessPosList*)malloc(sizeof(chessPosList));
	checkAllocation(lst);
	makeEmptyCPList(lst);

	while (ftell(file) < fileSize)
	{
		if (countBytes - countBits >= 3)
		{
			if ((countBytes - countBits) % 8 == 0)
				fread(&currByte, sizeof(BYTE), 1, file);

			row = currByte >> (countBytes - countBits - 3);
			mask = 0x07;
			row &= mask;
			row += 'A';
			currPos[0] = row;
			countBits += 3;
		}
		else
		{
			bytePosition = bitsToPossition(&currByte, countBits, countBytes, file);
			bytePosition = bytePosition + 'A';
			currPos[0] = bytePosition;
			countBits = countBits + 3;
			countBytes = countBytes + 8;
		}

		if (countBytes - countBits >= 3)
		{
			mask = 0x07;
			col = currByte >> (countBytes - countBits - 3);
			col &= mask;
			col += '0';
			currPos[1] = col;
			countBits += 3;
			if (countBits == countBytes)
				countBytes += 8;
			insertDataToEndCPList(lst, currPos[0],currPos[1]);
		}

		else
		{
			bytePosition = bitsToPossition(&currByte, countBits, countBytes, file);
			bytePosition = bytePosition + '0';
			currPos[1] = bytePosition;
			insertDataToEndCPList(lst, currPos[0], currPos[1]);
			countBits += 3;
			countBytes += 8;
		}
	}
	return lst;
}

/* This function make position Byte*/
BYTE bitsToPossition(BYTE* temp, int countBits, int countBytes, FILE* file)
{
	/* Variable definition*/
	BYTE mask1, mask2, resByte;
	int remainder, moveLeft, moveRight;

	mask1 = *temp;
	remainder = countBytes - countBits;
	moveLeft = 8 - remainder;
	moveRight = moveLeft;

	mask1 = mask1 << moveLeft;
	mask1 = mask1 >> moveRight;
	moveLeft = 3 - remainder;
	mask1 = mask1 << moveLeft;

	fread(temp, sizeof(BYTE), 1, file);

	mask2 = *temp;
	moveRight = 8 - (3 - remainder);
	mask2 >>= moveRight;
	resByte = mask1 | mask2;

	return resByte;
}

/* This function get the size of file*/
long int getSizeOfFile(FILE* file)
{
	long int res;

	fseek(file, 0, SEEK_END);
	res = ftell(file);
	fseek(file, 0, SEEK_SET);
	return res;
}

/* This function check if the path in list is valid*/
bool isValidPath(chessPosList* lst, bool* allCells)
{
	chessPosCell* prev, * curr;
	int tempArr[SIZEOFBOARD][SIZEOFBOARD] = { 0 };
	int row, col, counter = 1;
	bool isValid = true;

	prev = lst->head;
	curr = prev->next;
	row = prev->position[0] - 'A';
	col = prev->position[1] - '0';
	tempArr[row][col] = 1;

	while ((curr != NULL) && (isValid))
	{
		row = curr->position[0] - 'A';
		col = curr->position[1] - '0';
		if (tempArr[row][col] == 0)
		{
			counter++;
			tempArr[row][col] = 1;
		}
		isValid = isValidMove(prev->position, curr->position);
		prev = curr;
		curr = curr->next;
	}

	if (counter == SIZEOFBOARD * SIZEOFBOARD)
		*allCells = true;

	return isValid;
}

/* This function check if the move from chessPos first to second is valid*/
bool isValidMove(chessPos first, chessPos second)
{
	bool res = false;
	if ((first[0] == second[0] + 1) || ((first[0] == second[0] - 1)))
	{
		if ((first[1] == second[1] + 2) || (first[1] == second[1] - 2))
		{
			res = true;
		}
	}

	if ((first[0] == second[0] + 2) || (first[0] == second[0] - 2))
	{
		if ((first[1] == second[1] + 1) || ((first[1] == second[1] - 1)))
		{
			res = true;
		}
	}
	return res;
}


/*****************************************************************/

int che(char* file_name)
{
	FILE* fb;
	chessPosList* lst;
	bool allCells = false;
	short int numOfPosition;
	int numOfBytes;
	BYTE* tempByteArr;

	fb = fopen(file_name, "rb");
	if (fb == NULL)
		return -1;

	fread(&numOfPosition, sizeof(short int), 1, fb);
	numOfBytes = getSizeOfFile(fb);

	tempByteArr = (BYTE*)malloc(numOfBytes * sizeof(BYTE));
	checkAllocation(tempByteArr);

	fread(tempByteArr, sizeof(BYTE), numOfBytes, fb);
	fclose(fb);

	lst = (chessPosList*)malloc(sizeof(chessPosList));
	checkAllocation(lst);
	makeEmptyCPList(lst);
	buildLocationCPLst(lst, numOfPosition, tempByteArr, numOfBytes);

	if (!isValidPath(lst, &allCells))
	{
		return 1;
	}
	else
	{
		display(lst);
	}
	if (allCells)
		return 2;
	else
		return 3;
}



void buildLocationCPLst(chessPosList* lst, int numOfPosition, BYTE* arr, int arrSize)
{
	char row, col;
	BYTE currByte, mask = 0xE0;
	int i, j, bitCount = 0, index = 0;
	bool b_FirstIter = true;

	for (i = 0; i < numOfPosition; i++)
	{
		arr[arrSize - 1] = arr[arrSize - 1] << bitCount;
		currByte = arr[0] & mask;
		row = (currByte >> 5) + 'A';

		if (b_FirstIter)
		{
			b_FirstIter = false;
			bitCount = 3;
		}

		currByte = (arr[0] << bitCount) & mask;
		col = (currByte >> 5) + '0';
		insertDataToEndCPList(lst, row, col);
	}
}



/*****************************************************************/


























































/*End of Q6*/


/*Q7*/
/* This is the game function*/
void play()
{
	int userChose;
	chessPos pos;
	pathTree tr;
	chessPosList *lst = (chessPosList*) malloc(sizeof(chessPosList));

	pos[0] = -1;
	tr.root = NULL;
	checkAllocation(lst);
	makeEmptyCPList(lst);

	printMenu();
	scanf("%d", &userChose);

	while (userChose != 6)
	{
		playMenu(userChose, &pos, &tr, &lst);
		//system("cls");
		printf("\n\n\n\n");
		printMenu();
		if (pos[0] != -1) 
			printf("You choosed position: %c%c\n", pos[0], pos[1]+(char)1);
		scanf("%d", &userChose);
	}
	free(lst);
}

/* This function print the menu of the game*/
void printMenu()
{
	printf("Please choose one of the option:\n");
	printf("1. Enter a knight's starting position\n"
		"2. Create all possible knight paths\n"
		"3. Find a knight path covering all board\n"
		"4. Save knight path covering all board to file\n"
		"5. Load and display path from file\n"
		"6. Exit\n");
}

/* This function get chessPos and check if it in board*/
bool isInBoard(chessPos pos)
{
	bool isValid = true;
	if (((pos[0] - 'A') > SIZEOFBOARD) || ((pos[0] - 'A') < 0) ||
		((pos[1] - '0') > SIZEOFBOARD) || ((pos[1] - '0') < 0))
		isValid = false;
	return isValid;
}

/* This function get possition from user*/
void getPos(chessPos pos)
{
	printf("Please enter row\n");
	scanf(" %c", &pos[0]);
	printf("Please enter col\n");
	scanf(" %c", &pos[1]);
	pos[1] = pos[1] - (char)1;
}

/* This function is handle the options of the menu game*/
void playMenu(int userChose, chessPos pos, pathTree *tr, chessPosList ** lst)
{
	switch (userChose)
	{
	case (1):
	{
		getPos(pos);

		while (!isInBoard(pos))
		{
			printf("You entered wrong posstion, please insert again \n");
			getPos(pos);
		}
			
		break;
	}
	case (2):
	{
		if (pos[0] == -1)
		{
			printf("Please chose first option in the menu before you create all possible paths\n\n");
			Sleep(2000);
			playMenu(1, pos, tr, lst);
		}
		
		*tr = findAllPossibleKnightPaths(pos);
		break;
	}
	case (3):
	{
		if ((tr == NULL) || (pos[0] == - 1))
		{
			playMenu(2, pos, tr, lst);
			printf("Tree created for you\n");
			Sleep(2000);
		}
		*lst = findKnightPathCoveringAllBoard(tr);

		if ((*lst)->head == NULL)
			printf("There isn't path that cover all board cells\n");
		break;
	}
	case (4):
	{
		char str[MAXNAME];
		printf("Please enter file name\n");
		scanf(" %s", str);
		
		if ((*lst)->head == NULL)
		{
			playMenu(3, pos, tr, lst);
			printf("Path list created for you\n");
			Sleep(2000);
		}
		saveListToBinFile(str, *lst);
		break;
	}
	case (5):
	{
		char str[MAXNAME];
		int res;
		printf("Please enter file name\n");
		scanf(" %s", str);
		//res = checkAndDisplayPathFromFile(str);
		res = che(str);

		switch (res)
		{
		case(1):
		{
			printf("Illegal path\n");
			break;
		}
		case(2):
		{
			printf("The path is cover all board cells\n");
			break;
		}
		case(3):
		{
			printf("The path isn't cover all board cells\n");
			break;
		}
		case(-1):
		{
			printf("The file isn't exists\n");
			break;
		}
		break;
		}
	}
	}
}
