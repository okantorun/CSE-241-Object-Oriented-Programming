#ifndef _Abstract_Board_h_
#define _Abstract_Board_h_


namespace Okan
{
	class AbstractHex{
		public:
			class Cell{
				public:
					Cell();
					Cell(int r,int c);		//in the play function, it is the constructor that takes my coordinates.
					Cell(int r,int c,int user);
					void set_Cell(char data);	//I'm putting in the coordinates.
					char get_Cell()const {return getData;}
					int get_compRow()const {return comp_Row;}		
					int get_compCol()const {return comp_Col;}
					int get_userRow()const {return user_row;}		
					int get_userCol()const {return user_col;}


				protected:
					char getData;	
					int comp_Row;
					int comp_Col;
					int user_row;
					int user_col;
					int user_move;

			};
			enum cell{user1='x',user2='o',empty='.'};
			AbstractHex();
			virtual void setSize(int set_size)=0;
			virtual int getSize() const{return size;};
			virtual int getSelection() const{return selection;};
			virtual int getCounter() const{return counter;};
			virtual void reset() = 0;
			virtual void print() const = 0;				//Display function
			virtual void writeToFile() = 0;				//Save function
			virtual void readFromFile() = 0;			//Load function
			virtual int isEnd_x(int check_count) const = 0;	//controls the end of the game 
			virtual int isEnd_o(int check_count) const = 0;	//controls the end of the game
			virtual Cell play() = 0;		//computer
			virtual void play(Cell Position) = 0;	//user1-user2
			virtual void playGame() = 0;
			virtual void setAddLastMove(int row,int col);
			virtual char lastMove() const ;
			virtual char operator()(int row, int col) const  = 0;
			virtual bool operator==(AbstractHex &otherBoard);
			virtual int numberOfMoves() const;
			virtual void edit_coordinate(int& row,int& column);
			
			int m_numberOfMoves=0;
			

		protected:

			char *coordinate_r=nullptr;			//I'm assigning pointer nullptr for the initial value. 
			char *coordinate_c=nullptr;
			char *load_name=nullptr;
			char *save_name=nullptr;
			int x;
			int y;
			int size;
			int selection;
			int counter;

			
	};
	
}


#endif