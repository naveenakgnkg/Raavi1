#include <stdio.h> 
#include <stdlib.h> 
//#include "task_queue.h"
#include <string.h>
 
 int rear=-1,front=-1;
 int count=0;
 
   struct task { 
    int id;
    char * sender;
    char * destination;
    char * message_type;
    int processing_attempts;
    char * status;
     
};
struct task t1[50];
void enqueue(struct task t )
{
if (front==-1)
	front=0;
printf("insert the element in queue\n");
rear=rear+1;
t1[rear].id=t.id;
t1[rear].sender=t.sender;
t1[rear].destination=t.destination;
t1[rear].message_type=t.message_type;
t1[rear].processing_attempts=1;
t1[rear].status="available";
count++;
}

void dequeue()
{
	if(front ==-1 || front>rear)
	{
		printf("no elements present");
		front=-1;
		rear=-1;
	}
	else
	{
		printf("deleted id is %d\n",t1[front].id);
		front=front+1;
		count=count-1;
	}
}

void display ()
{
int i;
	if (front==-1)
		printf("no elements");
	else
	{
	for(i=front;i<front+count;i++)
	{
		printf("id =%d ",t1[i].id);
		printf("sender =%s ",t1[i].sender);
		printf("destination =%s ",t1[i].destination);
		printf("message_type =%s ",t1[i].message_type);
		printf("processing_attempts =%d ",t1[i].processing_attempts);
		printf("status =%s \n",t1[i].status);
	}
	}
}

int request_process()
{
	int i=front;
	
	if (front==-1)
		printf("no elements");
	else
	{
	while(i<=rear)
	{
		
		if(!(strcmp(t1[i].status,"available")))
		{
			if(t1[i].processing_attempts<99)
			{
				t1[i].status="taken";
				t1[i].processing_attempts++;
				//transport and transform table
			}
			
			else
				t1[i].status="failed";
				//clean up;
		}
		i++;
	}
	}
}
int main()
{


struct task temp;
temp.id=10;
temp.sender="abc10";
temp.destination="xyz10";
temp.message_type="xml";

enqueue(temp);

temp.id=11;
temp.sender="abc11";
temp.destination="xyz11";
temp.message_type="xml";

enqueue(temp);
display();
request_process();
dequeue();

display();
return 0;
}
