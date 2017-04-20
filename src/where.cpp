/*
* author - mandeep singh
* 13-04-2017
* copyright 2017 reserved
    GNU GENERAL PUBLIC LICENSE
    Version 3, 29 June 2007

*/

#include "where.h"
#include "BPtree.h"

void select_particular_query(string table_name,string col_to_search,string col_value,std::map<string,int> &display_col_list){
    //process the particular query
    char *tab = (char*)malloc(sizeof(char)*MAX_NAME);
    strcpy(tab,table_name.c_str());
    int check = search_table(tab);
    if(check == 1){
        /*
        access the meta data of table
        */
        table inp1;
        FILE *fp = open_file(tab, const_cast<char*>("r"));
        //if select contains '*'
        if(display_col_list.find("all_columns_set") == display_col_list.end()){
			if(fp){
				fread(&inp1,sizeof(table),1,fp);
				for(int k=0; k<inp1.count; k++){
					string temp_str(inp1.col[k].col_name);
					map<string,int>::iterator it = display_col_list.find(temp_str);
					if(it != display_col_list.end()){
						it->second = 1;
					}
				}
				map<string,int> :: iterator it = display_col_list.begin();
				for(it = display_col_list.begin(); it != display_col_list.end(); it++){
					if(it->second == 0){
						//column dont exist in table, query error
						printf("\nerror\n");
						cout<<it->first<<" is not a valid column for table "<<inp1.name<<"\n";
						return;
					}
				}
			}else{
				printf("\ninternal server error\nexiting...\n");
				return;
			}
		}
        if(fp){
            int pri_int;
            int c;
            char d[MAX_NAME];
            char pri_char[MAX_NAME];
            BPtree mytree(tab);
            int ret=0;
            if(strcmp(inp1.col[0].col_name,col_to_search.c_str()) == 0){
                //primary key, use btree for searching
                if(inp1.col[0].type == INT){
                    pri_int = atoi( col_value.c_str());
                    ret = mytree.get_record(pri_int);
                    if (ret == BPTREE_SEARCH_NOT_FOUND){
                       printf("\nkey %d don't exist!!!\n", pri_int);
                   }else{
                       FILE *fpz;
                       char *str1;
                       printf("\n------------------------------------\n");
                       str1=(char*)malloc(sizeof(char)*MAX_PATH);
                       sprintf(str1,"table/%s/file%d.dat",tab,ret);
                       fpz=fopen(str1,"r");
                       for(int j=0; j < inp1.count;j++){
                           string temp_str(inp1.col[j].col_name);
                               if(inp1.col[j].type==INT){
                                   fread(&c,1,sizeof(int),fpz);
                                   if(display_col_list.find(temp_str) != display_col_list.end())
                                   cout<<c<<"\t";
                               }
                               else if(inp1.col[j].type==VARCHAR){
                                   fread(d,1,sizeof(char)*MAX_NAME,fpz);
                                   if(display_col_list.find(temp_str) != display_col_list.end())
                                   cout<<d<<"\t";
                               }
                       }
                       printf("\n------------------------------------\n");
                       fclose(fpz);
                       free(str1);
                   }
               }else if(inp1.col[0].type==VARCHAR){
                   strcpy(pri_char,col_value.c_str());
                   void *arr[MAX_NAME];
                   arr[0]=(char*)malloc(sizeof(char)*MAX_NAME);
                   arr[0]=pri_char;
                   ret=mytree.get_record(*(int*)arr[0]);
                   if (ret == BPTREE_SEARCH_NOT_FOUND){
                       printf("\nkey %s don't exist !!!\n", pri_char);
                   }
                   else{
                       //print the details of the particular row;
                       FILE *fpz;
                       char *str1;
                       str1=(char*)malloc(sizeof(char)*MAX_PATH);
                       sprintf(str1,"table/%s/file%d.dat",tab,ret);
                       fpz=fopen(str1,"r");
                       printf("\n------------------------------------\n");
                       for(int j=0; j < inp1.count; j++){
                           string temp_str(inp1.col[j].col_name);
                         //  if(display_col_list.find(temp_str) != display_col_list.end()){
                               if(inp1.col[j].type==INT){
                                   fread(&c,1,sizeof(int),fpz);
                                   if(display_col_list.find(temp_str) != display_col_list.end())
                                   cout<<c<<"\t";
                               }
                               else if(inp1.col[j].type==VARCHAR){
                                   fread(d,1,sizeof(char)*MAX_NAME,fpz);
                                   if(display_col_list.find(temp_str) != display_col_list.end())
                                   cout<<d<<"\t";
                               }
                         //  }
                       }
                       printf("\n-------------------------------------\n");
                       fclose(fpz);
                       free(str1);
                   }
               }
            }else{
                //brute force search
                //column entered not a primary key
                /*
                    * identify the column no.
                    * fseek for column in file file%d.dat
                    * check if the entry matches
                */
                int col_number = 1;
                int col_type = 0;
                int flag = 0;
                for(int i = 0; i < inp1.count ;i++){
                    if(strcmp(inp1.col[i].col_name,col_to_search.c_str()) == 0){
                        col_number = i + 1;
                        col_type = inp1.col[i].type;
                        flag = 1;
                        cout<<"col_number,col_type::"<<col_number<<", "<<col_type<<endl;
                        break;
                    }
                }
                if(flag == 0){
                    printf("\ncolumn doesn't exist\nexiting...\n\n");
                    return ;
                }else{
                    //search for entry;
                    flag = 0;
                    int c;
                    char d[MAX_NAME];
                    //cout<<"C........"<<c<<endl;
                    for(int i=0;i<inp1.rec_count;i++){
                            FILE *fpr;
                            char *str;
                            str=(char*)malloc(sizeof(char)*MAX_PATH);
                            sprintf(str,"table/%s/file%d.dat",tab,i);
                            //cout<<str<<endl;
                            fpr=fopen(str,"r");
                            for(int j = 0; j < col_number; j++){
                                //make it more efficient;
                                    if(inp1.col[j].type==INT){
                                        fread(&c,1,sizeof(int),fpr);
                                        //cout<<"c::"<<c<<endl;
                                    }else if(inp1.col[j].type==VARCHAR){
                                        fread(d,1,sizeof(char)*MAX_NAME,fpr);
                                        //cout<<"d:: "<<d<<endl;
                                    }
                            }
                            if(col_type == INT){
                                int col_int_value = atoi( col_value.c_str());
                                if(col_int_value == c){
                                    //display the requried fields
                                    //printf("col_type is int");
                                    int c1;
                                    char d1[MAX_NAME];
                                    fclose(fpr);
                                    fpr=fopen(str,"r");
                                    printf("\n-------------------------------------\n");
                                    for(int j=0; j < inp1.count; j++){
                                        string temp_str(inp1.col[j].col_name);
                                            if(inp1.col[j].type==INT){
                                                fread(&c1,1,sizeof(int),fpr);
                                                if(display_col_list.find(temp_str) != display_col_list.end())
                                                cout<<c1<<"\t";
                                            }
                                            else if(inp1.col[j].type==VARCHAR){
                                                fread(d1,1,sizeof(char)*MAX_NAME,fpr);
                                                if(display_col_list.find(temp_str) != display_col_list.end())
                                                cout<<d1<<"\t";
                                            }
                                    }
                                    printf("\n-------------------------------------\n");
                                    flag = 1;
                                }
                            }else if(col_type == VARCHAR){
                                //cout<<"d,col_value:: "<<d<<" ,"<<col_value.c_str()<<endl;
                                if(strcmp(d,col_value.c_str()) == 0){
                                    //printf("col_type varchar");
                                    int c1;
                                    char d1[MAX_NAME];
                                    fclose(fpr);
                                    fpr=fopen(str,"r");
                                    printf("\n-------------------------------------\n");
                                    for(int j=0; j < inp1.count; j++){
                                        string temp_str(inp1.col[j].col_name);
                                            if(inp1.col[j].type==INT){
                                                fread(&c1,1,sizeof(int),fpr);
                                                if(display_col_list.find(temp_str) != display_col_list.end())
                                                cout<<c1<<"\t";
                                            }
                                            else if(inp1.col[j].type==VARCHAR){
                                                fread(d1,1,sizeof(char)*MAX_NAME,fpr);
                                                if(display_col_list.find(temp_str) != display_col_list.end())
                                                cout<<d1<<"\t";
                                            }
                                    }
                                    printf("\n-------------------------------------\n");
                                    flag = 1;
                                }
                            }else{
                                printf("\ninternal server error\nexiting...\n\n");
                                return;
                            }
                            cout<<"\n\n";
                            free(str);
                            fclose(fpr);
                            if(flag == 1){
                                break;
                            }
                    }
                }
            }
        }
    }
}
