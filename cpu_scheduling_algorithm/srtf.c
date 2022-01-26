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
	int startTime;
	int remain;
}process;

int i,j,process_no,totalWaiting=0,totalTurnaround=0,min_burst=99999,clock=0,num=-1,exe=0;
float avgWaitingTime,avgTurnaround;
process p[20],tmp;


void accept()
{
	printf("Enter the no. of processes: ");
	scanf("%d",&process_no);
	getchar();
	
	for(i=0;i<process_no;i++)
	{
		p[i].pid = i+1;
		printf("Enter Arrival Time of process %d : ",p[i].pid);
		scanf("%d",&p[i].arrivalTime);
		getchar();
		printf("Enter Burst Time of process %d : ",p[i].pid);
		scanf("%d",&p[i].burstTime);
		p[i].remain = p[i].burstTime;
		getchar();
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
	p[4].burstTime = 4;

	p[0].remain = 10;
	p[1].remain = 2;
	p[2].remain = 1;
	p[3].remain = 5;
	p[4].remain = 4;*/

}

void print_struct()
{
	for(num=0;num<process_no;num++)
	{		
	printf("\nProcess : %d\tArrival : %d\tBurst : %d\tRemain : %d\tStart : %d\tCompletion : %d",p[num].pid,p[num].arrivalTime,p[num].burstTime,p[num].remain,p[num].startTime,p[num].completionTime);
	}
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
}

void get_srt()
{
	for(i=0;i<process_no;i++)
	{
		if(p[i].arrivalTime <= clock  && p[i].isCompleted == 0)
		{
			if(p[i].remain < min_burst)
			{				
					min_burst = p[i].remain;
					num = i;
			}
			if(p[i].remain == min_burst)
			{
				if(p[i].arrivalTime < p[num].arrivalTime)
				{
					min_burst = p[i].remain;
					num = i;					
				}				
			}
		}
	}
}

void srt()
{		
while(exe != process_no)
{	
	get_srt();
	if(num != -1)
	{	
		
		if(p[num].remain == p[num].burstTime)
		{
			p[num].startTime = clock;
		}		
		p[num].remain = p[num].remain - 1;
		clock++;

		if(p[num].remain == 0)
		{
			p[num].completionTime = clock;			
			p[num].turnaroundTime = p[num].completionTime - p[num].arrivalTime;
			p[num].waitingTime = p[num].turnaroundTime - p[num].burstTime;
			p[num].responseTime = p[num].startTime - p[num].arrivalTime;
						

			min_burst = 99999;
			totalWaiting = totalWaiting + p[num].waitingTime;
			totalTurnaround = totalTurnaround + p[num].turnaroundTime;			
		
			avgWaitingTime = (float)totalWaiting / (float)process_no;
			avgTurnaround = (float)totalTurnaround / (float)process_no;

			p[num].isCompleted = 1;
			exe++;
		}
	}
}
}

void print_table()
{
	puts("+----------+---------------+------------+---------------+-------------+----------------+");
	puts("|  Process |  ArrivalTime  | BurstTime  |  ResponseTime | WaitingTime | TurnAroundTime |");	
	puts("+----------+---------------+------------+---------------+-------------+----------------+");
	
	for(i=0;i<process_no;i++)
	{
		printf("|   P%d    |       %d      |       %d      |     %d     |       %d      |      %d     |\n",p[i].pid,p[i].arrivalTime,p[i].burstTime,p[i].responseTime,p[i].waitingTime,p[i].turnaroundTime);
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
	
	srt();

	print_table();
	
	//print_struct();

	print_gantt_chart();

}
