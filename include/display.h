#include "declaration.h"

void display(){
	char *tab;
	tab=(char*)malloc(sizeof(char)*MAX_PATH);
	cout<<"enter table name to display\n";
	cin>>tab;
	int ret=search_table(tab);
	if(ret==0) {
		printf("%s doesn't exist\n\n",tab);
		return ;
	}
	else if(ret==1){
		//table exists

		table *temp;
		int count;
		int tot=0;
		temp=(table*)malloc(sizeof(table));
		printf("\n-----------------------------------------------\n");
		FILE *fp=open_file(tab,const_cast<char*>("r"));
		if(fp){
			fread(temp,1,sizeof(table),fp);
			count=temp->count;
			void *data2[MAX_ATTR];
			for(int i=0;i<count;i++){
				cout<<temp->col[i].col_name<<setw(20);
				if(temp->col[i].type==INT)
				{
					data2[i] =(int*) malloc(sizeof(int));
					if(data2[i]==NULL)
					{
						cout<<"NULL";
						return;
					}
					tot+=sizeof(int);
				}
				else if(temp->col[i].type==VARCHAR)
				{
					data2[i] = malloc(sizeof(char) * (MAX_NAME + 1));
					if(data2[i]==NULL)
					{
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
					}
					else if(temp->col[j].type==VARCHAR){
						fread(d,1,sizeof(char)*MAX_NAME,fpr);
						cout<<d<<setw(20);
					}
				}
				cout<<"\n\n";

				free(str);
				fclose(fpr);
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
