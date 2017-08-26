/*
// ----------------------------------------------------------------------
 // File    : file_handler.cpp
 // Author  : Mandeep singh
 // Purpose : code for creating new files and folders (file handling operations)
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

#include "file_handler.h"

FILE *open_file(char t_name[] ,char perm[]){

    FILE *fp;
    struct stat st = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    char *name = (char *)malloc(sizeof(char) * (2 * MAX_NAME + 15));
       strcpy(name, "./table/");

    if (stat(name, &st) == -1)
        mkdir(name, 0775);

    strcat(name, t_name);
    strcat(name, "/");

    if (stat(name, &st) == -1)
        mkdir(name, 0775);
    strcat(name, "met");
    fp = fopen(name, perm);
    if (!fp){
        printf("\nError in opening file\n");
    }
    free(name);
    return fp;
}

int store_meta_data(struct table *t_ptr)
{
    FILE *fp = open_file(t_ptr->name, const_cast<char*>("w"));
    fwrite(t_ptr, sizeof(struct table), 1, fp);
    fclose(fp);
    return 0;
}
