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

Hex::Hex():counter(0){	//a counter that determines who is next
}



int Hex::Marked_Compare(){
	int marked_counter=0;
	int i,j;
	
	for(i=0;i<size;i++){			//I find the number of marked cells in the object with the loop.
		for(j=0;j<size;j++){
			if(hexCells[i][j].getData==user1 || hexCells[i][j].getData==user2)
			marked_counter++;
		}	
	}

	return marked_counter;




}

void Hex::initial_board(){
	int i,j;
	int  a,x;
	char str[] = {'a','b','c','d','e','f','g','h','I','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

	hexCells.resize(size);	//I determine the size of the vector as much as the size of the board taken from the user.
	
	for(i=0;i<size;i++){
		if(i==0){
			cout <<"   ";
			for (int k = 0; k < size; ++k)
			{
				cout <<  str[k]<<"  ";

			}
			cout <<"\n";
		}
		hexCells[i].resize(size); //it is two-dimensional, I make every index of the vector as much as the width of the board.
		cout <<  i+1<<" ";

		for(j=0;j<i;j++){
			cout <<"  ";
		}
		for(j=0;j<size;j++){
			cout <<" . ";
			hexCells[i][j].getData=empty;
		}
		cout <<"\n";
	}
}	
int Hex::checked_x(int check_count){
	int i;
	int j;

	for(i=0;i<size;i++){
		if(hexCells[i][check_count].getData==user1){		//the funciton controls to see if 'x' wins  with recursion.
			for(j=i-1;j<i+1;j++){
				if(j!=-1){
					if(hexCells[j][check_count+1].getData==user1){
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
		if(hexCells[check_count][i].getData==user2){			//the funciton controls to see if 'o' wins  with recursion.
			for(j=i-1;j<i+1;j++){
				if(hexCells[check_count+1][j].getData==user2){
					return checked_o(check_count+2);
				}

			}
		}
		
	}
	
	return check_count;
	
}

void Hex::play(int cell_row,int cell_column){
	int i,j;

	if(selection==1){	
		if(counter%2==0){
			hexCells[cell_row-1][cell_column].getData=user1;		//it places the coordinates set by the user in the vector.	user vs comp
		}

		display();

	}

	else if(selection==2){

		if(counter%2==0){
			hexCells[cell_row-1][cell_column].getData=user1;
		}
		else if(counter%2==1){										//it places the coordinates set by the user in the vector.  user vs user
			hexCells[cell_row-1][cell_column].getData=user2;
		}		
	}
}

void Hex::play(){
	int row,column;
	int c=0;
	int i;
	int j;
	int k,m;
	int control=0;
	int control2=0;
	int control_o=0;
	

	for(i=0;i<size;i++){
		if(hexCells[0][i].getData==user2)
			control++;
	}
	
	if(control==0){										//I'm trying to determine the computer's moves as smart as possible.
		for(i=0;i<size;i++){
			for(j=0;j<size;j++){
				if(hexCells[i][j].getData==user1){
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
			hexCells[0][column-2].getData=user2;
		}
		else{
			hexCells[0][column+2].getData=user2;
		}
		
	}
	else{
		for(k=size-1;k>=0;k--){
			for(m=size-1;m>=0;m--){
				if(hexCells[k][m].getData==user2){
					control_o++;
					break;
				}
			}
			if(control_o!=0)
				break;
		}
			
		for(j=m-1;j<m+1;j++){
			if(hexCells[k+1][j].getData==empty){
				hexCells[k+1][j].getData=user2;	
				control2++;
				break;
			}
		}
		if(control2==0){
			
			if(hexCells[k][m-1].getData==empty){
				
				hexCells[k][m-1].getData=user2;
			}
			else if(hexCells[k][m+1].getData==empty){
				
				hexCells[k][m+1].getData=user2;
			}
			else{
				
				hexCells[k+2][m].getData=user2;
			}
		}

	}

}


void Hex::upper(int check_count){
	int i;
	int j;
	
	if(counter%2==0){
		for(i=0;i<size;i++){
			if(hexCells[i][check_count].getData==user1){
				for(j=i-1;j<i+1;j++){
					if(j!=-1){
						if(hexCells[j][check_count+1].getData==user1){
							hexCells[j][check_count+1].getData=user1-32;
							hexCells[i][check_count].getData=user1-32;
						    upper(check_count+2);

						}
					}
				}
			}
			
		}			////I conver to uppercase the letters of the winning team with the same logic as we find the winner with recursion.
	}
	else if(counter%2==1 && check_count!=size){
		for(i=0;i<size;i++){
			if(hexCells[check_count][i].getData==user2){
				for(j=i-1;j<i+1;j++){
					if(hexCells[check_count+1][j].getData==user2){
						hexCells[check_count+1][j].getData=user2-32;
						hexCells[check_count][i].getData=user2-32;
					    upper(check_count+2);

					}
				}
			}
			
		}

	}
	if(check_count==size){
		display();
		
	}
	
	
}

void Hex::display(){
	char str[] = {'a','b','c','d','e','f','g','h','I','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	Hex::Cell c1;
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
					cout <<" "<<hexCells[i][j].getData<<" ";
				}
				cout <<"\n";
			}										//it prints the current state of the board.
			
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
					cout <<" "<<hexCells[i][j].getData<<" ";
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
					cout <<" "<<hexCells[i][j].getData<<" ";
					
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
					cout <<" "<<hexCells[i][j].getData<<" ";
					
				}
				cout <<"\n";
			}
		}
	}
	

}
void Hex::edit_coordinate(char coordinate_r[25],char coordinate_c[25],int& row,int& column){
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
void Hex::save_file(char file_name[25]){

	ofstream outStream;
	outStream.open(file_name);

	if(selection==1){ outStream<<"1"<<endl;}				//it is recording the selection
	else{outStream<<"2"<<endl;}

	if(counter%2==0) {outStream<<"0"<<endl;}				//it records who's next.
	else{ outStream<<"1"<<endl;}

	outStream<<size<<endl;									//it records board_size

	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
			outStream<<hexCells[i][j].getData;

	outStream.close( );
}
void Hex::load_file(char file_name[25]){
	
	
	ifstream inStream;
	inStream.open(file_name);

	inStream>>selection;					//I'm taking back the information.
	inStream>>counter;
	inStream>>size;
	hexCells.resize(size);
	for(int i=0;i<size;i++){
		hexCells[i].resize(size);
		for(int j=0;j<size;j++){
			inStream>>hexCells[i][j].getData;
		}
	}
}


void Hex::playGame(){
	char coordinate_c[25],coordinate_r[25];
	char save_name[25];
	int menu_counter=0;
	int row;
	int column;
	int winner=0;
	int check_count=0;
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
					display();
				if(counter%2==0 || (counter%2==1 && selection==2)){
					cout<<"Please enter a coordinate  Ex(C 5):";
					cout<<"\nex(LOAD load.txt) to load the game or ex(SAVE save.txt) to save the game:";
					cout<<"\nfor Back to Menu ex(BACK MENU):";
					cin>>coordinate_c>>coordinate_r;
					if(strcmp(coordinate_c,"SAVE")==0){
						save_file(coordinate_r);
						counter++;

					}
					else if(strcmp(coordinate_c,"LOAD")==0){
						load_file(coordinate_r);
						display();
						counter++;


					}
					else if(strcmp(coordinate_c,"BACK")==0 && strcmp(coordinate_r,"MENU")==0){
						game_count++;
						menu_counter++;	//a variable to get out of the game
						break;
					}
					else{

						edit_coordinate(coordinate_r,coordinate_c,row,column);
						while(column>size-1 || row>size){
							cerr<<"Please enter a valid coordinate:";
							cin>>coordinate_c>>coordinate_r;
							edit_coordinate(coordinate_r,coordinate_c,row,column);
							
						}
						while(hexCells[row-1][column].getData!='.'){
							cerr<<"This move has been made before.:";
							cin>>coordinate_c>>coordinate_r;
							edit_coordinate(coordinate_r,coordinate_c,row,column);
							
						}

						Marked_Number++;		//the number of marked cells is increasing.

						play(row,column);
						display();

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
					}
				}
				else if(counter%2==1 && selection==1){

					Marked_Number++;

					play();
					display();
					if(checked_o(check_count)==size){
						upper(check_count);
						winner++;
						game_count--;
						cout<<game_count;
						break;
					}
					
				}
				if(winner!=0)
					break;
				

				if(menu_counter!=0){
					menu_counter=0;
					break;
				}

				counter++;
			}

			break;


		case 2:
			
			while(1){
				if(game_count!=0)
					display();
				if(counter%2==0 || (counter%2==1 && selection==2)){
					cout<<"Please enter a coordinate  Ex(C 5):";
					cout<<"\nex(LOAD load.txt) to load the game or ex(SAVE save.txt) to save the game:";
					cout<<"\nfor Back to Menu ex(BACK MENU):";
					cin>>coordinate_c>>coordinate_r;
					if(strcmp(coordinate_c,"SAVE")==0){
						save_file(coordinate_r);

					}
					else if(strcmp(coordinate_c,"LOAD")==0){
						load_file(coordinate_r);
						display();
							
					}
					else if(strcmp(coordinate_c,"BACK")==0 && strcmp(coordinate_r,"MENU")==0){
						game_count++;
						menu_counter++;
						counter--;
						break;
					}
					else{

						edit_coordinate(coordinate_r,coordinate_c,row,column);

						while(column>size-1 || row>size){
							cerr<<"Please enter a valid coordinate:";
							cin>>coordinate_c>>coordinate_r;
							edit_coordinate(coordinate_r,coordinate_c,row,column);
											
						}
						while(hexCells[row-1][column].getData!='.'){
							cerr<<"This move has been made before.:";
							cin>>coordinate_c>>coordinate_r;
							edit_coordinate(coordinate_r,coordinate_c,row,column);
											
						}
						
						Marked_Number++;

						play(row,column);
						display();
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

					play();
					display();
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