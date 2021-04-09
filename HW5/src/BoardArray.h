#ifndef _Board_Array_h_
#define _Board_Array_h_

#include "AbstractBoard.h"



namespace Okan{
	class HexArray1D : public AbstractHex{

		public:
			HexArray1D():AbstractHex(){}
			
			//Big three:I created they for deep copying of dynamic arrays.
			HexArray1D (const HexArray1D& HexObject);		//Copy Constructor
			HexArray1D& operator=(const HexArray1D& rightSide);	//Assigment Operator 
			~HexArray1D( ); 		//Destructor
	   	
	   		void setSize(int set_size);
			void reset() ;
			void print() const ;				//Display function
			void writeToFile();				//Save function
			void readFromFile();			//Load function
			int isEnd_x(int check_count) const;	//finds the winner 
			int isEnd_o(int check_count) const;	//finds the winner
			Cell play();		//computer
			void play(Cell Position);	//user1-user2
			void playGame();
			void upper(int check_count);
			char operator()(int row, int col) const ;
			int game_count=0;

		private:
			Cell *hexCellsArr;


	};
}

#endif