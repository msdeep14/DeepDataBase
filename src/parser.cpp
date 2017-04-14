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
    1. SELECT * FROM TABLE_NAME;

*/
#include "parser.h"

void tokenize(char query[]){
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
    /*
    for(unsigned int i = 0; i < temp.size(); i++){
        if(temp[i].size() == 1 && temp[i][0] == 59){
            //do nothing, terminate the string after the semicolon
            break;
        }else if(temp[i][temp[i].size() - 1] == ';' || temp[i][temp[i].size() - 1] == ','){
            string new_token_string = temp[i].substr(0,temp[i].size()-2);
            token_vector.push_back(new_token_string);
        }else{
            token_vector.push_back(temp[i]);
        }
    }
    temp.clear();
    */

    /*
        if token[0] dont belong to {"select","create","insert","drop","describe","show"}, then ERROR
    */
    if(token_vector[0] == "select"){
        process_select(token_vector);
    }else{
        printf("\nsyntax error\n");
        return;
    }
    /*
    for(int i=0;i<token_vector.size();i++){
        cout<<token_vector[i]<<"\n";
    }*/

    // store tokens into particular data structure

}

void get_query(){
    char *query;
    query = (char*) malloc (sizeof(char)*50);
    printf("enter query to test\n");
    fflush(stdin);
    fflush(stdout);
    fgets(query,sizeof(char)*MAX_NAME,stdin);
    fgets(query,sizeof(char)*MAX_NAME,stdin);
    /*
    //take input until ';' is entered
    if(strcmp(query[strlen(query)-1],';') != 0){

    }*/
    tokenize(query);
    //printf("\nquery:: %s\n",query);
}

/*
int main(){
    get_query();

    return 0;
}
*/
