#include<stdio.h>

typedef struct process
{
	int pid;
	int arrivalTime;
	int burstTime;
	int waitingTime;
	int turnaroundTime;
	int responseTime;
	int completionTime;
	int isCompleted;
}process;
float avgWaitingTime,avgTurnAround,avgResponseTime;
int totalWaiting=0,totalTurnAround=0,num=999,exe=0,i,j,process_no,temp_comp,min_burst;
process p[20],tmp;

/*void print_struct(process arg[20])
{
	printf("Process Arrival Burst Response Complete\n");
	for(i=0;i<process_no;i++)
	{
		printf("\nP%d  \t%d  \t%d  \t%d  \t%d\n",arg[i].pid,arg[i].arrivalTime,arg[i].burstTime,arg[i].responseTime,arg[i].completionTime);
	}
}*/

void accept()
{
	printf("\nEnter number of processes:");
	scanf("%d",&process_no);
	for(i=0;i<process_no;i++)
	{
		p[i].pid=i+1;
		p[i].isCompleted=0;
		printf("\nEnter Arrivaltime of processes:");
		scanf("%d",&p[i].arrivalTime);
		printf("\nEnter bursttime of process:");
		scanf("%d",&p[i].burstTime);
	}
}
	void sort_arrival()
	{
		for(i=0;i<process_no;i++)
		
			{
for(j=i+1;j<process_no;j++)
{
if(p[i].arrivalTime>p[j].arrivalTime)
{
tmp=p[i];
p[i]=p[j];
p[j]=tmp;
}
}
}                             
				
					p[0].responseTime=p[0].waitingTime=0;
					p[0].completionTime=p[0].burstTime;
					p[0].isCompleted=1;
					temp_comp=temp_comp+p[0].completionTime;
					min_burst=p[1].burstTime;
exe +=1;
}
				
			
		


	void sort_completion()
	{
		for(i=0;i<process_no;i++)
		{
			for(j=i+1;j<process_no;j++)
			{
				if(p[j].completionTime<p[i].completionTime)
				{
					tmp=p[j];
					p[j]=p[i];
					p[i]=tmp;
				}
			}
		}
	}

	void sjf()
	{
for(j=0;j<process_no;j++)
{
		for(i=0;i<process_no;i++)
		{
if(p[i].arrivalTime<=temp_comp &&p[i].burstTime<min_burst &&p[i].isCompleted!=1)
{
min_burst=p[i].burstTime;
num=i;
}
}
}
if(num!=999)
{
min_burst=120;
p[num].completionTime=temp_comp+p[num].burstTime;
temp_comp=p[num].completionTime;
p[num].isCompleted=1;
exe+=1;
}
}


		

	void calculate()
	{
		for(i=0;i<process_no;i++)
		{
			p[i].turnaroundTime=p[i].completionTime-p[i].arrivalTime;
			p[i].waitingTime=p[i].turnaroundTime-p[i].burstTime;
                        p[i].responseTime=p[i].waitingTime;
                       
                        
			totalWaiting=totalWaiting+p[i].waitingTime;
                        totalTurnAround = totalTurnAround+p[i].turnaroundTime;
		}

                 avgWaitingTime = (float)totalWaiting/(float)process_no;
                 avgTurnAround = (float)totalTurnAround/(float)process_no;
		avgResponseTime = avgWaitingTime;
	}

	void print_table()
	{
		printf("\n+---------+-------------+-----------+--------------+-------------+---------------+");
		printf("\n| Process | ArrivalTime | BurstTime | ResponseTime | WaitingTime |TurnAroundTime |");
		printf("\n+---------+-------------+-----------+--------------+-------------+---------------+");
		for(i=0;i<process_no;i++)
		{
			printf("\n|   %d     |    %d        |     %d     |     %d        |     %d        |     %d        |",p[i].pid,p[i].arrivalTime,p[i].burstTime,p[i].responseTime,p[i].waitingTime,p[i].turnaroundTime);
			printf("\n+---------+-------------+-----------+--------------+-------------+---------------+\n");

		}
printf("\n\nAverage Response Time:%f\nAverage Waiting Time: %f\nAverage Turnaround Time:%f\n",avgResponseTime,avgWaitingTime,avgTurnAround);
	}


	void print_gantt_chart()
	{
		// print topbar
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

		//printing process id in middle 
		for(i=0;i<process_no;i++)
		{
			for(j=0;j<p[i].burstTime-1;j++)
			{
				printf(" ");
			}
			printf("P%d",p[i].pid);
			for(j=0;j<p[i].burstTime-1;j++)
			{
				printf(" ");
			}
			printf("|");
		}
		printf("\n ");
		// printing bottom bar 
		for(i=0;i<process_no;i++)
		{
			for(j=0;j<p[i].burstTime;j++)
			{
				printf("--");
			}
			printf(" ");
		}
		printf("\n");

		//printing the time line
		printf("0");
		for(i=0;i<process_no;i++)
		{
			for(j=0;j<p[i].burstTime;j++)
			{
				printf("  ");
			}
			if(p[i].turnaroundTime>9)
			{
				printf("\b");//backspace removes 1 space
			}
			printf("%d",p[i].completionTime);
		}
		printf("\n");
	}
	void main()
	{
		accept();
		sort_arrival();
		while(exe!=process_no)
{
		sjf();
}
		calculate();
                //printf("\n\nWT  : %d,\tTT: %d\n\n",totalWaiting,totalTurnAround);
		sort_completion();
         	print_table();
		print_gantt_chart();
	}




