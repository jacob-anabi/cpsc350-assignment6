/**
 * @author Jacob Anabi
 * @date 2018-12-14
 * @version 1.0
 * 2294644
 * CPSC 350
 * Assignment 6 - Sorting
 **/

#ifndef SORTING_H
#define SORTING_H

#include <string>

class Sorting
{
public:
	/**
	 * Variable constructor
	 * @param inFileName - the file to read from
	**/
	Sorting(const std::string& inFileName);
	/**
	 * Destructor
	 **/
	~Sorting();
	/**
	 * Time 4 sorting algortihms:
	 * - Bubble Sort
	 * - Selection Sort
	 * - Inserion Sort
	 * - Quick Sort
	 **/
	void timeit();
private:
	// 4 arrays for four sorting algorithms
	double* bubbleArr;
	double* selectArr;
	double* insertArr;
	double* quickArr;

	int size; // size of arrays
	std::string inFileName; // the input file name

	/**
	 * Sortings list of doubles using bubble sort
	 **/
	void bubbleSort();
	/**
	 * Sortings list of doubles using selection sort
	 **/
	void selectionSort();
	/**
	 * Sortings list of doubles using insertion sort
	 **/
	void insertionSort();
	/**
	 * Sortings list of doubles using quick sort
	 * @param low - lower bound for pivot
	 * @param high - upper bound for pivot
	 **/
	void quickSort(int low, int high);

	/**
	 * initializes our class
	 **/
	void initialize();
};

#endif // SORTING_H