#include <iostream>
#include "myheader.h"
using namespace std;



int main()
{	
	int coordinate_r;
	char coordinate_c;
	char array[13][13];
	int count =0;
	int check_count=0;
	int sayi;
	int winner=0;
	int selection;
	int row,column;
	cout<<"(1)Computer-User or (2)User1-User2:";
	cin>>selection;
	switch(selection){
		case(1):
			cout<<"Please enter a board size Ex(Enter 6 for 6x6):";
			cin>>sayi;
			board(sayi,array);
			while(1){
				if(count%2==0){
					cout<<"Please enter a coordinate  Ex(C5):";
					cin>>coordinate_c>>coordinate_r;
					column=coordinate_c-65;
					row=coordinate_r;
					while(coordinate_c-65>sayi-1 || coordinate_r>sayi){
						cout<<"Please enter a valid coordinate:";				
						cin>>coordinate_c>>coordinate_r;
					}
					while(array[coordinate_r-1][coordinate_c-65]!='.'){
					cout<<"This move has been made before.:";
					cin>>coordinate_c>>coordinate_r;
					}
					display(sayi,coordinate_r,coordinate_c,array,count,selection);
					if(checked_x(array,sayi,check_count)==sayi){
						upper(array,sayi,check_count,coordinate_r,coordinate_c,count,selection);
						winner++;
						break;
					}
				}
				else if(count%2==1){
					computer_move(sayi,coordinate_r,coordinate_c,array,count,selection,check_count);
					display(sayi,coordinate_r,coordinate_c,array,count,selection);
					if(checked_o(array,sayi,check_count)==sayi){
						upper(array,sayi,check_count,coordinate_r,coordinate_c,count,selection);
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
			board(sayi,array);
			while(1){
				cout<<"Please enter a coordinate  Ex(C5):";
				cin>>coordinate_c>>coordinate_r;
				column=coordinate_c-65;
				row=coordinate_r;
				while(coordinate_c-65>sayi-1 || coordinate_r>sayi){
					cout<<"Please enter a valid coordinate:";
					cin>>coordinate_c>>coordinate_r;
				}
				
				while(array[coordinate_r-1][coordinate_c-65]!='.'){
					//cout<<coordinate_r<<"--"<<coordinate_c-65;
					cout<<"This move has been made before.:";
					cin>>coordinate_c>>coordinate_r;
				}
				display(sayi,coordinate_r,coordinate_c,array,count,selection);
				if(count%2==0){
					if(checked_x(array,sayi,check_count)==sayi){
						upper(array,sayi,check_count,coordinate_r,coordinate_c,count,selection);
						winner++;
						break;
					}
				}
				else if(count%2==1){
					if(checked_o(array,sayi,check_count)==sayi){
						upper(array,sayi,check_count,coordinate_r,coordinate_c,count,selection);
						winner++;
						break;
					}
				}
				if(winner!=0)
					break;
				count++;
				
			}
	}
}
