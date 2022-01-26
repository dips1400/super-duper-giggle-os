#include<stdio.h>

typedef struct process
{
	int pid;
	int arrivalTime;
	int responseTime;
	int burstTime;
	int waitingTime;
	int completionTime;
	int turnAroundTime;
}process;

int i,j,process_no = 0,totalWaiting,totalTurnaround;
float avgWaitingTime = 0,avgTurnaroundTime = 0;
process p[20],tmp;

void accept()
{
	printf("\nEnter the no. of processes: ");
	scanf("%d",&process_no);
	
	for(i=0;i<process_no;i++)
	{
		p[i].pid = i+1;
		printf("Enter Arrival Time of process %d ",p[i].pid);
		scanf("%d",&p[i].arrivalTime);
		printf("Enter Burst Time of process %d ",p[i].pid);
		scanf("%d",&p[i].burstTime);
	}
	
	/*process_no = 4;
	p[0].pid = 1;
	p[1].pid = 2;
	p[2].pid = 3;
	p[3].pid = 4;
	
	p[0].arrivalTime = 0;
	p[1].arrivalTime = 3;
	p[2].arrivalTime = 8;
	p[3].arrivalTime = 2;	

	p[0].burstTime = 8;
	p[1].burstTime = 1;
	p[2].burstTime = 5;
	p[3].burstTime = 3;*/

}

void sort()
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
}

void calculate()
{
	p[0].responseTime = p[0].waitingTime = 0;
	p[0].completionTime = p[0].completionTime + p[0].burstTime;
	
	for(i=0;i < process_no;i++)
	{
			
		p[i+1].completionTime = p[i].completionTime + p[i+1].burstTime;
		p[i].turnAroundTime = p[i].completionTime - p[i].arrivalTime;
		p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;
		p[i].responseTime = p[i].waitingTime;			
		totalWaiting = totalWaiting + p[i].waitingTime;
		totalTurnaround = totalTurnaround + p[i].turnAroundTime;
	}

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
		if(p[i].turnAroundTime > 9)
		{
			printf("\b");		
		}
		printf("%d",p[i].completionTime);
	}
	printf("\n");
}

void print_table()
{
	puts("+----------+---------------+------------+---------------+-------------+----------------+");
	puts("|  Process |  ArrivalTime  | BurstTime  |  ResponseTime | WaitingTime | TurnAroundTime |");	
	puts("+----------+---------------+------------+---------------+-------------+----------------+");
	
	for(i=0;i<process_no;i++)
	{
		printf("|   P%d    |       %d        |     %d      |       %d       |      %d      |       %d       |\n",p[i].pid,p[i].arrivalTime,p[i].burstTime,p[i].responseTime,p[i].waitingTime,p[i].turnAroundTime);
	}
		  puts("+----------+---------------+------------+---------------+-------------+----------------+");
	//printf("\n\nArrival Waiting Time : %f\nAverage Turn Around Time : %f\n",avgWaitingTime,avgTurnaroundTime);
}

int main()
{
	
	accept();
	sort();
	calculate();
	

	printf("\n\n");
	
	print_table();	
	
	avgWaitingTime = (float)totalWaiting / (float)process_no;
	avgTurnaroundTime = (float)totalTurnaround / (float)process_no;
	printf("\nAverage Waiting Time : %f\n",avgWaitingTime);
	printf("\nAverage Turn Around Time : %f\n",avgTurnaroundTime);
	printf("\n");

	print_gantt_chart();
	
	return 0;
	
}


