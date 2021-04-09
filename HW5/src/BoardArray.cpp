#include "BoardArray.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>
using std::ifstream;
using std::ofstream;
using std::cin;
using std::cout;
using std::endl;


namespace Okan{
	


	HexArray1D& HexArray1D::operator=(const HexArray1D& rightSide){

		if(size!=rightSide.size){
			delete [] hexCellsArr;				//I added This condition to be more efficient		
			hexCellsArr=(Cell*) malloc((size*size)*sizeof(Cell));
		}
		counter=rightSide.counter;
		size=rightSide.size;
		x=rightSide.x;
		y=rightSide.y;							//I do the same operations in copy constructor in the assigment operator.
		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){										
				hexCellsArr[i*size+j].set_Cell(rightSide.hexCellsArr[i*size+j].get_Cell());
			}
		}
		
		return *this;
	
	}
	HexArray1D::HexArray1D(const HexArray1D& HexObject):AbstractHex()
	{
		hexCellsArr=(Cell*) malloc((size*size)*sizeof(Cell));
		for(int i=0;i<size;i++){							//I'm copying the information necessary for the game to continue.
			for(int j=0;j<size;j++){
				hexCellsArr[i*size+j].set_Cell(HexObject.hexCellsArr[i*size+j].get_Cell());
			}
		}

	}

	HexArray1D::~HexArray1D( ){

		delete [] coordinate_r;		//I did not add hexCells pointer to destructor to avoid the previous game's move information when switching between games.
		delete [] coordinate_c;
		delete [] load_name;
		delete [] save_name;
	    
	}
	void HexArray1D::setSize(int set_size){
		size=set_size;
	}
	void HexArray1D::reset(){
		int i,j;
		int  a,x;
		char str[] = {'a','b','c','d','e','f','g','h','I','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

		hexCellsArr=(Cell*) malloc((size*size)*sizeof(Cell));

		
		for(i=0;i<size;i++){
			if(i==0){
				cout <<"   ";
				for (int k = 0; k < size; ++k)
				{
					cout <<  str[k]<<"  ";

				}
				cout <<"\n";
			}
			cout <<  i+1<<" ";

			for(j=0;j<i;j++){
				cout <<"  ";
			}
			for(j=0;j<size;j++){
				cout <<" . ";
				hexCellsArr[i*size+j].set_Cell(empty);
			}
			cout <<"\n";
		}
	}
	int HexArray1D::isEnd_x(int check_count) const{
		int i;
		int j;

		if(check_count==size){
			return 1;
		}

		for(i=0;i<size;i++){
			if(hexCellsArr[i*size+check_count].get_Cell()==user1){		//the funciton controls to see if 'x' wins  with recursion.
				if(hexCellsArr[i*size+check_count-size+1].get_Cell()==user1){
					return isEnd_x(check_count+2);
				}
				else if(hexCellsArr[i*size+check_count+1].get_Cell()==user1){
								
					return isEnd_x(check_count+2);
				}
			}
		}

		if(check_count==size){
			return 1;
		}
		else
			return 0;
		
		
	}

	int HexArray1D::isEnd_o(int check_count) const{
		int i;
		int j;

		if(check_count==size){
			return 1;
		}
		for(i=check_count*size;i<check_count*size+size;i++){
			if(hexCellsArr[i].get_Cell()==user2){			//the funciton controls to see if 'o' wins  with recursion.
				for(j=i-1+size;j<i+1+size;j++){
					if(hexCellsArr[j].get_Cell()==user2){
						return isEnd_o(check_count+2);
					}

				}
			}
			
		}
		
		if(check_count==size){
			return 1;
		}
		else
			return 0;
		
	}
	void HexArray1D::upper(int check_count){
		int i;
		int j;
		
		if(counter%2==0){
			for(i=0;i<size;i++){
				if(hexCellsArr[i*size+check_count].get_Cell()==user1){		//the funciton controls to see if 'x' wins  with recursion.
					for(j=0;j<2;j++){
				
						if(hexCellsArr[i*size+check_count-size+1].get_Cell()==user1){
							hexCellsArr[i*size+check_count-size+1].set_Cell(user1-32);
							hexCellsArr[i*size+check_count].set_Cell(user1-32);
							upper(check_count+2);
						}
						
						else if(hexCellsArr[i*size+check_count+1].get_Cell()==user1){
						  hexCellsArr[i*size+check_count+1].set_Cell(user1-32);
						  hexCellsArr[i*size+check_count].set_Cell(user1-32);
						  upper(check_count+2);
						}
					}
				}
			}
			
		}
		else if(counter%2==1 && check_count!=size){

			for(i=check_count*size;i<check_count*size+size;i++){
				if(hexCellsArr[i].get_Cell()==user2){			//the funciton controls to see if 'o' wins  with recursion.
					for(j=i-1+size;j<i+1+size;j++){
						if(hexCellsArr[j].get_Cell()==user2){
							hexCellsArr[j].set_Cell(user2-32);
							hexCellsArr[i].set_Cell(user2-32);
						    upper(check_count+2);
						}

					}
				}
			
			}

		}
		if(check_count==size){
			print();
		}
		
		
	}
	void HexArray1D::play(Cell temp){
		int i,j;

		if(selection==1){	
			if(counter%2==0){
				hexCellsArr[(temp.get_userRow()-1)*size+temp.get_userCol()].set_Cell(user1);
						//it places the coordinates set by the user in the vector.	user vs comp
				setAddLastMove(temp.get_userRow()-1,temp.get_userCol());
			}

			
			print();
		}

		else if(selection==2){
			if(counter%2==0)
				hexCellsArr[(temp.get_userRow()-1)*size+temp.get_userCol()].set_Cell(user1);
				
			else if(counter%2==1)								//it places the coordinates set by the user in the vector.  user vs user
				hexCellsArr[(temp.get_userRow()-1)*size+temp.get_userCol()].set_Cell(user2);
				
			setAddLastMove(temp.get_userRow()-1,temp.get_userCol());
		}
	}

	HexArray1D::Cell HexArray1D::play(){
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
			if(hexCellsArr[i].get_Cell()==user2)
				control++;
		}
		
		if(control==0){										//I'm trying to determine the computer's moves as smart as possible.
			for(i=0;i<size;i++){
				for(j=0;j<size;j++){
					if(hexCellsArr[i*size+j].get_Cell()==user1){
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
				setAddLastMove(0,column-2);
				return temp;
			}
			else{
				temp=Cell(0,column+2);
				setAddLastMove(0,column+2);
				return temp;
			}
			
		}
		else{
			for(k=size-1;k>=0;k--){
				for(m=size-1;m>=0;m--){
					if(hexCellsArr[k*size+m].get_Cell()==user2){
						control_o++;
						break;
					}
				}
				if(control_o!=0)
					break;
			}
				
			for(j=m-1;j<m+1;j++){
				if(hexCellsArr[(k+1)*size+j].get_Cell()==empty){
					temp=Cell(k+1,j);						//I send the computer's move to my cell class with constructor and 
					setAddLastMove(k+1,j);
					return temp;							//assigned it to my object that I will return.
				}											
			}
			if(control2==0){
				
				if(hexCellsArr[k*size+(m-1)].get_Cell()==empty){
					temp=Cell(k,m-1);
					setAddLastMove(k,m-1);
					return temp;
				}
				else if(hexCellsArr[k*size+(m+1)].get_Cell()==empty){
					temp=Cell(k,m+1);
					setAddLastMove(k,m+1);
					return temp;
				}
				else{
					temp=Cell(k+2,m);
					setAddLastMove(k+2,m);
					return temp;
				}
			}

		}
		return temp;

	}
	void HexArray1D::print() const{
		char str[] = {'a','b','c','d','e','f','g','h','I','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
		int i,j;


		if(selection==1){
			if(counter%2==0){
				for(i=0;i<size;i++){
					if(i==0){
						cout <<"   ";
						for (int k = 0; k < size; ++k)
						{
							cout <<  str[k]<<"  ";

						}
						cout <<"\n";
					}

					cout <<  i+1<<" ";

					for(j=0;j<i;j++){
						cout <<"  ";
					}
					for(j=0;j<size;j++){
						cout <<" "<<hexCellsArr[i*size+j].get_Cell()<<" ";
						//cout <<" "<<hexCells[i][j].get_Cell()<<" ";
					}
					cout <<"\n";
				}										//it prints the current state of the board.
				
			}
			else if(counter%2==1){
				for(i=0;i<size;i++){
					if(i==0){
						cout <<"   ";
						for (int k = 0; k <size; ++k)
						{
							cout <<  str[k]<<"  ";

						}
						cout <<"\n";
					}

					cout <<  i+1<<" ";

					for(j=0;j<i;j++){
						cout <<"  ";
					}
					for(j=0;j<size;j++){
						cout <<" "<<hexCellsArr[i*size+j].get_Cell()<<" ";
					}
					cout <<"\n";
				}
				
			}

		}
		
		if(selection==2){
			if(counter%2==0){
				for(i=0;i<size;i++){
					if(i==0){
						cout <<"   ";
						for (int k = 0; k < size; ++k)
						{
							cout <<  str[k]<<"  ";

						}
						cout <<"\n";
					}

					cout <<  i+1<<" ";

					for(j=0;j<i;j++){
						cout <<"  ";
					}
					for(j=0;j<size;j++){
						cout <<" "<<hexCellsArr[i*size+j].get_Cell()<<" ";
						
					}
					cout <<"\n";
				}
			}
			else if(counter%2==1){

				
				for(i=0;i<size;i++){
					if(i==0){
						cout <<"   ";
						for (int k = 0; k < size; ++k)
						{
							cout <<  str[k]<<"  ";

						}
						cout <<"\n";
					}

					cout <<  i+1<<" ";

					for(j=0;j<i;j++){
						cout <<"  ";
					}
					for(j=0;j<size;j++){

						cout <<" "<<hexCellsArr[i*size+j].get_Cell()<<" ";
						
					}
					cout <<"\n";
				}
			}
		}

	}
	void HexArray1D::writeToFile(){
		
		ofstream outStream;
		outStream.open(save_name);

		if(selection==1){ outStream<<"1"<<endl;}				//it is recording the selection
		else{outStream<<"2"<<endl;}

		if(counter%2==0) {outStream<<"0"<<endl;}				//it records who's next.
		else{ outStream<<"1"<<endl;}

		outStream<<size<<endl;									//it records board_size

		for(int i=0;i<size;i++)
			for(int j=0;j<size;j++)
				outStream<<hexCellsArr[i*size+j].get_Cell();

		outStream.close( );
	}
	void HexArray1D::readFromFile(){
		char temp;
		int temp2,temp3;

		ifstream inStream;
		inStream.open(load_name);

		inStream>>selection;					//I'm taking back the information.
		inStream>>counter;
		inStream>>size;
		
		hexCellsArr=(Cell*) malloc((size*size)*sizeof(Cell));

		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				inStream>>temp;
				hexCellsArr[i*size+j].set_Cell(temp);
			}
		}

	}
	char HexArray1D::operator()(int row, int col) const{

		try{
			if(row>=0 && col>=0 && row<size && col<size){
				return hexCellsArr[(row)*size+col].get_Cell();
			}
			else{
				throw std::runtime_error("Runtime Exception");
			}
		}
		catch(std::exception & exp) {
			cout<<exp.what();
			return '\n';

		}
	}
	

	void HexArray1D::playGame(){
	int menu_counter=0;
	int row;
	int length;
	int column;
	int winner=0;
	int check_count=0;
	int set_Size;
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
		cin>>set_Size;
		while(set_Size<6 || set_Size>26){
			cout<<"Please enter a value between 6 and 26:";
			cin>>set_Size;
		}

		setSize(set_Size);
		reset();
	}
	switch(selection){
		case 1:
			while(1){
				if(game_count!=0){
					print();
					game_count=0;
				}
				if(counter%2==0 || (counter%2==1 && selection==2)){
					cout<<"Please enter a coordinate  Ex(C 5):";
					cout<<"\nex(LOAD load.txt) to load the game or ex(SAVE save.txt) to save the game:";
					cout<<"\nfor Back to Menu ex(BACK MENU):";
					cin>>coordinate_c>>coordinate_r;
					if(strcmp(coordinate_c,"SAVE")==0){
						save_name=new char[strlen(coordinate_r)];
						strcpy(save_name,coordinate_r);
						writeToFile();
					}
					else if(strcmp(coordinate_c,"LOAD")==0){
						load_name=new char[strlen(coordinate_r)];
						strcpy(load_name,coordinate_r);
						readFromFile();
						print();
					}
					else if(strcmp(coordinate_c,"BACK")==0 && strcmp(coordinate_r,"MENU")==0){
						game_count++;
						menu_counter++;	//a variable to get out of the game
						break;
					}
					else if(strcmp(coordinate_c,"LAST")==0 && strcmp(coordinate_r,"MOVE")==0){
						cout<<endl<<"Last Move : "<<(*this).lastMove()<<endl<<endl;						
					}
					
					else{
						

						edit_coordinate(row,column);
						while(column>size-1 || row>size){
							if(strcmp(coordinate_c,"UNDO")==0){
								cout<<"No moves left to erase"<<endl;
								cout<<"Please enter a valid coordinate:";
							}
							else
								cout<<"Please enter a valid coordinate:";

							cin>>coordinate_c>>coordinate_r;
							edit_coordinate(row,column);
							
						}
						while(hexCellsArr[(row-1)*size+column].get_Cell()!='.'){
							cout<<"This move has been made before.:";
							cin>>coordinate_c>>coordinate_r;
							edit_coordinate(row,column);
							
						}

					
						m_numberOfMoves++;
						
						Position=Cell(row,column,1);
						play(Position);
						print();

						if(isEnd_x(check_count)){
							upper(check_count);
							winner++;
							break;
						}
						if(isEnd_o(check_count)){
							upper(check_count);
							winner++;
							break;
						}
						counter++;
					}
				}
				else if(counter%2==1 && selection==1){

					m_numberOfMoves++;
			
					comp=play();
					hexCellsArr[comp.get_compRow()*size+comp.get_compCol()].set_Cell(user2);
					print();
					if(isEnd_o(check_count)){
						upper(check_count);
						winner++;
						game_count--;
						
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
					print();
				if(counter%2==0 || (counter%2==1 && selection==2)){
					cout<<"Please enter a coordinate  Ex(C 5):";
					cout<<"\nex(LOAD load.txt) to load the game or ex(SAVE save.txt) to save the game:";
					cout<<"\nfor Back to Menu ex(BACK MENU):";
					cin>>coordinate_c>>coordinate_r;
					if(strcmp(coordinate_c,"SAVE")==0){
						save_name=new char[strlen(coordinate_r)];
						strcpy(save_name,coordinate_r);
						writeToFile();
						
					}
					else if(strcmp(coordinate_c,"LOAD")==0){
						load_name=new char[strlen(coordinate_r)];
						strcpy(load_name,coordinate_r);
						readFromFile();
						print();							
					}
					else if(strcmp(coordinate_c,"BACK")==0 && strcmp(coordinate_r,"MENU")==0){
						game_count++;
						menu_counter++;
						counter--;
						break;
					}
					else if(strcmp(coordinate_c,"LAST")==0 && strcmp(coordinate_r,"MOVE")==0){
						cout<<endl<<"Last Move : "<<(*this).lastMove()<<endl<<endl;						
					}

					else{

						edit_coordinate(row,column);

						while(column>size-1 || row>size){
							if(strcmp(coordinate_c,"UNDO")==0){
								cout<<"No moves left to erase"<<endl;
								cout<<"Please enter a valid coordinate:";
							}
							else
								cout<<"Please enter a valid coordinate:";
							
							cin>>coordinate_c>>coordinate_r;
							edit_coordinate(row,column);
											
						}
						while(hexCellsArr[(row-1)*size+column].get_Cell()!='.'){
							cout<<"This move has been made before.:";
							cin>>coordinate_c>>coordinate_r;
							edit_coordinate(row,column);
											
						}
						
						m_numberOfMoves++;
				
						
						
						Position=Cell(row,column,1);
						play(Position);
						print();
						if(counter%2==0){

							if(isEnd_x(check_count)){
								upper(check_count);
								winner++;
								break;
							}
						}
						else if(counter%2==1){
						
							if(isEnd_o(check_count)){
								upper(check_count);
								winner++;
								break;
							}
						}
									
						counter++;
					}
					
				}
				else{
					m_numberOfMoves++;
				
					comp=play();
					hexCellsArr[comp.get_compRow()*size+comp.get_compCol()].set_Cell(user2);
					print();
					if(isEnd_o(check_count)){
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

}



