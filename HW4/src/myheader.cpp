#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>
#include "myheader.h"
using std::ifstream;
using std::ofstream;
using namespace std;


int Hex::Marked_Number=0;		//İnitilaizing static variable

Hex::Hex(int move,int game_type):counter(move),selection(game_type){	//the computer starts the game with the values I give.

}

Hex::Hex(int start_size):size(start_size){	//default value of the board
}

Hex::Hex():used(0),counter(0){	//a counter that determines who is next
}

Hex::Cell::Cell(){	//default Cell constructor 
	comp_Row=1;
	comp_Col=1;
}
Hex::Cell::Cell(int r,int c){	//in the play function, I use to return  coordinate .
	comp_Row=r;
	comp_Col=c;
}
Hex::Cell::Cell(int r,int c,int user){
	user_row=r;
	user_col=c;
	user_move=user;


}
void Hex::Cell::set_Copy(int copy_row,int copy_col){
	copy_cr_r=copy_row;
	copy_cr_c=copy_col;
}
void Hex::Cell::set_Cell(char data){
	getData=data;
}


Hex::Hex(const Hex& HexObject)
	:counter(HexObject.counter),size(HexObject.size),used(HexObject.used),
	score_o(HexObject.score_o),score_x(HexObject.score_x)
{
	hexCells = new Cell*[size];
	for(int i=0;i<size;i++){
		hexCells[i]=new Cell[size];							//I'm copying the information necessary for the game to continue.
		for(int j=0;j<size;j++){
			hexCells[i][j].set_Cell(HexObject.hexCells[i][j].get_Cell());
		}
	}
	copy_Cells=new Cell[size*size];
	for(int i=0;i<used;i++){
		copy_Cells[i].set_Copy(HexObject.copy_Cells[i].get_copy_row(),	//I'm copying the order of moves
								HexObject.copy_Cells[i].get_copy_col());
		
	}

}
Hex& Hex::operator=(const Hex& rightSide){

	if(size!=rightSide.size){
		delete [] hexCells;				//I added This condition to be more efficient
		delete [] copy_Cells;			
		hexCells = new Cell*[size];
		copy_Cells=new Cell[size*size];
		for(int i=0;i<size;i++)
			hexCells[i]=new Cell[size];
	}
	counter=rightSide.counter;
	size=rightSide.size;
	used=rightSide.used;							//I do the same operations in copy constructor in the assigment operator.
	score_x=rightSide.score_x;
	score_x=rightSide.score_x;
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){										
			hexCells[i][j].set_Cell(rightSide.hexCells[i][j].get_Cell());
		}
	}
	for(int i=0;i<used;i++){
		copy_Cells[i].set_Copy(rightSide.copy_Cells[i].get_copy_row(),
								rightSide.copy_Cells[i].get_copy_col());
		
	}

	return *this;
	
}

Hex::~Hex( )
{	
	delete [] coordinate_r;		//I did not add hexCells pointer to destructor to avoid the previous game's move information when switching between games.
	delete [] coordinate_c;
	delete [] load_name;
	delete [] save_name;
    
}
void Hex::set_Marked_Compare(int set_Marked_Counter){
	marked_counter=set_Marked_Counter;
}

int Hex::Marked_Compare(){
	int marked_counter=0;
	int i,j;
	
	for(i=0;i<size;i++){			//I find the number of marked cells in the object with the loop.
		for(j=0;j<size;j++){
			if(hexCells[i][j].get_Cell()==user1 || hexCells[i][j].get_Cell()==user2)
			marked_counter++;
		}	
	}

	return marked_counter;




}

