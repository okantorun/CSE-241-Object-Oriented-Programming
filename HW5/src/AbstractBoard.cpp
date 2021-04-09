#include "AbstractBoard.h"
#include <cstring>
#include <iostream>
using std::cout;

namespace Okan
{

	AbstractHex::AbstractHex():counter(0),selection(1),x(-99),y(-99){}

	AbstractHex::Cell::Cell(){	//default Cell constructor 
		comp_Row=1;
		comp_Col=1;
	}
	AbstractHex::Cell::Cell(int r,int c){	//in the play function, I use to return  coordinate .
		comp_Row=r;
		comp_Col=c;
	}
	AbstractHex::Cell::Cell(int r,int c,int user){
		user_row=r;
		user_col=c;
		user_move=user;


	}
	void AbstractHex::Cell::set_Cell(char data){
		getData=data;
	}


	void AbstractHex::edit_coordinate(int& row,int& column){
		int length;

		length=strlen(coordinate_r);
		if(length==1){
			column=coordinate_c[0]-65;
			row=coordinate_r[0]-'0';
		}				
		else if(length==2){											////I'm editing the entered string coordinate
			column=coordinate_c[0]-65;
			row=(coordinate_r[0]-'0')*10+coordinate_r[1]-'0';

		}
		else{
			column=coordinate_c[0]-65;
			row=15;

		}

	}

	void AbstractHex::setAddLastMove(int row,int col){
		y=row;
		x=col;
	}

	char AbstractHex::lastMove() const {
	
		try{
			if(x!=-99 && y!=-99)
				return (*this)(y,x);
			else
				throw std::runtime_error("Error: There is no move made.");
		}

		catch(std::exception & exp){
			cout<<exp.what();
			return '\n';
		}

	}

	
	int AbstractHex::numberOfMoves() const{
		return m_numberOfMoves;
	}

	bool AbstractHex::operator==(AbstractHex &otherBoard)
	{
		
	    if (otherBoard.size==size)
	    {
	        for (int i = 0; i <size; i++)
	        {
	            for (int j = 0; j < size; j++)
	            {
	                if (otherBoard(i, j) != (*this)(i, j))
	                {
	                    return false;
	                }
	            }
	        }
	    }
	    else
	    {
	        return false;
	    }

	    return true;
	}




}