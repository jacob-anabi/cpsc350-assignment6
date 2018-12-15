/**
 * @author Jacob Anabi
 * @date 2018-12-14
 * @version 1.0
 * 2294644
 * CPSC 350
 * Assignment 6 - Sorting
 **/

#include "Sorting.h"
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "RuntimeException.h"

// variable constructor
Sorting::Sorting(const std::string& inFileName)
: inFileName(inFileName), size(0)
{
	initialize();
}

// destructor
Sorting::~Sorting()
{
	delete[] bubbleArr;
	delete[] selectArr;
	delete[] insertArr;
	delete[] quickArr;
}

// sorting time function
void Sorting::timeit()
{
	// timing bubble sort
	auto bubbleStart = std::chrono::high_resolution_clock::now();
	bubbleSort();
	auto bubbleEnd = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> bTime_ms = bubbleEnd - bubbleStart; // bubble sort time (ms)

	// timing selection sort
	auto selectStart = std::chrono::high_resolution_clock::now();
	selectionSort();
	auto selectEnd = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> sTime_ms = selectEnd - selectStart; // bubble sort time (ms)

	// timing insertion sort
	auto insertStart = std::chrono::high_resolution_clock::now();
	insertionSort();
	auto insertEnd = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> iTime_ms = insertEnd - insertStart;  // insertion sort time (ms)

	// timing quick sort
	auto quickStart = std::chrono::high_resolution_clock::now();
	quickSort(0, this->size-1);
	auto quickEnd = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> qTime_ms = quickEnd - quickStart;   // quick sort time (ms)

	// printing times
	std::cout << "Bubble Sort Delta Time:\n" <<
	bTime_ms.count() << " ms\n\n" <<
	"Selection Sort Delta Time:\n" <<
	sTime_ms.count() << " ms\n\n" <<
	"Insertion Sort Delta Time:\n" <<
	iTime_ms.count() << " ms\n\n" <<
	"Quick Sort Delta Time:\n" <<
	qTime_ms.count() << " ms" << std::endl;
	
}

// bubble sort
void Sorting::bubbleSort()
{
	double temp = 0; // used for swapping
	for (int i = 0; i < this->size; ++i) // traverse through array
	{
		for (int j = 0; j < (this->size-i-1); ++j) // ignore sorted elements
		{
			if (this->bubbleArr[j+1] < this->bubbleArr[j]) // elements out of order
			{
				// swap
				temp = this->bubbleArr[j];
				this->bubbleArr[j] = this->bubbleArr[j+1];
				this->bubbleArr[j+1] = temp;
			}
		}
	}
}

// selection sort
void Sorting::selectionSort()
{
	double temp = 0;
	int minimum = 0;
	for (int i = 0; i < this->size; ++i) // traverse through arr
	{
		minimum = i; // set the minimum index
		for (int j = (i+1); j < this->size; ++j)
		{
			if (this->selectArr[minimum] > this->selectArr[j])
			{
				minimum = j;
			}
		}
		// swap
		temp = this->selectArr[i];
		this->selectArr[i] = this->selectArr[minimum];
		this->selectArr[minimum] = temp;
	}
}

// inserition sort
void Sorting::insertionSort()
{
	double temp = 0;
	int beforeIndex = 0;
	for (int i = 1; i < this->size; ++i) // first element is already sorted
	{
		beforeIndex = i;
		while(beforeIndex > 0 && insertArr[beforeIndex] < insertArr[beforeIndex-1]) // might not always run, so avg runtime < worst runtime
		{
			// swap
			temp = this->insertArr[beforeIndex];
			this->insertArr[beforeIndex] = this->insertArr[beforeIndex-1];
			this->insertArr[beforeIndex-1] = temp;
			beforeIndex--;
		}
	}
}

// quick sort
void Sorting::quickSort(int low, int high)
{
	double temp = 0;
	if (low > high)
	{
		return;
	}
	int pivot = quickArr[high]; // pivot point
	int left = low;
	int right = high-1;
	while (left <= right)
	{
		while (left <= right && (pivot >= quickArr[left])) // comb through right for value larger than pivot
		{
			++left;
		}
		while (right >= left && (quickArr[right] > pivot)) // comb through left for value smaler than pivot
		{
			--right;
		}
		if (left < right) // found it
		{
			// swap
			temp = quickArr[left];
			quickArr[left] = quickArr[right];
			quickArr[right] = temp;
		}
	}
	// swap
	temp = quickArr[left];
	quickArr[left] = quickArr[high];
	quickArr[high] = temp;
	// recursive call
	quickSort(low, left-1);
	quickSort(left+1, high);
}

// initialize private members
void Sorting::initialize()
{
	std::string fileLine;
	std::ifstream inFile(this->inFileName);
	int lineNum = 0;
	if (inFile) // if we can open the file, it exists
	{
		while (getline(inFile, fileLine)) // read file line by line
		{
			if (lineNum > this->size) // too much input
			{
				throw RuntimeException("File contains too much input");
			}
			if (lineNum == 0)
			{
				try
				{
					this->size = std::stod(fileLine); // size of arrays
				}
				catch(const std::invalid_argument& err) // can't parse line
				{
					throw RuntimeException("File contains invalid input");
				}
				this->bubbleArr = new double[this->size];
				this->selectArr = new double[this->size];
				this->insertArr = new double[this->size];
				this->quickArr = new double[this->size];
				for (int i = 0; i < this->size; ++i) // initialize arrays
				{
					this->bubbleArr[i] = 0.0;
					this->selectArr[i] = 0.0;
					this->insertArr[i] = 0.0;
					this->quickArr[i] = 0.0;
				}
			}
			else // set appropriate values
			{
				try
				{
					this->bubbleArr[lineNum-1] = std::stod(fileLine);
					this->selectArr[lineNum-1] = std::stod(fileLine);
					this->insertArr[lineNum-1] = std::stod(fileLine);
					this->quickArr[lineNum-1] = std::stod(fileLine);
				}
				catch(const std::invalid_argument& err) // can't parse line
				{
					throw RuntimeException("File contains invalid input");
				}
			}
			++lineNum;
		}
		if ((lineNum-1) < this->size)
		{
			throw RuntimeException("File contains too little input");
		}
	}
	else
	{
		throw RuntimeException("No file found");
	}
}