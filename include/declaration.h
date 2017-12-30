/*
// ----------------------------------------------------------------------
 // File    : declaration.h
 // Author  : Mandeep singh
 // Purpose : contains all the declarations of project
 //
 //
 // DeepDataBase, Copyright (C) 2015 - 2017
 //
 // This program is free software; you can redistribute it and/or
 // modify it under the terms of the GNU General Public License as
 // published by the Free Software Foundation; either version 2 of the
 // License, or (at your option) any later version.
 //
 // This program is distributed in the hope that it will be useful,
 // but WITHOUT ANY WARRANTY; without even the implied warranty of
 // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 // General Public License for more details.
 //
 // You should have received a copy of the GNU General Public License along
 // with this program; if not, write to the Free Software Foundation, Inc.,
 // 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

// ----------------------------------------------------------------------
*/

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
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <utility>


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
	FILE *fp; // .rec file
	void *blockbuf; // store the pointers to the blocks of table loaded
	int rec_count; //no of enteries in table
};

//extern functions
//extern void process_select(std::vector <std::string> &token_vector);
extern void create();
extern int search_table(char tab_name[]);
extern void insert();
extern void search();
extern void show_tables();
extern int insert_record(int primary_key, int record_num);
extern FILE *open_file(char t_name[] ,char perm[]);
extern int store_meta_data(struct table *t_ptr);

#endif
