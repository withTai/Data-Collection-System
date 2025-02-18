#ifndef DLINK_H
#define DLINK_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

typedef struct dlist
{
	char path[100];
	struct dlist *prev;
	struct dlist *next;		//也可以与path分开写
}DLIST;

void init_dlinklist(DLIST *d);
void create_dlinklist(DLIST *d,char *s[],int size);
int legnth_dlinklist(DLIST *d);
void show_dlinklist(DLIST *d);
void del_dlinklist(DLIST *d,int pos);
//void insert_dlinklist(DLIST *d,char *s);

void dlinkilist_tofile(DLIST *d);
void file_tolinklist(DLIST *d);

#endif
