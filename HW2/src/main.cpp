#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include "myheader.h"
using std::ifstream;
using std::ofstream;
using namespace std;


int main(){	
	char coordinate_r[25];
	char coordinate_c[20];
	char array[13][13];
	int count =0;
	int check_count=0;
	int sayi;
	int move;
	int j=0;
	int i=5;
	int winner=0;
	int selection;
	decltype(count) row=0;					//Using decltype
	auto column=row;						//Using auto
	int length;
	cout<<"(1)Computer-User or (2)User1-User2:";
	cin>>selection;
	switch(selection){
		case(1):
			cout<<"Please enter a board size Ex(Enter 6 for 6x6):";
			cin>>sayi;
			while(sayi<6 || sayi>12){
				cerr<<"Please enter a value between 6 and 12:";
				cin>>sayi;
			}
			board(sayi,array);
			while(1){
				if(count%2==0 || (count%2==1 && selection==2)){
					cout<<"Please enter a coordinate  Ex(C 5):";
					cout<<"\nex(LOAD load.txt) to load the game or ex(SAVE save.txt) to save the game:";
					cin>>coordinate_c>>coordinate_r;
					if(strcmp(coordinate_c,"SAVE")==0){
						save_file(coordinate_r,sayi,array,count,selection);
						count++;

					}
					else if(strcmp(coordinate_c,"LOAD")==0){
						load_file(coordinate_r,array,selection,move,sayi);
						display(sayi,15,15,array,count,selection);
						//count++;


					}
					else{
						edit_coordinate(coordinate_r,coordinate_c,row,column);
						while(column>sayi-1 || row>sayi){
							cerr<<"Please enter a valid coordinate:";
							cin>>coordinate_c>>coordinate_r;
							edit_coordinate(coordinate_r,coordinate_c,row,column);
							
						}
						while(array[row-1][column]!='.'){
							cerr<<"This move has been made before.:";
							cin>>coordinate_c>>coordinate_r;
							edit_coordinate(coordinate_r,coordinate_c,row,column);
							
						}
						display(sayi,row,column,array,count,selection);
						if(checked_x(array,sayi)==sayi){
							upper(array,sayi,check_count,row,column,count,selection);
							winner++;
							break;
						}
						if(checked_o(array,sayi)==sayi){
							upper(array,sayi,check_count,row,column,count,selection);
							winner++;
							break;
						}
					}
				}
				else if(count%2==1 && selection==1){
					computer_move(sayi,row,column,array,count,selection,check_count);
					display(sayi,row,column,array,count,selection);
					if(checked_o(array,sayi)==sayi){
						upper(array,sayi,check_count,row,column,count,selection);
						winner++;
						break;
					}
					
				}
				if(winner!=0)
					break;

				count++;
			}

			break;
		case(2):
			cout<<"Please enter a board size Ex(Enter 6 for 6x6):";
			cin>>sayi;
			while(sayi<6 || sayi>12){
				cerr<<"Please enter a value between 6 and 12:";
				cin>>sayi;
			}
			board(sayi,array);
			while(1){
				if(count%2==0 || (count%2==1 && selection==2)){
					cout<<"Please enter a coordinate  Ex(C5):";
					cout<<"\nex(LOAD load.txt) to load the game or ex(SAVE save.txt) to save the game:";
					cin>>coordinate_c>>coordinate_r;
					if(strcmp(coordinate_c,"SAVE")==0){
						save_file(coordinate_r,sayi,array,count,selection);

					}
					else if(strcmp(coordinate_c,"LOAD")==0){
						load_file(coordinate_r,array,selection,move,sayi);
						display(sayi,15,15,array,count,selection);
						
					}
					else{
						edit_coordinate(coordinate_r,coordinate_c,row,column);

						while(column>sayi-1 || row>sayi){
							cerr<<"Please enter a valid coordinate:";
							cin>>coordinate_c>>coordinate_r;
							edit_coordinate(coordinate_r,coordinate_c,row,column);
								
						}
						while(array[row-1][column]!='.'){
							cerr<<"This move has been made before.:";
							cin>>coordinate_c>>coordinate_r;
							edit_coordinate(coordinate_r,coordinate_c,row,column);
								
						}
						display(sayi,row,column,array,count,selection);
						if(count%2==0){
							if(checked_x(array,sayi)==sayi){
								upper(array,sayi,check_count,row,column,count,selection);
								winner++;
								break;
							}
						}
						else if(count%2==1){
							if(checked_o(array,sayi)==sayi){
								upper(array,sayi,check_count,row,column,count,selection);
								winner++;
								break;
							}
						}
						
						count++;
					}
				}
				else{
					computer_move(sayi,row,column,array,count,selection,check_count);
					display(sayi,row,column,array,count,selection);
					if(checked_o(array,sayi)==sayi){
						upper(array,sayi,check_count,row,column,count,selection);
						winner++;
						break;
					}
					count++;

				}
				if(winner!=0)
					break;
				
			}
		}
		
}