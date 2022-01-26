#include<stdio.h>

typedef struct process
{
	int pid;
	int arrivalTime;
	int responseTime;
	int burstTime;
	int waitingTime;
	int completionTime;
	int turnaroundTime;
	int isCompleted;
	int priority;
}process;

int i,j,process_no,totalWaiting=0,totalTurnaround=0,priority=99999,temp_comp,num=999,exe=0;
float avgWaitingTime,avgTurnaround;
process p[20],tmp;


void accept()
{
	printf("\nEnter the no. of processes: ");
	scanf("%d",&process_no);
	
	for(i=0;i<process_no;i++)
	{
		p[i].pid = i+1;
		printf("Enter Priority of process %d ",p[i].pid);
		scanf("%d",&p[i].priority);
		printf("Enter Arrival Time of process %d ",p[i].pid);
		scanf("%d",&p[i].arrivalTime);
		printf("Enter Burst Time of process %d ",p[i].pid);
		scanf("%d",&p[i].burstTime);
	}
	
	/*process_no = 5;
	p[0].pid = 1;
	p[1].pid = 2;
	p[2].pid = 3;
	p[3].pid = 4;
	p[4].pid = 5;
	
	p[0].arrivalTime = 0;
	p[1].arrivalTime = 3;
	p[2].arrivalTime = 4;
	p[3].arrivalTime = 7;
	p[4].arrivalTime = 1;	

	p[0].burstTime = 10;
	p[1].burstTime = 2;
	p[2].burstTime = 1;
	p[3].burstTime = 5;
	p[4].burstTime = 4;*/
}

void sort_arrival()
{
	for(i=0;i < process_no;i++)
	{
		for(j=i+1;j<process_no;j++)
		{
			if(p[j].arrivalTime < p[i].arrivalTime)
			{
				tmp = p[i];
				p[i] = p[j];
				p[j] = tmp;
			}
		}
	}
	p[0].responseTime = p[0].waitingTime = 0;
	p[0].completionTime = p[0].burstTime;
	p[0].isCompleted = 1;

	temp_comp = temp_comp + p[0].completionTime;
	priority = 99999;
	exe += 1;
}


void sort_compeletion()
{
	for(i=0;i<process_no;i++)
	{
		for(j=i+1;j<process_no;j++)
		{
			if(p[j].completionTime < p[i].completionTime)
			{
				tmp = p[j];
				p[j] = p[i];
				p[i] = tmp;
			}
		}
	}
}

void pnp()
{	
	for(j=0;j<process_no;j++)
	{	
		for(i=0;i<process_no;i++)
		{
			if(p[i].arrivalTime <= temp_comp && p[i].priority < priority && p[i].isCompleted != 1)
			{
				
				priority = p[i].priority;
				num = i;
			}
		}
	}
	
	if(num != 999)
	{
		priority = 120;		
		
		p[num].completionTime = temp_comp + p[num].burstTime;
		temp_comp = p[num].completionTime;		
		p[num].isCompleted = 1;
		exe += 1;	
		
	}
}

void calculate()
{
	for(i=0;i<process_no;i++)
	{
		p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
		p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;
		p[i].responseTime = p[i].waitingTime;
		
		totalWaiting = totalWaiting + p[i].waitingTime;
		totalTurnaround = totalTurnaround + p[i].turnaroundTime;	
	}
	
	avgWaitingTime = (float)totalWaiting / (float)process_no;
	avgTurnaround = (float)totalTurnaround / (float)process_no;
}

void print_table()
{
	puts("+----------+------------+---------------+------------+---------------+-------------+----------------+");
	puts("|  Process |  Priority  |  ArrivalTime  | BurstTime  |  ResponseTime | WaitingTime | TurnAroundTime |");	
	puts("+----------+------------+---------------+------------+---------------+-------------+----------------+");
	
	for(i=0;i<process_no;i++)
	{ 
		printf("|   P%d    |       %d      |       %d      |     %d      |       %d       |      %d      |       %d      |\n",p[i].pid,p[i].priority,p[i].arrivalTime,p[i].burstTime,p[i].responseTime,p[i].waitingTime,p[i].turnaroundTime);
	}
		  puts("+----------+------------+---------------+------------+---------------+-------------+----------------+");
	printf("\n\nArrival Waiting Time : %f\nAverage Turn Around Time : %f\n",avgWaitingTime,avgTurnaround);
}

void print_gantt_chart()
{
	printf(" ");
	for(i=0;i<process_no;i++)
	{
		for(j=0;j<p[i].burstTime;j++)
		{
			printf("--");
		}
		printf(" ");
	}
	printf("\n|");
	
	for(i=0;i<process_no;i++)
	{
		for(j=0;j<p[i].burstTime - 1;j++)
		{
			printf(" ");
		}
		printf("P%d",p[i].pid);
		for(j=0;j<p[i].burstTime - 1;j++)
		{
			printf(" ");
		}	
		printf("|");
	}
	printf("\n ");

	for(i=0;i<process_no;i++)
	{
		for(j=0;j<p[i].burstTime;j++)
		{
			printf("--");
		}
		printf(" ");
	}
	printf("\n");

	printf("0");
	for(i=0;i<process_no;i++)
	{
		for(j=0;j<p[i].burstTime;j++)
		{
			printf("  ");
		}
		if(p[i].turnaroundTime > 9)
		{
			printf("\b");		
		}
		printf("%d",p[i].completionTime);
	}
	printf("\n");
}

int main()
{	
	accept();
	
	sort_arrival();
	
	while(exe != process_no)
	{
		pnp();
	}

	calculate();

	sort_compeletion();

	print_table();

	print_gantt_chart();

}


