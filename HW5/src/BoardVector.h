#ifndef _Board_Vector_h_
#define _Board_Vector_h_

#include <vector>

#include "AbstractBoard.h"


namespace Okan{
	class HexVector : public AbstractHex{

		public:
			HexVector():AbstractHex(){}
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

			std::vector<std::vector<Cell>> hexCells;



	};
}

#endif