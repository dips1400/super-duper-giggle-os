#include<stdio.h>
void main()
{
	int a[100]; //An integer array to store the disk requests
	int b[100]; //An integer array to store the initial disk request sequence
	int SeekDistance[100]; //An Array to store individual Seek distances
	int distance, num_requests, i, j, temp, shortest_distance;
	int swap = 0, tot_distance = 0, z = 0;


	//Fetch # requests to be processed
	printf("\nEnter the number of requests (max 100) :\n");
	do
	{
		scanf("%d", &num_requests);
		if (num_requests <= 0 || num_requests > 100)
			printf("Please enter a proper number of requests!!!\n");
	} while (num_requests <= 0 || num_requests>100);

	//Fetch initial Head Position
	printf("Enter the initial head position:\n");
	scanf("%d", &a[0]);

	//Read All requests
	printf("\nEnter %d valid disk processing requests\n", num_requests);
	for (i = 1; i <= num_requests; i++)
	{
		scanf("%d", &a[i]);
	}

	//Copy Initial Sequence into another list
	for (i = 1; i <= num_requests; i++)
	{
		b[i] = a[i];
	}

	//Identify the next request with the shortest distance
	for (i = 0; i<num_requests; i++)
	{
		shortest_distance = abs(a[i] - a[i + 1]);

		for (j = i + 1; j <= num_requests; j++)
		{

			distance = abs(a[i] - a[j]);

			if (distance <= shortest_distance)
			{
				shortest_distance = distance;
				swap = j;
			}
		}
		SeekDistance[i] = shortest_distance;
		tot_distance = tot_distance + (shortest_distance);

		//Move the completed requests
		temp = a[i + 1];
		a[i + 1] = a[swap];
		a[swap] = temp;
		
	}
	printf("\n****************Final Output****************\n");
	printf("\n Initial Head Position is %d:\n\n", a[0]);

	printf("Shortest seek \t   Individual Seek Length\n");
	printf("----------------------------------------------\n");

	for (i = 0; i < num_requests; i++)
	{
		printf(" %d\t\t\t %d\n",  a[i+1], SeekDistance[i]);
		//printf("\n%d", b[i]);
	}
	printf("\nTotal Head Movement:%d", tot_distance);
	printf("\n");

}