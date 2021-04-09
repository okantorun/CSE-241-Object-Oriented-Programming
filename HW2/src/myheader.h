#ifndef _MYHEADER_H
#define _MYHEADER_H

enum cell{user1='x',user2='o',empty='.'};
void board(const int &sayi,char array[13][13]);
void display(const int &sayi,int row,int column,char array[13][13],int counter,int selection);
int checked_x(char array[13][13],int sayi,int check_count=0);
int checked_o(char array[13][13],int sayi,int check_count=0);
void upper(char array[13][13],int sayi,int check_count,int row,int column,int count,int selection);
void computer_move(int sayi,int row,int column,char array[13][13],int counter,int selection,int check_count);
void edit_coordinate(char coordinate_r[25],char coordinate_c[20],int& row,int& column);
void save_file(char file_name[25],int board_size,char array[13][13],int count,int selection);
void load_file(char file_name[25],char array[13][13],int &selection,int &move,int &board_size);


#endif
