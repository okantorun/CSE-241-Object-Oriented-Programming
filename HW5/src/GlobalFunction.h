#include "AbstractBoard.h"

bool isValidSequence(Okan::AbstractHex *arr[],int length){


	for(int i = 0; i < length; i++)
	{									
		if(arr[i] -> getSize() < 6 || arr[i] -> getSize() > 26 ||
			arr[i] -> getSelection() !=1 || arr[i] -> getSelection() != 2 ||			
			arr[i] -> getCounter() !=0 || arr[i] -> getCounter() != 1)				
		{																					
			return false;												//I return false if board size, user order and game selection are invalid.
		}
	}

	for(int i = 0; i < length; i++)
	{
		
		for (int j = 0; j < arr[i]->getSize(); j++)
	    {

	       for (int k = 0; k < arr[i]->getSize(); k++)
	        {

	          if ((*arr[i])(j, k) != 'x' && (*arr[i])(j, k) != 'o' && (*arr[i])(j, k) != '.')
	           {
	                return false;			//The game is invalid if there are characters outside 'x', 'o' and '.' 
	           }        
	        }
	    }
	}
	return true;

}