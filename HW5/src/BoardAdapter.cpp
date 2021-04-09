#include "BoardAdapter.h"
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
	template<template<typename ...>class T>
	void HexAdapter<T>::setSize(int set_size){
		size=set_size;
	}
	template<template<typename ...>class T>
	void HexAdapter<T>::reset(){

		int i,j;
		int  a,x;
		char str[] = {'a','b','c','d','e','f','g','h','I','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

		hexCells.resize(size); 		////I determine the size of the vector as much as the size of the board taken from the user.

		for(i=0;i<size;i++){
			if(i==0){
				cout <<"   ";
				for (int k = 0; k < size; ++k)
				{
					cout <<  str[k]<<"  ";

				}
				cout <<"\n";
			}
			hexCells[i].resize(size);
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
	template<template<typename ...>class T>
	int HexAdapter<T>::isEnd_x(int check_count) const{
		int i;
		int j;

		for(i=0;i<size;i++){
			if(hexCells[i][check_count].get_Cell()==user1){		//the funciton controls to see if 'x' wins  with recursion.
				for(j=i-1;j<i+1;j++){
					if(j!=-1){
						if(hexCells[j][check_count+1].get_Cell()==user1){
							return isEnd_x(check_count+2);
						}
					}
				}
			}
		}

		if(check_count==size)
			return 1;
		else
			return 0;
		
		
	}
	template<template<typename ...>class T>
	int HexAdapter<T>::isEnd_o(int check_count) const{
		int i;
		int j;
		if(check_count==size)
			return check_count;
		for(i=0;i<size;i++){
			if(hexCells[check_count][i].get_Cell()==user2){			//the funciton controls to see if 'o' wins  with recursion.
				for(j=i-1;j<i+1;j++){
					if(hexCells[check_count+1][j].get_Cell()==user2){
						return isEnd_o(check_count+2);
					}

				}
			}
			
		}
		
		if(check_count==size)
			return 1;
		else
			return 0;
		
	}
	template<template<typename ...>class T>
	void HexAdapter<T>::upper(int check_count){
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
			print();
		}
		
		
	}
	template<template<typename ...>class T>
	void HexAdapter<T>::play(Cell temp){
		int i,j;

		if(selection==1){	

			if(counter%2==0){

				hexCells[temp.get_userRow()-1][temp.get_userCol()].set_Cell(user1);
				setAddLastMove(temp.get_userRow()-1,temp.get_userCol());

			}
			print();

		}

		else if(selection==2){

			if(counter%2==0){
				hexCells[temp.get_userRow()-1][temp.get_userCol()].set_Cell(user1);
			}
			else if(counter%2==1){										//it places the coordinates set by the user in the vector.  user vs user
				hexCells[temp.get_userRow()-1][temp.get_userCol()].set_Cell(user2);
			}		
			setAddLastMove(temp.get_userRow()-1,temp.get_userCol());
		}
	}

	template<template<typename ...>class T>
	typename HexAdapter<T>::Cell HexAdapter<T>::play(){
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
		
		if(control==0){	
											//I'm trying to determine the computer's moves as smart as possible.
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
					setAddLastMove(k+1,j);
					return temp;							//assigned it to my object that I will return.
				}											
			}
			if(control2==0){
				
				if(hexCells[k][m-1].get_Cell()==empty){
					temp=Cell(k,m-1);
					setAddLastMove(k,m-1);
					return temp;
				}
				else if(hexCells[k][m+1].get_Cell()==empty){
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
	template<template<typename ...>class T>
	void HexAdapter<T>::print() const{
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
						cout <<" "<<hexCells[i][j].get_Cell()<<" ";
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
						cout <<" "<<hexCells[i][j].get_Cell()<<" ";
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
						cout <<" "<<hexCells[i][j].get_Cell()<<" ";
						
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

						cout <<" "<<hexCells[i][j].get_Cell()<<" ";
						
					}
					cout <<"\n";
				}
			}
		}

	}

	template<template<typename ...>class T>
	void HexAdapter<T>::writeToFile(){
		
		ofstream outStream;
		outStream.open(save_name);

		if(selection==1){ outStream<<"1"<<endl;}				//it is recording the selection
		else{outStream<<"2"<<endl;}

		if(counter%2==0) {outStream<<"0"<<endl;}				//it records who's next.
		else{ outStream<<"1"<<endl;}

		outStream<<size<<endl;									//it records board_size

		for(int i=0;i<size;i++)
			for(int j=0;j<size;j++)
				outStream<<hexCells[i][j].get_Cell();
		

		outStream.close( );
	}

	template<template<typename ...>class T>
	void HexAdapter<T>::readFromFile(){
		char temp;
		int temp2,temp3;

		ifstream inStream;
		inStream.open(load_name);

		inStream>>selection;					//I'm taking back the information.
		inStream>>counter;
		inStream>>size;
		
		hexCells.resize(size);
		for(int i=0;i<size;i++){
			hexCells[i].resize(size);
			for(int j=0;j<size;j++){
				inStream>>temp;
				hexCells[i][j].set_Cell(temp);
			}
		}

	}

	template<template<typename ...>class T>
	char HexAdapter<T>::operator()(int row, int col) const{

		try{
			if(row>=0 && col>=0 && row<size && col<size){
				return hexCells[row][col].get_Cell();
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

	template<template<typename ...>class T>
	void HexAdapter<T>::playGame(){
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
					//cout<<(*this)(row,column)
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
						while(hexCells[row-1][column].get_Cell()!='.'){
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

					hexCells[comp.get_compRow()][comp.get_compCol()].set_Cell(user2);
					
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
						while(hexCells[row-1][column].get_Cell()!='.'){
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
					hexCells[comp.get_compRow()][comp.get_compCol()].set_Cell(user2);

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




