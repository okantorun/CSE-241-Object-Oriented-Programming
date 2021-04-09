#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include "myheader.h"
using std::ifstream;
using std::ofstream;
using namespace std;




void board(const int &sayi,char array[13][13]){
	int i,j;
	int  a,x;
	char str[] = {'a','b','c','d','e','f','g','h','I','j','k','l'};
	
	for(i=0;i<sayi;i++){
		if(i==0){
			cout <<"   ";
			for (int k = 0; k < sayi; ++k)
			{
				cout <<  str[k]<<"  ";

			}														//at first, it is printed on the screen depending on the index entered by the user
			cout <<"\n";
		}

		cout <<  i+1<<" ";

		for(j=0;j<i;j++){
			cout <<"  ";
		}
		for(j=0;j<sayi;j++){
			cout <<" . ";
			array[i][j]=empty;
		}
		cout <<"\n";
	}
} 

void display(const int &sayi,int row,int column,char array[13][13],int counter,int selection){
	int i,j;
	int  a,x;
	char str[] = {'a','b','c','d','e','f','g','h','I','j','k','l'};
	
	if(selection==1){
		if(counter%2==0){
			for(i=0;i<sayi;i++){
				if(i==0){
					cout <<"   ";
					for (int k = 0; k < sayi; ++k)
					{
						cout <<  str[k]<<"  ";

					}
					cout <<"\n";
				}							//prints the user's movement between the coordinate values I send from the main function and the user's computer

				cout <<  i+1<<" ";

				for(j=0;j<i;j++){
					cout <<"  ";
				}
				for(j=0;j<sayi;j++){
					if(i==row-1 && j==column){
						array[i][j]=user1;
						cout <<" "<<array[i][j]<<" ";
					}
					else{
						cout <<" "<<array[i][j]<<" ";
					}
				}
				cout <<"\n";
			}
			
		}
		else if(counter%2==1){
			for(i=0;i<sayi;i++){
				if(i==0){
					cout <<"   ";
					for (int k = 0; k < sayi; ++k)
					{
						cout <<  str[k]<<"  ";

					}
					cout <<"\n";
				}										//prints the movement of the computer with the value I send in the computer_move function.

				cout <<  i+1<<" ";

				for(j=0;j<i;j++){
					cout <<"  ";
				}
				for(j=0;j<sayi;j++){
					
						cout <<" "<<array[i][j]<<" ";
				}
				cout <<"\n";
			}
			
		}

	}
	
	else if(selection==2){
		if(counter%2==0){
			for(i=0;i<sayi;i++){
				if(i==0){
					cout <<"   ";
					for (int k = 0; k < sayi; ++k)
					{
						cout <<  str[k]<<"  ";

					}
					cout <<"\n";
				}

				cout <<  i+1<<" ";

				for(j=0;j<i;j++){								//prints user1 coordinates 
					cout <<"  ";
				}
				for(j=0;j<sayi;j++){
					if(i==row-1 && j==column){
						array[i][j]=user1;
						cout <<" "<<array[i][j]<<" ";
					}
					else{
						cout <<" "<<array[i][j]<<" ";
					}
				}
				cout <<"\n";
			}
		}
		else if(counter%2==1){
			for(i=0;i<sayi;i++){
				if(i==0){
					cout <<"   ";
					for (int k = 0; k < sayi; ++k)
					{
						cout <<  str[k]<<"  ";

					}
					cout <<"\n";
				}											//prints user1 coordinates 

				cout <<  i+1<<" ";

				for(j=0;j<i;j++){
					cout <<"  ";
				}
				for(j=0;j<sayi;j++){
					if(i==row-1 && j==column){
						array[i][j]=user2;
						cout <<" "<<array[i][j]<<" ";
					}
					else{
						cout <<" "<<array[i][j]<<" ";
					}
				}
				cout <<"\n";
			}
		}
	}



}

int checked_x(char array[13][13],int sayi,int check_count){
	int i;																	//I assigned a default value to the check_count.
	int j;
	for(i=0;i<sayi;i++){
		if(array[i][check_count]==user1){
			for(j=i-1;j<i+1;j++){
				if(array[j][check_count+1]==user1){							//after each 'x' cordinate value entered, I send the array to this 
					return checked_x(array,sayi,check_count+2);				//function and check whether the game is over with recursion.
				}															//I start with the leftmost column and continue with the neighbors of the X values,
			}																//each time I increase my counter,and when the table is complete, 
		}																	//I convert letters to uppercase if my counter is equal to the number of columns.
																				
	}
	
	return check_count;
	
}
int checked_o(char array[13][13],int sayi,int check_count){
	int i;
	int j;
	for(i=0;i<sayi;i++){													//for 'o' values
		if(array[check_count][i]==user2){
			for(j=i-1;j<i+1;j++){
				if(array[check_count+1][j]==user2){
					return checked_o(array,sayi,check_count+2);
				}
			}
		}
		
	}
	
	return check_count;
	
}

