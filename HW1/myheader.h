#ifndef _MYHEADER_H
#define _MYHEADER_H

void board(int sayi,char array[13][13]);
void display(int sayi,int coordinate_r,char coordinate_c,char array[13][13],int counter,int selection);
int checked_x(char array[13][13],int sayi,int check_count);
int checked_o(char array[13][13],int sayi,int check_count);
void upper(char array[13][13],int sayi,int check_count,int coordinate_r,char coordinate_c,int count,int selection);
void computer_move(int sayi,int coordinate_r,char coordinate_c,char array[13][13],int counter,int selection,int check_count);


#endif
