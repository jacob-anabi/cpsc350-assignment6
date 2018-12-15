/**
 * @author Jacob Anabi
 * @date 2018-12-14
 * @version 1.0
 * 2294644
 * CPSC 350
 * Assignment 6 - Sorting
 **/

#include <iostream>
#include "Sorting.h"
#include "RuntimeException.h"

int main(int argc, char** argv)
{
	if (argc > 1)
	{
		try
		{
			Sorting*  sort = new Sorting(argv[1]);
			sort->timeit();
			delete sort;
		}
		catch (RuntimeException& err)
		{
			std::cout << err.getErr() << std::endl;
		}
	}
	else
	{
		std::cout << "No file input" << std::endl;
	}
	
	return 0;
}