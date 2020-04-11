#define _CRT_SECURE_NO_WARNINGS
#define NODE_SIZE 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct Vector {
	char* data;
	size_t size, capacity;
} Vector;

typedef struct Node {
	char data[NODE_SIZE];
	struct Node* next;
} Node;

void main() 
{
	const int textSize = 120;
	int numberOfNodes = (textSize + NODE_SIZE - 1) / NODE_SIZE;
	int count, positionInNode;
	char nodeData[NODE_SIZE];
	bool toUpper = false;
	int s = 2, n = 5, countS, countN;
	Node* current;
	
	//Measuring time values to work with
	clock_t start1, start2, end1, end2;
	long double cpu_time_used1, cpu_time_used2;

	//Creating text data to work with
	char text[] = "So\nLet's test the different methods of saving data\nThe goal is to compare time & memory usage\nLet the experiment begin!";

	//Entering text data to the Vector representation
	Vector vec = { text, textSize, textSize };

	//Enter text data to the Node representation
	Node* nodes;	//array is just for easy initialization & data entering. For all other purposes we'll use the node system itself
	nodes = (Node*)malloc(numberOfNodes * sizeof(Node));
	
	
	for (count = 0; count < numberOfNodes; count++)
	{
		for (positionInNode = 0; positionInNode < NODE_SIZE; positionInNode++)
		{
			nodeData[positionInNode] = text[count * NODE_SIZE + positionInNode];
		}
		
		strncpy(nodes[count].data, nodeData, NODE_SIZE);
		if (count == numberOfNodes - 1)
			nodes[count].next = 0;
		else
			nodes[count].next = &nodes[count + 1];
	}

	//User interface for entering values
	printf("\t\tText: \n%s\n\n", text);
	do
	{
		printf("Enter the starting line position for uppercasing:\t");
		scanf("%d", &s);
		s--;		// because [0] is 1-st
	} while (s < 0 && printf("It must be greater than zero! Try again!\n"));

	do
	{
		printf("Enter the starting character position for uppercasing:\t");
		scanf("%d", &n);
		n--;		// because [0] is 1-st
	} while (n < 0 && printf("It must be greater than zero! Try again!\n"));
	printf("\n\n");

	//Measuring time for Vector representation:
	start1 = clock();
	for (int i = 0; i < 1000000; i++)
	{
		countS = 0;
		countN = 0;
		toUpper = false;

		for (size_t i = 0; i < vec.size; ++i)
		{
			toUpper = (countS == s && countN >= n);
			if (toUpper)
				vec.data[i] = toupper(vec.data[i]);
			if (countS == s)
				countN++;
			if (vec.data[i] == '\n')
				countS++;
		}
	}
	end1 = clock();
	cpu_time_used1 = ((double)(end1 - start1)) / CLOCKS_PER_SEC;

	//Printing results for Vector representation
	printf("\t\tVector representation\n\nUsed memory: %d bytes\nUsed time for million iterations: %.3f seconds\n\nOutput:\n", sizeof(vec) + sizeof(*vec.data) * vec.capacity, cpu_time_used1);
	for (size_t i = 0; i < vec.size; ++i)
		printf("%c", vec.data[i]);
	printf("\n\n\n");

	//Measuring time for Node representation:
	start2 = clock();
	for (int i = 0; i < 1000000; i++)
	{
		current = &nodes[0];
		countS = 0;
		countN = 0;
		toUpper = false;

		do
		{
			for (count = 0; count < NODE_SIZE; count++)
			{
				toUpper = (countS == s && countN >= n);
				
				if (toUpper)
					current->data[count] = toupper(current->data[count]);
				
				if (countS == s)
					countN++;

				if (current->data[count] == '\n')
					countS++;
			}
		} while (current = current->next);
	}
	end2 = clock();
	cpu_time_used2 = ((double)(end2 - start2)) / CLOCKS_PER_SEC;

	//Printing results for Node representation
	printf("\t\tNode representation\n\nUsed memory: %d bytes\nUsed time for million iterations: %.3f seconds\n\nOutput:\n", sizeof(Node) * numberOfNodes, cpu_time_used2);
	current = &nodes[0];
	do
	{
		for (count = 0; count < NODE_SIZE; count++)
			printf("%c", current->data[count]);
	} while (current = current->next);

	free(nodes);

	printf("\n\n");
	system("pause");
}