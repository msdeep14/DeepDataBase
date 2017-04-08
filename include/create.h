#include "declaration.h"
#include "file_handler.h"

int record_size(table *temp){
	int size=0;
	temp->prefix[0]=0;
	for(int i=0;i<temp->count;i++){
		switch(temp->col[i].type){
		case INT:
			temp->prefix[i+1]=sizeof(int)+temp->prefix[i];
			size+=sizeof(int);
			break;
		case VARCHAR:
			temp->prefix[i+1]=sizeof(char)*(MAX_VARCHAR +1) +temp->prefix[i];
			size+=sizeof(char)*(MAX_VARCHAR +1);
			break;
		}
	}
	return size;
}

//verify input
/*
void verify_input_size_and_type(string type, string size){

}*/

table * create_table(char name[],int count){
	table *toreturn = new table();
	table *temp=new table();
	temp->fp=NULL;
	temp->blockbuf=NULL;
	strcpy(temp->name,name);
	temp->name[strlen(name)]='\0';
	temp->count=count;
	temp->rec_count=0;
	temp->data_size=0;

	//enter the data for columns of table
	int i=0;
	cout<<"Enter column name,Data type(1.int 2.varchar) and max size(max allowed int=6,char=99) of column\n";
	for(i=0;i<count;i++){
		string type;
		string size;
		//verify_input_size_and_type(type,size);
		cin>>temp->col[i].col_name>>type>>size;
		//check if entered datatype no. is correct
		if(type.length()>1){
			printf("\nwrong input(datatype should be (1=int or 2=varchar))\nexiting...\n\n");
			printf("-------------------------------------------------------------------------\n");
			return NULL;
		}else{
			if(type[0] == 49 || type[0] == 50){
				temp->col[i].type = type[0]-48;
			}else{
				printf("\nwrong input(datatype should be (1=int or 2=varchar))\nexiting...\n\n");
				printf("-------------------------------------------------------------------------\n");
				return NULL;
			}
		}
		//check size input;
		if(size.length() > 2){
			printf("\n123wrong input\nmax size(max allowed int=6,char=99), exiting...\n");
			printf("---------------------------------------------------------------------\n");
			return NULL;
		}else{
			if(type[0] == 49){
				if(size.length() > 1){
					printf("\n124wrong input, max size allowed for int = 6\nexiting...\n");
					printf("--------------------------------------------------------\n");
					return NULL;
				}else{
					if(size[0] > 48 && size[0] < 55){
						temp->col[i].size = size[0] -48;
					}else{
						printf("\n125wrong input, max size allowed for int = 6\nexiting...\n");
						printf("--------------------------------------------------------\n");
						return NULL;
					}
				}
			}else if(type[0] == 50){
				if(size[0] > 48 && size[0] < 58){
					if(size.length() == 1){
						temp->col[i].size = size[0] -48;
					}else if(size.length() == 2){
						temp->col[i].size = (size[0] - 48)*10 + (size[1] - 48);
					}else{
						printf("\nwrong input\nmax size(max allowed char=99), exiting...\n");
						printf("---------------------------------------------------------------------\n");
						return NULL;
					}
				}
			}
		}
	}
	if(i<count){
		printf("\n\tYou have not entered all details of columns\n\n");
		return NULL;
	}
	else{
		toreturn = temp;
		return toreturn;
	}
}

void create(){
	char *name;
	int count;
	name=(char*)malloc(sizeof(char)*MAX_NAME);
	cout<<"Enter table name: ";
	cin>>name;

	//check if new table already exists in table list or not
	FILE *fp=fopen("./table/table_list","r+");
	if(fp==NULL) cout<<"file pointer is null\n";
	char tab_name[20];
	while(fscanf(fp,"%s",tab_name)!=EOF){
		if(strcmp(tab_name,name)==0){
			cout<<"error\ntable name already exists\n";
			return;
		}
	}

	//enter table details if not exist
	cout<<"enter no. of columns: ";
	cin>>count;
	table *temp;
	temp=create_table(name,count);
	if(temp != NULL){
	//calculate the size of the block
		temp->size=record_size(temp);
		if(temp!=NULL){
		temp->blockbuf = malloc(temp->BLOCKSIZE);
		FILE *fpr;
        fpr  = open_file(temp->name, const_cast<char*>("w"));
        fwrite(temp->blockbuf, 1, temp->BLOCKSIZE, fp);
        fclose(fpr);
        store_meta_data(temp);
        free(temp->blockbuf);
		free(temp);

		//if its a new table, make a entry inside table_list
		fseek(fp,0,SEEK_END);
		fprintf(fp,"%s\n",name);
		fclose(fp);
		free(name);
	}else{
		      printf("create_table inside CREATE function returned NULL\n");
		       // return 1;
		 }
	 }else{
		 //printf("\nwrong input\nexiting...\n\n");
		 return;
	 }

}
