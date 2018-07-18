#include<stdio.h>


typedef struct
{
	HDR_L *fptr;
	HDR_L *bptr;
}HDR_L;

HDR_L* head_list;

typedef struct
{
	int mid;
	int sid;
	int active;
}evtdb_list;
void main()
{
	int a;
	evtdb_list *new_node;
	while(1)
	{
		printf("Press 1 to add an item in list");
		scanf("%d",&a);
		
		switch(a)
		{
			case 1:
				new_node = (evtdb_list *) malloc (sizeof(evtdb_list));
				printf("Enter mid");
				scanf("%d",&new_node->mid);
				printf("Enter cid");
				scanf("%d",&new_node->cid);
				printf("Enter active");
				scanf("%d",&new_node->active);
				
				break;
			case 2:
				for(ptr=head_list)	
				
		}
	}
}


void create_list(HDR_L *head,evtdb_list *cur_node)
{
	if(head==null)
	{
		head->fptr
	}
}