void Hex::initial_board(){
	int i,j;
	int  a,x;
	char str[] = {'a','b','c','d','e','f','g','h','I','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

	hexCells = new Cell*[size];

	//hexCells.resize(size);	//I determine the size of the vector as much as the size of the board taken from the user.
	
	for(i=0;i<size;i++){
		if(i==0){
			cout <<"   ";
			for (int k = 0; k < size; ++k)
			{
				cout <<  str[k]<<"  ";

			}
			cout <<"\n";
		}
		hexCells[i]=new Cell[size];
		//hexCells[i].resize(size); //it is two-dimensional, I make every index of the vector as much as the width of the board.
		cout <<  i+1<<" ";

		for(j=0;j<i;j++){
			cout <<"  ";
		}
		for(j=0;j<size;j++){
			cout <<" . ";
			hexCells[i][j].set_Cell(empty);
		}
		cout <<"\n";
	}
}

int Hex::checked_x(int check_count){
	int i;
	int j;

	for(i=0;i<size;i++){
		if(hexCells[i][check_count].get_Cell()==user1){		//the funciton controls to see if 'x' wins  with recursion.
			for(j=i-1;j<i+1;j++){
				if(j!=-1){
					if(hexCells[j][check_count+1].get_Cell()==user1){
						return checked_x(check_count+2);
					}
				}
			}
		}
	}

	
	return check_count;
	
}

int Hex::checked_o(int check_count){
	int i;
	int j;
	if(check_count==size)
		return check_count;
	for(i=0;i<size;i++){
		if(hexCells[check_count][i].get_Cell()==user2){			//the funciton controls to see if 'o' wins  with recursion.
			for(j=i-1;j<i+1;j++){
				if(hexCells[check_count+1][j].get_Cell()==user2){
					return checked_o(check_count+2);
				}

			}
		}
		
	}
	
	return check_count;
	
}

void Hex::play(Cell temp){
	int i,j;

	if(selection==1){	

		if(counter%2==0){

			hexCells[temp.get_userRow()-1][temp.get_userCol()].set_Cell(user1);
			perror("debug");

			//hexCells[cell_row-1][cell_column].set_Cell(user1);		//it places the coordinates set by the user in the vector.	user vs comp
		}
			
		cout<<*this;

	}

	else if(selection==2){

		if(counter%2==0){
			hexCells[temp.get_userRow()-1][temp.get_userCol()].set_Cell(user1);
			//hexCells[cell_row-1][cell_column].set_Cell(user1);
		}
		else if(counter%2==1){										//it places the coordinates set by the user in the vector.  user vs user
			hexCells[temp.get_userRow()-1][temp.get_userCol()].set_Cell(user2);
			//hexCells[cell_row-1][cell_column].set_Cell(user2);
		}		
	}
}

Hex::Cell Hex::play(){
	int row,column;
	int c=0;
	int i;
	int j;
	int k,m;
	int control=0;
	int control2=0;
	int control_o=0;
	Cell temp;
	
	for(i=0;i<size;i++){
		if(hexCells[0][i].get_Cell()==user2)
			control++;
	}
	
	if(control==0){										//I'm trying to determine the computer's moves as smart as possible.
		for(i=0;i<size;i++){
			for(j=0;j<size;j++){
				if(hexCells[i][j].get_Cell()==user1){
					row=i;
					column=j;
					c++;
					break;
				}

			}									
			if(c!=0)
				break;
		}
		if(column+2>=size){						//it checks the board and tries to play a sub-index every time he moves, if it's full, it turns to other alternatives.
			temp=Cell(0,column-2);
			return temp;
		}
		else{
			temp=Cell(0,column+2);
			return temp;
		}
		
	}
	else{
		for(k=size-1;k>=0;k--){
			for(m=size-1;m>=0;m--){
				if(hexCells[k][m].get_Cell()==user2){
					control_o++;
					break;
				}
			}
			if(control_o!=0)
				break;
		}
			
		for(j=m-1;j<m+1;j++){
			if(hexCells[k+1][j].get_Cell()==empty){
				temp=Cell(k+1,j);						//I send the computer's move to my cell class with constructor and 
				return temp;							//assigned it to my object that I will return.
			}											
		}
		if(control2==0){
			
			if(hexCells[k][m-1].get_Cell()==empty){
				temp=Cell(k,m-1);
				return temp;
			}
			else if(hexCells[k][m+1].get_Cell()==empty){
				temp=Cell(k,m+1);
				return temp;
			}
			else{
				temp=Cell(k+2,m);
				return temp;
			}
		}

	}
	return temp;

}

void Hex::upper(int check_count){
	int i;
	int j;
	
	if(counter%2==0){
		for(i=0;i<size;i++){
			if(hexCells[i][check_count].get_Cell()==user1){
				for(j=i-1;j<i+1;j++){
					if(j!=-1){
						if(hexCells[j][check_count+1].get_Cell()==user1){
							hexCells[j][check_count+1].set_Cell(user1-32);
							hexCells[i][check_count].set_Cell(user1-32);
						    upper(check_count+2);

						}
					}
				}
			}
			
		}			////I conver to uppercase the letters of the winning team with the same logic as we find the winner with recursion.
	}
	else if(counter%2==1 && check_count!=size){
		for(i=0;i<size;i++){
			if(hexCells[check_count][i].get_Cell()==user2){
				for(j=i-1;j<i+1;j++){
					if(hexCells[check_count+1][j].get_Cell()==user2){
						hexCells[check_count+1][j].set_Cell(user2-32);
						hexCells[check_count][i].set_Cell(user2-32);
					    upper(check_count+2);

					}
				}
			}
			
		}

	}
	if(check_count==size){
		cout<<*this;
	}
	
	
}

ostream& operator<<(ostream& output,const Hex& obj){
	char str[] = {'a','b','c','d','e','f','g','h','I','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	Hex::Cell c1;
	int i,j;
	int *target_cell;


	if(obj.selection==1){
		if(obj.counter%2==0){
			for(i=0;i<obj.size;i++){
				if(i==0){
					output <<"   ";
					for (int k = 0; k < obj.size; ++k)
					{
						output <<  str[k]<<"  ";

					}
					output <<"\n";
				}

				output <<  i+1<<" ";

				for(j=0;j<i;j++){
					output <<"  ";
				}
				for(j=0;j<obj.size;j++){
					output <<" "<<obj.hexCells[i][j].get_Cell()<<" ";
				}
				output <<"\n";
			}										//it prints the current state of the board.
			
		}
		else if(obj.counter%2==1){
			for(i=0;i<obj.size;i++){
				if(i==0){
					output <<"   ";
					for (int k = 0; k <obj.size; ++k)
					{
						output <<  str[k]<<"  ";

					}
					output <<"\n";
				}

				output <<  i+1<<" ";

				for(j=0;j<i;j++){
					output <<"  ";
				}
				for(j=0;j<obj.size;j++){
					output <<" "<<obj.hexCells[i][j].get_Cell()<<" ";
				}
				output <<"\n";
			}
			
		}

	}
	
	if(obj.selection==2){
		if(obj.counter%2==0){
			for(i=0;i<obj.size;i++){
				if(i==0){
					output <<"   ";
					for (int k = 0; k < obj.size; ++k)
					{
						output <<  str[k]<<"  ";

					}
					output <<"\n";
				}

				output <<  i+1<<" ";

				for(j=0;j<i;j++){
					output <<"  ";
				}
				for(j=0;j<obj.size;j++){
					output <<" "<<obj.hexCells[i][j].get_Cell()<<" ";
					
				}
				output <<"\n";
			}
		}
		else if(obj.counter%2==1){

			
			for(i=0;i<obj.size;i++){
				if(i==0){
					output <<"   ";
					for (int k = 0; k < obj.size; ++k)
					{
						output <<  str[k]<<"  ";

					}
					output <<"\n";
				}

				output <<  i+1<<" ";

				for(j=0;j<i;j++){
					output <<"  ";
				}
				for(j=0;j<obj.size;j++){

					output <<" "<<obj.hexCells[i][j].get_Cell()<<" ";
					
				}
				output <<"\n";
			}
		}
	}
	return output;

}
void Hex::edit_coordinate(int& row,int& column){
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
ofstream& operator<<(ofstream& os,Hex& obj){
	
	os.open(obj.save_name);

	if(obj.selection==1){ os<<"1"<<endl;}				//it is recording the selection
	else{os<<"2"<<endl;}

	if(obj.counter%2==0) {os<<"0"<<endl;}				//it records who's next.
	else{ os<<"1"<<endl;}

	os<<obj.size<<endl;									//it records board_size
	os<<obj.used<<endl;

	for(int i=0;i<obj.size;i++)
		for(int j=0;j<obj.size;j++)
			os<<obj.hexCells[i][j].get_Cell();
	os<<endl;
	for(int i=0;i<obj.used;i++){
		os<<obj.copy_Cells[i].get_copy_row()<<endl;		//I'm saving my moves order in the file.
		os<<obj.copy_Cells[i].get_copy_col()<<endl;
	}

	os.close( );
	return os;
}
ifstream& operator>>(ifstream& is,Hex& obj){
	char temp;
	int temp2,temp3;

	is.open(obj.load_name);

	is>>obj.selection;					//I'm taking back the information.
	is>>obj.counter;
	is>>obj.size;
	is>>obj.used;

	obj.copy_Cells=new Hex::Cell[obj.size*obj.size];
	obj.hexCells = new Hex::Cell*[obj.size];
	for(int i=0;i<obj.size;i++){
		obj.hexCells[i] = new Hex::Cell[obj.size];
		for(int j=0;j<obj.size;j++){
			is>>temp;
			obj.hexCells[i][j].set_Cell(temp);
		}
	}
	for(int i=0;i<obj.used;i++){
		is>>temp2;
		is>>temp3;
		obj.copy_Cells[i].set_Copy(temp2,temp3);
	}
	return is;

}

Hex Hex::operator--( ) //prefix version
{
	hexCells[copy_Cells[used-1].get_copy_row()][copy_Cells[used-1].get_copy_col()].set_Cell(empty);	//I'm replacing the last move with a dot.
	used--;			//and I'm reducing my move counter.
	counter--;
    return *this;
}
Hex Hex::operator--(int ignoreMe) //postfix version
{

	int temp1=used;					//in user vs computer, I delete both the computer and the user's moves.
	int temp2=counter;				//I do this at postfix.

	hexCells[copy_Cells[used-1].get_copy_row()][copy_Cells[used-1].get_copy_col()].set_Cell(empty);
	used--;			
	counter--;
	hexCells[copy_Cells[temp1-2].get_copy_row()][copy_Cells[temp1-2].get_copy_col()].set_Cell(empty);
	used--;
	counter--;
	perror("debug");
    return *this;
}
void Hex::addElement(int r,int c){

	if(used==0)
		copy_Cells=new Cell[size*size];			//I copy the move after every move played

	copy_Cells[used].set_Copy(r-1,c);
	used++;

}
int Hex::get_score_x(int check_count,int score_x,int count_score_x){
	int i;
	int j;

	for(i=0;i<size;i++){
		if(hexCells[i][check_count].get_Cell()==user1){		//I calculate the score of the value x with recursion.
			if(count_score_x==0){
				score_x+=10;
				count_score_x++;
			}
			for(j=i-1;j<i+1;j++){
				if(j!=-1){
					if(hexCells[j][check_count+1].get_Cell()==user1){
						score_x+=10;
						count_score_x=0;
						return get_score_x(check_count+2,score_x,count_score_x);
					}
				}
			}
		}
	}

	
	return score_x;
	
}
int Hex::get_score_o(int check_count,int score_o,int count_score_o){
	int i;
	int j;
	if(check_count==size)
		return check_count;
	for(i=0;i<size;i++){
		if(hexCells[check_count][i].get_Cell()==user2){			//I calculate the score of the value o with recursion.
			if(count_score_o==0){
				score_o+=10;
				count_score_o++;
			}
			for(j=i-1;j<i+1;j++){
				if(hexCells[check_count+1][j].get_Cell()==user2){
					score_o+=10;
					count_score_o=0;
					return get_score_o(check_count+2,score_o,count_score_o);
				}

			}
		}
		
	}
	
	return score_o;
	
}

void Hex::playGame(){
	int menu_counter=0;
	int row;
	int length;
	int column;
	int winner=0;
	int check_count=0;
	Cell comp;
	Cell Position; 
	ofstream file_os;
	ifstream file_if;
	coordinate_r=new char[25];
	coordinate_c=new char[25];
	if(game_count==0){				//game_count variable: to continue from the same place in the game change
		cout<<"(1)Computer-User or (2)User1-User2:";
		cin>>selection;
		cout<<"Please enter a board size Ex(Enter 6 for 6x6):";
		cin>>size;
		while(size<6 || size>26){
			cerr<<"Please enter a value between 6 and 26:";
			cin>>size;
		}
		initial_board();
	}
	switch(selection){
		case 1:
			while(1){
				if(game_count!=0)
					cout<<*this;
				if(counter%2==0 || (counter%2==1 && selection==2)){
					cout<<"Please enter a coordinate  Ex(C 5):";
					cout<<"\nex(LOAD load.txt) to load the game or ex(SAVE save.txt) to save the game:";
					cout<<"\nfor Back to Menu ex(BACK MENU):";
					cin>>coordinate_c>>coordinate_r;
					if(strcmp(coordinate_c,"SAVE")==0){
						save_name=new char[strlen(coordinate_r)];
						strcpy(save_name,coordinate_r);
						file_os<<*this;

					}
					else if(strcmp(coordinate_c,"LOAD")==0){
						load_name=new char[strlen(coordinate_r)];
						strcpy(load_name,coordinate_r);
						file_if>>*this;
						cout<<*this;
					}
					else if(strcmp(coordinate_c,"BACK")==0 && strcmp(coordinate_r,"MENU")==0){
						game_count++;
						menu_counter++;	//a variable to get out of the game
						break;
					}
					else if(strcmp(coordinate_c,"UNDO")==0 &&strcmp(coordinate_r,"MOVE")==0 && used>0 && selection==1){
						
						(*this)--;
						cout<<*this;

					}
					else if(strcmp(coordinate_c,"UNDO")==0 &&strcmp(coordinate_r,"MOVE")==0 && used>0 && selection==2){
					
						--(*this);
						cout<<*this;
					}
					else if(strcmp(coordinate_c,"SCORE")==0 && strcmp(coordinate_r,"GAME")==0){
						score_x=0;
						score_o=0;
						cout<<"User1 SCORE: = "<<(get_score_x(check_count,score_x,count_score_x))<<endl;
						cout<<"User2 SCORE: = "<<(get_score_o(check_count,score_o,count_score_o))<<endl;
					}
					else{

						edit_coordinate(row,column);
						while(column>size-1 || row>size){
							if(strcmp(coordinate_c,"UNDO")==0){
								cerr<<"No moves left to erase"<<endl;
								cerr<<"Please enter a valid coordinate:";
							}
							else
								cerr<<"Please enter a valid coordinate:";

							cin>>coordinate_c>>coordinate_r;
							edit_coordinate(row,column);
							
						}
						while(hexCells[row-1][column].get_Cell()!='.'){
							cerr<<"This move has been made before.:";
							cin>>coordinate_c>>coordinate_r;
							edit_coordinate(row,column);
							
						}

						addElement(row,column);

						Marked_Number++;		//the number of marked cells is increasing.
						perror("debug");
						Position=Cell(row,column,1);
						play(Position);
						cout<<*this;

						if(checked_x(check_count)==size){
							upper(check_count);
							winner++;
							break;
						}
						if(checked_o(check_count)==size){
							upper(check_count);
							winner++;
							break;
						}
						counter++;
					}
				}
				else if(counter%2==1 && selection==1){

					Marked_Number++;
					comp=play();
					hexCells[comp.get_compRow()][comp.get_compCol()].set_Cell(user2);
					addElement(comp.get_compRow()+1,comp.get_compCol());
					cout<<*this;
					if(checked_o(check_count)==size){
						upper(check_count);
						winner++;
						game_count--;
						//cout<<game_count;
						break;
					}
					counter++;
					
				}
				if(winner!=0)
					break;
				

				if(menu_counter!=0){
					menu_counter=0;
					break;
				}
			}

			break;


		case 2:
			
			while(1){
				if(game_count!=0)
					cout<<*this;
				if(counter%2==0 || (counter%2==1 && selection==2)){
					cout<<"Please enter a coordinate  Ex(C 5):";
					cout<<"\nex(LOAD load.txt) to load the game or ex(SAVE save.txt) to save the game:";
					cout<<"\nfor Back to Menu ex(BACK MENU):";
					cin>>coordinate_c>>coordinate_r;
					if(strcmp(coordinate_c,"SAVE")==0){
						save_name=new char[strlen(coordinate_r)];
						strcpy(save_name,coordinate_r);
						file_os<<*this;

					}
					else if(strcmp(coordinate_c,"LOAD")==0){
						load_name=new char[strlen(coordinate_r)];
						strcpy(load_name,coordinate_r);
						file_if>>*this;
						cout<<*this;
							
					}
					else if(strcmp(coordinate_c,"BACK")==0 && strcmp(coordinate_r,"MENU")==0){
						game_count++;
						menu_counter++;
						counter--;
						break;
					}
					else if(strcmp(coordinate_c,"UNDO")==0 &&strcmp(coordinate_r,"MOVE")==0 && used>0 && selection==1){
						(*this)--;
						cout<<*this;

					}
					else if(strcmp(coordinate_c,"UNDO")==0 &&strcmp(coordinate_r,"MOVE")==0 && used>0 && selection==2){
						--(*this);
						cout<<*this;
					}
					
					else if(strcmp(coordinate_c,"SCORE")==0 && strcmp(coordinate_r,"GAME")==0){
						score_x=0;
						score_o=0;
						cout<<"User1 SCORE: = "<<(get_score_x(check_count,score_x,count_score_x))<<endl;
						cout<<"User2 SCORE: = "<<(get_score_o(check_count,score_o,count_score_o))<<endl;
					}
					else{

						edit_coordinate(row,column);

						while(column>size-1 || row>size){
							if(strcmp(coordinate_c,"UNDO")==0){
								cerr<<"No moves left to erase"<<endl;
								cerr<<"Please enter a valid coordinate:";
							}
							else
								cerr<<"Please enter a valid coordinate:";
							
							cin>>coordinate_c>>coordinate_r;
							edit_coordinate(row,column);
											
						}
						while(hexCells[row-1][column].get_Cell()!='.'){
							cerr<<"This move has been made before.:";
							cin>>coordinate_c>>coordinate_r;
							edit_coordinate(row,column);
											
						}
						
						addElement(row,column);
						
						Marked_Number++;
						Position=Cell(row,column,1);
						play(Position);
						cout<<*this;
						if(counter%2==0){

							if(checked_x(check_count)==size){
								upper(check_count);
								winner++;
								break;
							}
						}
						else if(counter%2==1){
						
							if(checked_o(check_count)==size){
								upper(check_count);
								winner++;
								break;
							}
						}
									
						counter++;
					}
					
				}
				else{
					Marked_Number++;
					comp=play();
					hexCells[comp.get_compRow()][comp.get_compCol()].set_Cell(user2);
					addElement(comp.get_compRow()+1,comp.get_compCol());
					cout<<*this;
					if(checked_o(check_count)==size){
						upper(check_count);
						winner++;
						break;
					}
					counter++;

				}
				if(winner!=0){
					game_count=0;
					break;
				}
				if(menu_counter!=0){
					menu_counter=0;
					break;
				}
				
			}
	}

}