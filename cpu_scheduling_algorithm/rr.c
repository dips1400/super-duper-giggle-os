#include<stdio.h>
int n,q[20],front=-1,rear=-1;
struct proc
{
	int no,at,bt,ct,tat,wt,completed,bt1,cur,visited,res;
};

void enqueue(int i)
{
	if(rear==20)
		printf("Overflow");
	rear++;
	q[rear] = i;
	if(front==-1)
		front = 0;
}

int dequeue()
{
	if(front==-1)
		printf("Underflow");
	int temp = q[front];
	if(front==rear)
		front = rear = -1;
	else
		front++;
	return temp;
}

int IsInQueue(int i)
{
	int k;
	for(k=front;k<=rear;k++)
	{
		if(q[k]==i)
			return 1;
	}
	return 0;
}

struct proc read(int i)
{
	struct proc p;
	printf("Enter details of process %d",i);
	p.no = i;
	printf("\nEnter Burst time : ");
	scanf("%d",&p.bt);
	printf("Enter Arrival time : ");
	scanf("%d",&p.at);
	p.bt1 = p.bt;
	p.completed = 0;
	p.visited = 0;
	return p;
}

void main()
{
	int i,j,time=0,remaining,tq;
	struct proc p[20],temp;
	float avgtat=0,avgwt=0,avgres=0;
	printf("\nEnter number of processes : ");
	scanf("%d",&n);
	printf("Enter time quantum : ");
	scanf("%d",&tq);
	for(i=0;i<n;i++)
	{
		printf("\n");
		p[i] = read(i+1);
	}
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(p[j].at>p[j+1].at)
			{
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
		}
	}
	remaining = n;
	enqueue(0);
	printf("\nGantt Chart : \n");
	printf("|0");
	for(time=p[0].at;remaining!=0;)
	{
		i = dequeue();
		if(p[i].visited == 0)
		{
			p[i].cur = time;
			p[i].visited = 1;
		}
		if(p[i].bt1<=tq)
		{
			time += p[i].bt1;
			p[i].bt1 = 0;
			p[i].completed = 1;
			remaining--;
			printf(" P%d",p[i].no);
			printf(" %d|%d",time,time);
			p[i].ct = time;
			p[i].tat = p[i].ct-p[i].at;
			p[i].wt = p[i].tat - p[i].bt;
			avgtat += p[i].tat;
			avgwt += p[i].wt;
			for(j=0;j<n;j++)
			{
				if(p[j].at<=time && p[j].completed!=1 && IsInQueue(j)!=1)
				{
					enqueue(j);
				}
			}
		}
		else
		{
			if(p[i].visited == 0)
			{
				p[i].cur = time;
				p[i].visited = 1;
			}
			time += tq;
			p[i].bt1 -= tq;
			printf(" P%d",p[i].no);
			printf(" %d|%d",time,time);
			for(j=0;j<n;j++)
			{
				if(p[j].at<=time && p[j].completed!=1 && IsInQueue(j)!=1 && i!=j)
				{
					enqueue(j);
				}
			}
			enqueue(i);
		}
	}
	printf("\n\nPid\tBT\tAT\tCT\tRT\tTAT\tWT");
	for(i=0;i<n;i++)
	{
		p[i].res = p[i].cur-p[i].at;
		avgres += p[i].res;
		printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d",p[i].no,p[i].bt,p[i].at,p[i].ct,p[i].res,p[i].tat,p[i].wt);
	}
	avgtat = avgtat/n;
	avgwt = avgwt/n;
	avgres = avgres/n;
	printf("\nAverage turnaround time : %f",avgtat);
	printf("\nAverage waiting time : %f",avgwt);
	printf("\nAverage response time : %f\n",avgres);
}