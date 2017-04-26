/**/

#include "insert.h"
#include "file_handler.h"
#include "BPtree.h"
#include "aes.h"

int search_table(char tab_name[]){
	//check if new table already exists in table list or not

		//use grep to search table_name string inside table_list
		// -F -> --fixed-strings ;intepret pattern as a list of fixed strings
		// -x -> --line-regexp ;select only those matches that exactly match the whole line
		// -q -> quite, --silent ;write anything to standard output, exit immediately with zero status if any match is found
		char str[MAX_NAME+1];
		strcpy(str,"grep -Fxq ");
		strcat(str,tab_name);
		strcat(str," ./table/table_list");
		int x = system(str);
		if(x==0)return 1;
		else return 0;
	return 0;
}

void insert_command(char tname[],void *data[],int total){
	table *temp;
	int ret;
	BPtree obj(tname);
	//open meta data
	FILE *fp=open_file(tname,const_cast<char*>("r"));
	temp=(table*)malloc(sizeof(table));
	fread(temp,sizeof(table),1,fp);

	//insert into table and write to btree file nodes
	ret=obj.insert_record(*((int *)data[0]),temp->rec_count);
	if(ret==2){
		cout<<"key already exists\n";
		cout<<"exiting...\n";
		return ;
	}

	//if no error occurred during insertion of key

	//update the meta data;
	fp=open_file(tname,const_cast<char*>("w+"));
	int file_num=temp->rec_count;
	temp->rec_count=temp->rec_count+1;
	temp->data_size=total;
	fwrite(temp,sizeof(table),1,fp);
	fclose(fp);

	//update the particular entry of inserted data to file;
	char *str;
	str=(char *)malloc(sizeof(char)*MAX_PATH);
	sprintf(str,"table/%s/file%d.dat",tname,file_num);
	//cout<<str<<endl;
	FILE *fpr=fopen(str,"w+");
    int x;
	char y[MAX_NAME];
	for(int j=0;j<temp->count;j++){
		if(temp->col[j].type==INT){
			 x = *(int *)data[j];
			fwrite(&x,sizeof(int),1,fpr);
		}
		else if(temp->col[j].type==VARCHAR){
			strcpy(y,(char *)data[j]);
			fwrite(y,sizeof(char)*MAX_NAME,1,fpr);
		}
	}
	fclose(fpr);
	free(str);
	free(temp);

}


void insert(){
	char *tab;
	tab=(char*)malloc(sizeof(char)*MAX_PATH+1);
	cout<<"enter table name: ";
	cin>>tab;
	int check=search_table(tab);
	if(check==0){
		printf("Table %s not exists\n",tab);
		return ;
	}

	else{
		cout<<"\nTable exists enter data\n\n";
		char dir[100];
		strcpy(dir,"./table/");
		strcat(dir,tab);
		strcat(dir,"/met");
     	table inp1;
		int count;
		//read column details from file;
		FILE *fp = open_file(tab, const_cast<char*>("r"));
		int i=0;
		while(fread(&inp1,sizeof(table),1,fp)){
			printf("------------------------------------\n");
			cout<<"\ninsert the following details ::\n";
			printf("\n------------------------------------\n");
			count=inp1.count;
			for(i=0;i<inp1.count;i++){
				cout<<inp1.col[i].col_name<<"("<<inp1.col[i].type<<"),size:"<<inp1.col[i].size;
				cout<<"\t";
			}
		}
		printf("\n------------------------------------\n");
		//enter data;
		char var[MAX_NAME+1];
		void * data[MAX_ATTR];
		//void *data1[MAX_ATTR];

		//input data for the table of desired datatype 1.int 2.varchar;
		int size=0;
		int total=0;
		for(int i=0;i<count;i++){
			if(inp1.col[i].type==INT){
				data[i] =(int*) malloc(sizeof(int));
				total+=sizeof(int);
				string inp_int;
				cin>>inp_int;
				if(inp_int.length() > (unsigned)inp1.col[i].size){
					printf("\nwrong input, size <= %d\nexiting...\n",inp1.col[i].size);
					return;
				}else{
					//verify if entered input is integer and not a string;
					int num = 0;
					int factor_10 = 1;
					for(int j=inp_int.length()-1;j>=0;j--){
						if(inp_int[j] < 48 || inp_int[j] > 57){
							printf("\nwrong input, input should be integer\nexiting...\n");
							return;
						}else{
							num += (inp_int[j] - 48)*factor_10;
							factor_10 = factor_10 * 10;
						}
					}
					*((int*)data[i])=num;
				}
				size++;
			}else if(inp1.col[i].type==VARCHAR){
				//cout<<"inside varchar\n";
				data[i] = malloc(sizeof(char) * (MAX_NAME + 1));
				int flag=1;
				while(flag){
					cin>>var;
					total+=sizeof(char) * (MAX_NAME + 1);
					if(strlen(var)>(unsigned int)inp1.col[i].size){
						cout<<"error\nEntered size of string is greater than specified \n";
					}else flag=0;
				}
				strcpy((char*)(data[i]),var);
				//cout<<(char *)data[1]<<endl;
				size++;
			}
		}
		insert_command(tab,data,total);
	}
	free(tab);
}
