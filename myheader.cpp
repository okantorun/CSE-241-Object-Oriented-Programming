#include <iostream>
#include "myheader.h"
using namespace std;

void board(int sayi,char array[13][13]){
	int i,j;
	int  a,x;
	char str[] = {'A','B','C','D','E','F','G','H','I','J','K','L'};
	
	for(i=0;i<sayi;i++){
		if(i==0){
			cout <<"   ";
			for (int k = 0; k < sayi; ++k)			//at first, it is printed on the screen depending on the index entered by the user
			{
				cout <<  str[k]<<"  ";

			}
			cout <<"\n";
		}

		cout <<  i+1<<" ";

		for(j=0;j<i;j++){
			cout <<"  ";
		}
		for(j=0;j<sayi;j++){
			cout <<" . ";
			array[i][j]='.';
		}
		cout <<"\n";
	}
} 

void display(int sayi,int coordinate_r,char coordinate_c,char array[13][13],int counter,int selection){
	int i,j;
	int  a,x;
	char str[] = {'A','B','C','D','E','F','G','H','I','J','K','L'};
	int row,column;


	column=coordinate_c-65;
	row=coordinate_r;
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
				}						//prints the user's movement between the coordinate values I send from the main function and the user's computer

				cout <<  i+1<<" ";

				for(j=0;j<i;j++){
					cout <<"  ";
				}
				for(j=0;j<sayi;j++){
					if(i==row-1 && j==column){
						array[i][j]='x';
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
				}								//prints the movement of the computer with the value I send in the computer_move function.

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

				for(j=0;j<i;j++){
					cout <<"  ";									//prints user1 coordinates 
				}
				for(j=0;j<sayi;j++){
					if(i==row-1 && j==column){
						array[i][j]='x';
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
				}												//prints user1 coordinates 

				cout <<  i+1<<" ";

				for(j=0;j<i;j++){
					cout <<"  ";
				}
				for(j=0;j<sayi;j++){
					if(i==row-1 && j==column){
						array[i][j]='o';
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
	int i;
	int j;
	for(i=0;i<sayi;i++){												//after each 'x' cordinate value entered, I send the array to this 
		if(array[i][check_count]=='x'){									//function and check whether the game is over with recursion.
			for(j=i-1;j<i+1;j++){										//I start with the leftmost column and continue with the neighbors of the X values,
				if(array[j][check_count+1]=='x'){						//each time I increase my counter,and when the table is complete, 
					return checked_x(array,sayi,check_count+2);			//I convert letters to uppercase if my counter is equal to the number of columns.
				}
			}
		}
		
	}
	
	return check_count;
	
}
int checked_o(char array[13][13],int sayi,int check_count){						//for 'o' values
	int i;
	int j;
	for(i=0;i<sayi;i++){
		if(array[check_count][i]=='o'){
			for(j=i-1;j<i+1;j++){
				if(array[check_count+1][j]=='o'){
					return checked_o(array,sayi,check_count+2);
				}
			}
		}
		
	}
	
	return check_count;
	
}

void upper(char array[13][13],int sayi,int check_count,int coordinate_r,char coordinate_c,int count,int selection){
	int i;
	int j;
	if(count%2==0){
		for(i=0;i<sayi;i++){
			if(array[i][check_count]=='x'){				
				for(j=i-1;j<i+1;j++){
					if(array[j][check_count+1]=='x'){
						array[j][check_count+1]='X';
						array[i][check_count]='X';
					    upper(array,sayi,check_count+2,coordinate_r,coordinate_c,count,selection);

					}
				}
			}						//I conver to uppercase the letters of the winning team with the same logic as we find the winner with recursion.
			
		}
	}
	else if(count%2==1){
		for(i=0;i<sayi;i++){
			if(array[check_count][i]=='o'){
				for(j=i-1;j<i+1;j++){
					if(array[check_count+1][j]=='o'){
						array[check_count+1][j]='O';
						array[check_count][i]='O';
					    upper(array,sayi,check_count+2,coordinate_r,coordinate_c,count,selection);

					}
				}
			}
			
		}

	}
	if(check_count==sayi){
		display(sayi,coordinate_r,coordinate_c,array,count,selection);	//I'm printing the final version of the game.
	}
}

void computer_move(int sayi,int coordinate_r,char coordinate_c,char array[13][13],int counter,int selection,int check_count){
	int i;
	int j;
	int k,m;
	int control=0;
	int control2=0;
	int control_o=0;
	int row,column;

	column=coordinate_c-65;			//the computer makes its first move according to the value entered by the user and starts from the first line.
	row=coordinate_r;				//it then plays one line down on each move,preferring his right and left neighbors if there is no chance of moving below.

	for(i=0;i<sayi;i++){
		if(array[0][i]=='o')
			control++;
	}
	
	if(control==0){
		
		if(column+2>=sayi){
			array[0][column-2]='o';
		}
		else{
			array[0][column+2]='o';
		}
		
	}
	else{
		for(k=sayi-1;k>=0;k--){
			for(m=sayi-1;m>=0;m--){
				if(array[k][m]=='o'){
					control_o++;
					break;
				}
			}
			if(control_o!=0)
				break;
		}
			
		for(j=m-1;j<m+1;j++){
			if(array[k+1][j]=='.'){
				array[k+1][j]='o';	
				control2++;
				break;
			}
		}
		if(control2==0){
			if(array[k][m-1]=='.'){
				array[k][m-1]='o';
			}
			else if(array[k][m+1]=='.'){
				array[k][m+1]='o';
			}
			else if(array[k+2][m]='.'){
				array[k+2][m]='o';
			}
			else if(array[k][m+3]=='.'){
				array[k][m+3]=='o';
			}
		}

	}

}