void upper(char array[13][13],int sayi,int check_count,int row,int column,int count,int selection){
	int i;
	int j;
	if(count%2==0){
		for(i=0;i<sayi;i++){
			if(array[i][check_count]==user1){
				for(j=i-1;j<i+1;j++){
					if(array[j][check_count+1]==user1){
						array[j][check_count+1]=user1-32;
						array[i][check_count]=user1-32;
					    upper(array,sayi,check_count+2,row,column,count,selection);

					}
				}
			}
						//I conver to uppercase the letters of the winning team with the same logic as we find the winner with recursion.
		}
	}
	else if(count%2==1){
		for(i=0;i<sayi;i++){
			if(array[check_count][i]==user2){
				for(j=i-1;j<i+1;j++){
					if(array[check_count+1][j]==user2){
						array[check_count+1][j]=user2-32;
						array[check_count][i]=user2-32;
					    upper(array,sayi,check_count+2,row,column,count,selection);

					}
				}
			}
			
		}

	}
	if(check_count==sayi){
		display(sayi,row,column,array,count,selection);			//I'm printing the final version of the game.
	}
}

void computer_move(int sayi,int row,int column,char array[13][13],int counter,int selection,int check_count){
	int i;
	int j;
	int k,m;
	int control=0;
	int control2=0;
	int control_o=0;
	

	for(i=0;i<sayi;i++){
		if(array[0][i]==user2)		//the computer makes its first move according to the value entered by the user and starts from the first line.
			control++;				//it then plays one line down on each move,preferring his right and left neighbors if there is no chance of moving below.
	}
	
	if(control==0){
		
		if(column+2>=sayi){
			array[0][column-2]=user2;
		}
		else{
			array[0][column+2]=user2;
		}
		
	}
	else{
		for(k=sayi-1;k>=0;k--){
			for(m=sayi-1;m>=0;m--){
				if(array[k][m]==user2){
					control_o++;
					break;
				}
			}
			if(control_o!=0)
				break;
		}
			
		for(j=m-1;j<m+1;j++){
			if(array[k+1][j]==empty){
				array[k+1][j]=user2;	
				control2++;
				break;
			}
		}
		if(control2==0){
			
			if(array[k][m-1]==empty){
				
				array[k][m-1]=user2;
			}
			else if(array[k][m+1]==empty){
				
				array[k][m+1]=user2;
			}
			else{
				
				array[k+2][m]=user2;
			}
		}

	}

}
void edit_coordinate(char coordinate_r[25],char coordinate_c[20],int& row,int& column){
	int length;

	length=strlen(coordinate_r);
	if(length==1){
		column=coordinate_c[0]-65;
		row=coordinate_r[0]-'0';
	}
	else if(length==2){
		column=coordinate_c[0]-65;							//I'm editing the entered string coordinate
		row=(coordinate_r[0]-'0')*10+coordinate_r[1]-'0';

	}
	else{
		column=coordinate_c[0]-65;
		row=15;

	}

}
void save_file(char file_name[25],int board_size,char array[13][13],int count,int selection){

	ofstream outStream;
	outStream.open(file_name);

	if(selection==1){ outStream<<"1"<<endl;}	//it is recording the selection
	else{outStream<<"2"<<endl;}

	if(count%2==0) {outStream<<"0"<<endl;}		//it records who's next.
	else{ outStream<<"1"<<endl;}

	outStream<<board_size<<endl;				//it records board_size

	for(int i=0;i<board_size;i++)
		for(int j=0;j<board_size;j++)			
			outStream<<array[i][j];

	outStream.close( );
}

void load_file(char file_name[25],char array[13][13],int &selection,int &move,int &board_size){
	
	
	ifstream inStream;
	inStream.open(file_name);

	inStream>>selection;
	inStream>>move;				//I take it back with a reference to use the information.
	inStream>>board_size;

	for(int i=0;i<board_size;i++)
		for(int j=0;j<board_size;j++)
			inStream>>array[i][j];

	inStream.close( );
}
