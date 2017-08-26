/*
// ----------------------------------------------------------------------
 // File    : drop.h
 // Author  : Mandeep singh
 // Purpose : contains code for deletion of table
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

void drop(){
	char *tab;
	char *temp;
	char *temp1;
	temp1=(char*)malloc(sizeof(char)*MAX_NAME);
	temp=(char*)malloc(sizeof(char)*MAX_NAME);
	tab=(char*)malloc(sizeof(char)*MAX_NAME);
	cout<<"\nenter table name to delete: ";
	cin>>tab;
	strcpy(temp1,tab);
	int check=search_table(tab);
	if(check==0) printf("\n%s doesn't exist\n\n",tab);
	else if(check==1){
		sprintf(temp, "rm -R ./table/%s", tab);
		system(temp);
		//copy all the table names to new temp excluding given table to delete;
		sprintf(temp, "grep -v \"%s\" ./table/table_list > ./table/temp ; mv ./table/temp ./table/table_list", tab);
        system(temp);
        printf("\n%s deleted\n\n",temp1);
		printf("-------------------------------");
	}
	else{
		printf("\nerror\nexiting...\n\n");
		return;
	}
}
