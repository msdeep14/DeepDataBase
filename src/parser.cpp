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
/*
// ----------------------------------------------------------------------
 // File    : parser.cpp
 // Author  : Mandeep singh
 // Purpose : parses the query
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
#include "parser.h"
#include "display.h"
#include<cstring>
#include<iostream>

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
    // CREATE TABLE [IF NOT EXISTS] <tablename> (<column1> <datatype>, <column2> <datatype>, PRIMARY KEY(<column1>));

    /*
    * implementation1
    CREATE TABLE <tablename> (<column1> <datatype>, <column2> <datatype>);
    */
    char buffer[1024];
    vector <string> token_vector;

    strcpy(buffer, query);
    char *token = strtok(buffer, " ,;");
    while (token) {
        string token_temp(token);
        if(token_temp != " " && token_temp != "\n" ){
          std::transform(token_temp.begin(), token_temp.end(), token_temp.begin(), ::tolower);
            token_vector.push_back(token_temp);
        }
        token = strtok(NULL, " ,;");
    }

    // for(int i=0;i<token_vector.size();i++){
    //     cout<<token_vector[i]<<endl;
    // }
    cout<<endl;
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

void parse_create(){
  string s;
  cout<<"enter create query\n";
  cin.ignore();
  getline (cin, s);
  int openpos = s.find("(");
  int closepos = s.find(")");
  string token = s.substr(0, openpos);
  string tbetween = s.substr(openpos+1, s.length()-openpos-2);
  cout<<token<<endl;
  cout<<tbetween<<endl;

}
