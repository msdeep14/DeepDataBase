/*
// ----------------------------------------------------------------------
 // File    : BPtree.h
 // Author  : Mandeep singh
 // Purpose : Header file for btree.cpp
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

#include "declaration.h"

class Btreenode;
class BPtree{
    private:int files_till_now, root_num;
        char tablename[BPTREE_MAX_FILE_PATH_SIZE];

    void write_node(int filenum, Btreenode n);
    void update_meta_data();
public:
    BPtree();
    BPtree(char table_name[]);
    void read_node(int filenum, Btreenode & n);
    int insert_record(int primary_key, int record_num);
    Btreenode search_leaf(int primary_key);
    int get_record(int primary_key);
};
