// Branden Hicks 
// 5332991
// Lab Assignment 8

#include <time.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void replace(int *x, int *y)
{
	int tmp = *x; 
	*x = *y; 
	*y = tmp; 
} 

void heapHelper(int arr[], int n, int indexNum) 
{
    int max = indexNum;
		int rightSide = indexNum * 2 + 2; 
		int leftSide = indexNum * 2 + 1; 

		if(leftSide < n && arr[leftSide] > arr[max])
		{
			max = leftSide; 
		}
		
		if(rightSide < n && arr[rightSide] > arr[max])
		{
			max = rightSide; 
		}

		if(max != indexNum)
		{
			replace(&arr[indexNum], &arr[max]); 
			heapHelper(arr, n, max); 
		}
}

void heapSort(int arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapHelper(arr, n, i); 
	}

	for (int i = n - 1; i >= 0; i--)
	{
		replace(&arr[0], &arr[i]); 
		heapHelper(arr, i, 0); 
	}
	
}

void mergeHelper(int arr[], int l, int m, int r) 
{
    int a = 0, b = 0, c; 
		int num1 = m - l + 1; 
		int num2 = r - m; 

		int *left = malloc(num1 * sizeof(int)); 
		int *right = malloc(num2*sizeof(int)); 

		for (a = 0; a < num1; a++)
		{
			left[a] = arr[l + 1]; 
		}

		for (int b = 0; b < num2; b++)
		{
			right[b] = arr[m + 1 + b]; 
		}
		
		c = l; 

		while (a < num1 && b < num2)
		{
			if(left[a] <= right[a])
			{
				arr[c] = left[a]; 
				a++; 
			}
			else
			{
				arr[c] = right[b]; 
			}
		}
		
		while (a < num2)
		{
			arr[c] = left[a]; 
			a++; 
			c++; 
		}

		while (b < num2)
		{
			arr[c] = left[b]; 
			a++; 
			c++; 
		}
		
		free(left); 
		free(right); 
		
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int arr[], int l, int r)
{
	if(l > r)
	{
		int med = ((l + r) / 2); 
		mergeSort(arr, l, med); 
		mergeSort(arr, med + 1, r);
		mergeHelper(arr, l, med, r);  
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
}



// prints first and last 100 items in the data array
int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.3lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.3lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}