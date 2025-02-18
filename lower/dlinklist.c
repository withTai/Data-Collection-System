//#include <QtGui>
#include "dlinklist.h"
//头结点应该没有数据，否则如果把头结点当作第一个节点(含数据)，到时候删除第一个节点不好弄

void init_dlinklist(DLIST *d)
{
	d->next=NULL;
}

void create_dlinklist(DLIST *d,char *s[],int size)
{
	DLIST *p;
	DLIST *r=d;
	int i,j=0;
	for(i=0;i<size;i++)
	{
		j++;
		p=(DLIST*)malloc(sizeof(DLIST));
		memset(p,0,sizeof(p));
		strcpy(p->path,s[i]);
		r->next=p;
		if(j>1)
		{
			p->prev=r;
		}
		r=p;
	}
	r->next=d->next;
	d->next->prev=r;
}

int legnth_dlinklist(DLIST *d)	//不包括头结点
{
	int len=0;
	DLIST *p=d->next;
	while(p->next!=d->next)
	{
		p=p->next;
		len++;
//		printf("\n%s\n",p->path);
	}
	return len+1;
}

void show_dlinklist(DLIST *d)
{
	DLIST *p=d->next;
	while(p->next!=d->next)
	{
		printf("%s\t",p->path);		//正向
		p=p->next;
	}	
	printf("%s\t",p->path);

/*	DLIST *r;
	while(p->next!=d->next)
	{
		p=p->next;
	}
	printf("%s\n",p->path);
	r=p;
	while(p->prev!=r)
	{
		p=p->prev;
		printf("%s\n",p->path);		//反向
	}	*/
}

void del_dlinklist(DLIST *d,int pos)
{
	DLIST *p=d->next;
	DLIST *r;
	int i,len=legnth_dlinklist(d);
	if(pos<=0)
	{
		printf("invaild position\n");
		exit(1);
	}
	if(pos>len)pos=len;
	if(pos==1)
	{
		r=d->next;
		while(p->next!=d->next)
		{
			p=p->next;
		}
		p->next=r->next;
		d->next=r->next;
		r->next->prev=p;
		free(r);		//如果free(d)则行不通，会产生段错误
	}
	else
	{
		for(i=0;i<pos-2;i++)
		{
			p=p->next;
		}
		r=p->next;
		p->next=r->next;
		r->next->prev=p;
		free(r);
	}
}

/*
void insert_dlinklist(DLIST *d,char *s)	//这里是末尾添加
{
//	DLIST *p=d;
//	DLIST *q;
	p=d;
	q=(DLIST*)malloc(sizeof(DLIST));
	memset(q,0,sizeof(q));
	strcpy(q->path,s);

	if(p->next==NULL)
	{
		p->next=q;
		q->next=NULL;
	}
	else
	{
		while(p->next!=NULL)
		{
			p=p->next;
		}
		p->next=q;
		q->prev=p;
		q->next=NULL;
	}
	printf("insert success\n");
}	*/

void dlinkilist_tofile(DLIST *d)
{
	FILE *fp;
	DLIST *p=d->next;
	if((fp=fopen("n1.dat","wb"))==NULL)
	{
		perror("open failed");
		exit(-1);
	}
	while(p->next!=d->next)
	{
//		if(fwrite(p->path,sizeof(p->path),1,fp)==1)
		if(fwrite(p,sizeof(DLIST),1,fp)==1)
		{
//			printf("%s\n",p->path);			
			p=p->next;
		}
		else
		{
			perror("file write error!");
			break;
		}
	}
	fwrite(p,sizeof(DLIST),1,fp);
//	fwrite(p->path,sizeof(p->path),1,fp);
	fclose(fp);
}

void file_tolinklist(DLIST *d)
{
	FILE *fp;
	DLIST *p=d;
	DLIST *r;
	int i=0;
//	p->next=NULL;
	if((fp=fopen("n1.dat","rb"))==NULL)
	{
		perror("open failed");
		exit(-1);
	}
	r=(DLIST*)malloc(sizeof(DLIST));
	while(fread(r,sizeof(DLIST),1,fp)==1)
	{
		printf("%s\n",r->path);
		i++;
		p->next=r;
		if(i>1)
		{
			r->prev=p;
		}
		p=r;
		r=(DLIST*)malloc(sizeof(DLIST));
	}
	p->next=d->next;		//注意: 不是 r->next=d->next;
	d->next->prev=r;
}
