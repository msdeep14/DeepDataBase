
/**/

#include "display.h"
#include "file_handler.h"

void display(char tab[], std::map<string,int> &display_col_list);

void process_select(vector <string> &token_vector){
	std::map <std::string,int> display_col_list;
	int numOfCol = 0;
	//set which columns to display
	if(token_vector[1][0] == 42){
		display_col_list.insert(make_pair("all_columns_set",0));
		numOfCol = 1;
	}else{
		for(unsigned int i=1; i<token_vector.size()-2; i++){
			if(token_vector[i] == "from"){
				break;
			}else{
				//cout<<token_vector[i]<<endl;
				numOfCol += 1;
				display_col_list.insert(make_pair(token_vector[i],0));
			}
		}
	}

	if(token_vector[token_vector.size() - 1] == " " || token_vector[token_vector.size() - 1] == "\n"){
		printf("\ninternal server error\n");
		return;
	}
	const char *name = (char*)malloc(sizeof(char)*MAX_NAME);
	name = token_vector[numOfCol + 2].c_str();
	display((char*)name,display_col_list);
}

void display(char tab[], std::map<string,int> &display_col_list){
	vector<int> store_col_no;
	int ret=search_table(tab);
	if(ret==0) {
		printf("%s doesn't exist\n\n",tab);
		return ;
	}else if(ret==1){
		table *temp;
		int count;
		int tot=0;
		temp=(table*)malloc(sizeof(table));
		FILE *fp=open_file(tab,const_cast<char*>("r"));
		//table exists
		//now check if entered columns are valid
		if(display_col_list.find("all_columns_set") == display_col_list.end()){
			if(fp){
				fread(temp,1,sizeof(table),fp);
				for(int k=0; k<temp->count; k++){
					string temp_str(temp->col[k].col_name);
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
						cout<<it->first<<" is not a valid column for table "<<temp->name<<"\n";
						return;
					}
				}
			}else{
				printf("\ninternal server error\nexiting...\n");
				return;
			}
		}
		/*
			while iterating through the columns, check in set if that column is asked in select query;
		*/

		if(fp){
			fread(temp,1,sizeof(table),fp);
			count=temp->count;
			if(temp->count == 0 || temp->rec_count == 0){
				system("clear");
				printf("\ntable empty\n\n");
				return;
			}
			store_col_no.assign(count,0);
			void *data2[MAX_ATTR];
			//display all columns;
			printf("\n-----------------------------------------------\n");
			if(display_col_list.find("all_columns_set") != display_col_list.end()){
				for(int i=0;i<count;i++){
						cout<<temp->col[i].col_name<<setw(20);
						if(temp->col[i].type==INT)
						{
							data2[i] =(int*) malloc(sizeof(int));
							if(data2[i]==NULL){
								cout<<"NULL";
								return;
							}
							tot+=sizeof(int);
						}else if(temp->col[i].type==VARCHAR){
							data2[i] = malloc(sizeof(char) * (MAX_NAME + 1));
							if(data2[i]==NULL){
								cout<<"NULL";
								return;
							}
							tot+=(sizeof(char) * (MAX_NAME + 1));
						}
				}
				fclose(fp);
				cout<<"\n";
				printf("-----------------------------------------------\n");

				int c;
				char d[MAX_NAME];
				//cout<<"C........"<<c<<endl;
				for(int i=0;i<temp->rec_count;i++){
						FILE *fpr;
						char *str;
						str=(char*)malloc(sizeof(char)*MAX_PATH);
						sprintf(str,"table/%s/file%d.dat",tab,i);
						//cout<<str<<endl;
						fpr=fopen(str,"r");
						//cout<<*(int *)data1[0]<<" ";
						//fread(data2,temp->count,tot,fpr);
						//fread(data2,1,tot,fpr);
						for(int j=0;j<temp->count;j++){
							if(temp->col[j].type==INT){
								fread(&c,1,sizeof(int),fpr);
								cout<<c<<setw(20);
							}else if(temp->col[j].type==VARCHAR){
								fread(d,1,sizeof(char)*MAX_NAME,fpr);
								cout<<d<<setw(20);
							}
						}
						cout<<"\n\n";
						free(str);
						fclose(fpr);
				}
			}else{ //display selected columns;
				for(int i=0;i<count;i++){
					string temp_col_name(temp->col[i].col_name);
					if(display_col_list.find(temp_col_name) != display_col_list.end()){
						store_col_no[i] = 1;
						cout<<temp->col[i].col_name<<setw(20);
						if(temp->col[i].type==INT){
							data2[i] =(int*) malloc(sizeof(int));
							if(data2[i]==NULL){
								cout<<"NULL";
								return;
							}
							tot+=sizeof(int);
						}else if(temp->col[i].type==VARCHAR)
						{
							data2[i] = malloc(sizeof(char) * (MAX_NAME + 1));
							if(data2[i]==NULL){
								cout<<"NULL";
								return;
							}
							tot+=(sizeof(char) * (MAX_NAME + 1));
						}
					}
				}
				fclose(fp);
				cout<<"\n";
				printf("-----------------------------------------------\n");

				int c;
				char d[MAX_NAME];
				//cout<<"C........"<<c<<endl;
				for(int i=0;i<temp->rec_count;i++){
						FILE *fpr;
						char *str;
						str=(char*)malloc(sizeof(char)*MAX_PATH);
						sprintf(str,"table/%s/file%d.dat",tab,i);
						//cout<<str<<endl;
						fpr=fopen(str,"r");
						for(int j=0;j<temp->count;j++){
							if(store_col_no[j] == 1){
								if(temp->col[j].type==INT){
									fread(&c,1,sizeof(int),fpr);
									cout<<c<<setw(20);
								}else if(temp->col[j].type==VARCHAR){
									fread(d,1,sizeof(char)*MAX_NAME,fpr);
									cout<<d<<setw(20);
								}
							}
						}
						cout<<"\n\n";
						free(str);
						fclose(fpr);
				}
			}

			printf("-----------------------------------------------\n");
					//fclose(fp);
		}
	}
}

void show_tables(){
	char *name;
	printf("\n\nLIST OF TABLES\n\n");
	printf("---------------------------\n");
	int tabcount=0;
	name=(char*)malloc(sizeof(char)*MAX_NAME);
	FILE *fp=fopen("./table/table_list","r+");
	while(fscanf(fp,"%s",name)!=EOF){
		tabcount++;
		cout<<name<<"\n";
	}
	if(tabcount==0) printf("Database empty!!!\n");
	printf("---------------------------\n");
	free(name);
}
