/*
Assigned by:
Illya Naumenko 342418035
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


void GreedyColoring();

typedef struct Interval {
	int low;
	int high;
}interval;

typedef struct Graph {
	int color;
	int deg;
}graph;

void main()
{
	GreedyColoring();
}

void GreedyColoring()
{
	int k, j, i ;
	int color = 1;
	int countGedges = 0, countGcompedges = 0;
	printf("Please input k \n");
	scanf_s("%d", &k);

	interval *arr;
	arr = (interval*)calloc(k, sizeof(interval));
	assert(arr);

	graph *Garr; 
	Garr = (graph*)calloc(k, sizeof(graph));
	assert(Garr);

	int* colorarray;
	colorarray = (int*)calloc(k + 1, sizeof(int));
	assert(colorarray);

	printf("You will now be asked to insert a family of %d intervals:\n", k);

	for (i = 0; i < k; i++) 
	{
		printf("%dth Interval:\n", i + 1);
		scanf_s("%d", &(arr[i]).low); 
		scanf_s("%d", &(arr[i]).high); 
	}
	printf("The Intervals family is:\n");

	for (i = 0; i < k; i++) 
	{
		printf("[%d,%d]", arr[i].low, arr[i].high);
		if (i != k - 1)
			printf(","); 
	}
	printf("\n");

	for (i = 0; i < k - 1; i++) 
								
	{
		for (j = 0; j < k - 1; j++)
		{
			if (arr[j].low > arr[j + 1].low || (arr[j].low == arr[j + 1].low && arr[j].high > arr[j + 1].high)) 
			{
				interval temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	for (i = 0; i < k - 1; i++) 
	{
		for (j = i + 1; j < k; j++)
		{
			if (arr[i].low == arr[j].low || arr[i].high >= arr[j].low || (arr[i].high <= arr[j].high && arr[i].high >= arr[j].low))
			{
				countGedges++; 
				Garr[i].deg++; 
				Garr[j].deg++; 
			}
		}
	}

	int maxdeg = Garr[0].deg; 
	int mindeg = Garr[0].deg; 

	for (i = 1; i < k; i++) 
	{
		if (Garr[i].deg >= maxdeg)
			maxdeg = Garr[i].deg;
		else if (Garr[i].deg <= mindeg)
			mindeg = Garr[i].deg;
	}


	for (i = 0; i < k; i++) 
	{
		Garr[i].color = color;
	}


	for (i = 1; i < k; i++) 
	{
		for (j = i - 1; j >= 0; j--)
		{
			if (arr[j].low == arr[i].low || arr[j].high >= arr[i].low || (arr[j].high <= arr[i].high && arr[j].high >= arr[i].low))
			{
				colorarray[Garr[j].color]++; 
			}

			for (int t = 1; t < k + 1; t++) 
			{
				if (colorarray[t] == 0)
				{
					Garr[i].color = t; 
					break;
				}
			}

		}
		for (int m = 1; m < k + 1; m++) 
		{
			colorarray[m] = 0;
		}

	}

	for (i = 0; i < k; i++)
	{
		if (color < Garr[i].color) 
			color = Garr[i].color;
	}

	for (i = 0; i < k; i++)
	{
		colorarray[Garr[i].color]++; 
	}

	printf("G Edges = %d\n", countGedges);
	printf("Maximum Degree of G = %d\n", maxdeg); 
	printf("Minimum Degree of G = %d\n", mindeg); 
	printf("Chromatic Number of G = %d\n", color);
	countGcompedges = (k*(k - 1) / 2) - countGedges; 
	printf("G's Complement Edges = %d\n", countGcompedges);

	if (countGcompedges != 0) 
	{
		printf("Maximum Degree of G's Complement = %d\n", k - 1 - mindeg);
		printf("Minimum Degree of G's Complement = %d\n", k - 1 - maxdeg);
	}
	else
	{
		printf("Maximum Degree of G's Complement = 0\n"); 
		printf("Minimum Degree of G's Complement = 0\n"); 
	}

	int p = 1; 
	printf("Optional Coloring: ");

	while (p <= color) 
	{
		printf("{");
		for (i = 0; i < k; i++)
		{
			if (Garr[i].color == p)
			{
				colorarray[p]--; 
				printf("[%d,%d]", arr[i].low, arr[i].high); 
				if (colorarray[p] != 0)
					printf(","); 
			}
		}
		printf("} = %d", p);
		if (p != color)
		{
			printf(", ");
		}
		p++;
	}
	
	printf("\n");
	free(colorarray); 
	free(Garr); 
	free(arr); 

	system("pause");
}
