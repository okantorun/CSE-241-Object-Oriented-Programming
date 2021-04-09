#ifndef _MYHEADER_H
#define _MYHEADER_H

using namespace std;
class Hex{

	public:
		class Cell{
			public:
				Cell();
				Cell(int r,int c);		//in the play function, it is the constructor that takes my coordinates.
				Cell(int r,int c,int user);
				void set_Cell(char data);	//I'm putting in the coordinates.
				char get_Cell()const {return getData;}
				void set_Copy(int copy_row,int copy_col);	//for the order of moves
				int get_copy_row()const {return copy_cr_r;} 
				int get_copy_col()const {return copy_cr_c;} 
				int get_compRow()const {return comp_Row;}		
				int get_compCol()const {return comp_Col;}
				int get_userRow()const {return user_row;}		
				int get_userCol()const {return user_col;}


			private:
				char getData;	
				int copy_cr_r;
				int copy_cr_c;
				int comp_Row;
				int comp_Col;
				int user_row;
				int user_col;
				int user_move;

		};
		enum cell{user1='x',user2='o',empty='.'};
	    Hex(int move,int game_type);
		explicit Hex(int start_size);	//I added explicit keyword because I didn't want it to be used as a conversion constructor.
		Hex();
		//Big three:I created they for deep copying of dynamic arrays.
		Hex (const Hex& HexObject);		//Copy Constructor
		Hex& operator=(const Hex& rightSide);	//Assigment Operator 
		~Hex( ); 		//Destructor
		int  height_board() const{return size;}
		int  width_board() const {return size;}
		void initial_board();
		friend ostream& operator <<(ostream& output, const Hex& obj);	//Display function
		friend ofstream& operator<<(ofstream& os,Hex& obj);				//Save function
		friend ifstream& operator>>(ifstream& is,Hex& obj);				//Load function
		int get_score_x(int check_count,int score,int count_score);
		int get_score_o(int check_count,int score,int count_score);
		Cell play();		//computer
		void play(Cell Position);	//user1-user2
		void playGame();
		void edit_coordinate(int& row,int& column);
		void addElement(int r,int c);
		Hex operator--( ); 			//prefix-undo user1-user2
		Hex operator--(int); //postfix-undo user1-computer
		static int Marked_Cell(){return Marked_Number;}
		static int Marked_Number;
		bool operator ==(const Hex& Other_Object)const { return get_Marked_Compare()==Other_Object.get_Marked_Compare();}
		bool operator <(const Hex& Other_Object)const { return get_Marked_Compare()<Other_Object.get_Marked_Compare();}
		bool operator >(const Hex& Other_Object)const { return get_Marked_Compare()>Other_Object.get_Marked_Compare();}
		int Marked_Compare();
		void set_Marked_Compare(int set_Marked_Counter);
		int get_Marked_Compare()const {return marked_counter;}
		int game_count=0;
		

	private:
		char *coordinate_r=nullptr;			//I'm assigning pointer nullptr for the initial value. 
		char *coordinate_c=nullptr;
		char *load_name=nullptr;
		char *save_name=nullptr;
		int score_x=0;
		int score_o=0;
		int count_score_x=0;
		int count_score_o=0;
		int marked_counter;
		int size;
		int selection;
		int counter;
		int used;
		void upper(int check_count);
		int checked_x(int check_count);	//finds the winner 
		int checked_o(int check_count);	//finds the winner
		
		Cell **hexCells;
		Cell *copy_Cells;
		
};


#endif