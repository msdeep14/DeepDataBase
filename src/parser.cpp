// process a query
/*
    * author - mandeep singh
    * 13-04-2017
    * copyright 2017 reserved
        GNU GENERAL PUBLIC LICENSE
        Version 3, 29 June 2007

*/

/*
    * QUERIES (terminate with semicolon(;), tokens should be space separated)
    1. SELECT * FROM TABLE_NAME; OR SELECT COL1,COL2... FROM TABLE_NAME;

*/
#include "parser.h"
#include "display.h"

//tokenize select query for processing
void tokenize_select(char query[]){
    // break the query into tokens
    char buffer[1024];
    vector <string> token_vector;
    //vector <string> temp;
    strcpy(buffer, query);
    char *token = strtok(buffer, " ,;");
    while (token) {
        string token_temp(token);
        if(token_temp != " " && token_temp != "\n" ){
            token_vector.push_back(token_temp);
        }
        token = strtok(NULL, " ,;");
    }
    process_select(token_vector);
}

//tokenize create query for processing
void tokenize_create(char query[]){
    /*
        create table table_name(id int not null,name varchar(20),city varchar(30) not null, primary key(id));
    */

}

void get_query(){
    char *query;
    query = (char*) malloc (sizeof(char)*50);
    printf("enter query to test\n");
    fflush(stdin);
    fflush(stdout);
    fgets(query,sizeof(char)*MAX_NAME,stdin);
    fgets(query,sizeof(char)*MAX_NAME,stdin);

    //
    char buffer[1024];
    strcpy(buffer, query);
    char *token = strtok(buffer, " ");
    if(token){
        string token_temp(token);
        if(token_temp != " " && token_temp != "\n"){
            //cout<<"token:: "<<token<<endl;
            if(token_temp == "select"){
                tokenize_select(query);
            }else if(token_temp == "create"){
                tokenize_create(query);
            }
        }
    }


    //printf("\nquery:: %s\n",query);
}

/*
int main(){
    get_query();

    return 0;
}
*/
