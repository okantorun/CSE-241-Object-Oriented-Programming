#ifndef _Board_Adapter_h_
#define _Board_Adapter_h_


#include "AbstractBoard.h"

namespace Okan{

	template<template<typename ...>class T>
	class HexAdapter : public AbstractHex{
		public:
			HexAdapter():AbstractHex(){}
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
			T<T<Cell>>hexCells;


	};
	
}

#endif