/*
**
**

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
