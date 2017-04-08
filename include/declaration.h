#ifndef DEFINITIONS
#define DEFINITIONS 1

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>
#include <limits.h>
#include <iomanip>

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#define fe first
#define se second
#define pb push_back
#define INT 1
#define VARCHAR 2


#define BPTREE_MAX_FILE_PATH_SIZE 1000
#define BPTREE_MAX_KEYS_PER_NODE 50
#define BPTREE_INSERT_SUCCESS 1
#define BPTREE_INSERT_ERROR_EXIST 2
#define BPTREE_SEARCH_NOT_FOUND -1


#define ERROR 0
#define SUCCESS 1

#define MAX_VARCHAR 50
#define MAX_ATTR 30
#define MAX_NAME 50
#define MULTIPLICITY 10
#define MAX_PATH 1000

#define MAX_NODE 30

using namespace std;
struct col_details{
	char col_name[20];
	int type;
	int size;
};

struct table{
	int prefix[MAX_ATTR +1];
	col_details col[MAX_ATTR + 1];

	int count; //no. of attributes
	char name[20];//NAME OF TABLE
	int size; //size of record
	int data_size;
	int BLOCKSIZE;
	FILE *fp;
	void *blockbuf;
	int rec_count;
};
#endif
