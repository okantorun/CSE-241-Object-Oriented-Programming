#ifndef _MYHEADER_H
#define _MYHEADER_H

using namespace std;

class Hex{

	public:
		enum cell{user1='x',user2='o',empty='.'};
		Hex(int move,int game_type);
		Hex(int start_size);
		Hex();
		void save_file(char file_name[25]);
		void load_file(char file_name[25]);
		int  height_board() const{return size;}
		int  width_board() const {return size;}
		void display();
		void initial_board();
		void play();		//computer
		void play(int cell_row,int cell_column);	//user1-user2
		void playGame();
		void edit_coordinate(char coordinate_r[25],char coordinate_c[25],int& row,int& column);
		static int Marked_Cell(){return Marked_Number;}
		static int Marked_Number;
		bool Compare(Hex Other_Object)  {return Marked_Compare()>Other_Object.Marked_Compare();}
		int Marked_Compare();
		int game_count=0;


		


	private:
		
		int size;
		int selection;
		int counter=0;
		void upper(int check_count);
		int checked_x(int check_count);	//finds the winner 
		int checked_o(int check_count);	//finds the winner
		class Cell{
			public:

				char getData;
				
		};
		std::vector<std::vector<Cell>> hexCells;
		

		
};


#endif
