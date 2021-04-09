#include "BoardVector.h"
#include "BoardArray.h"
#include "BoardAdapter.h"
#include "BoardAdapter.cpp"
#include "GlobalFunction.h"
#include <iostream>
#include <vector>
#include <deque>


int main(){

	
	Okan::AbstractHex* HexObjects[5];
	
	HexObjects[0] = new Okan::HexVector();
	HexObjects[1] = new Okan::HexArray1D();
	HexObjects[2] = new Okan::HexAdapter<std::vector>;
	HexObjects[3] = new Okan::HexAdapter<std::deque>;
	HexObjects[4] = new Okan::HexArray1D;

	
	int select;
	int active_number;
	int game1,game2;

	
	std::cout<<"NOTE: You have five active games in the beginning"<<endl;
	while(1){
		std::cout<<endl<<"1)Active Game"<<endl;
		std::cout<<"2)Compare The Equality Of The Two Boards"<<endl;
		std::cout<<"3)Quit"<<endl<<endl;
		std::cout<<"Selection:";
		std::cin>>select;
		if(select==1){
			std::cout<<"You have 5 active games,"<<"which one do you want to play ?"<<endl;
			std::cout<<"ex(Enter '1' for 1. active game):";
			std::cin>>active_number;
			while(active_number>5){
				std::cout<<endl<<"Please open one of the active games."<<endl;
				std::cout<<"ex(Enter '1' for 1. active game):";
				std::cin>>active_number;
			}
			HexObjects[active_number-1]->playGame();

		}
		else if(select==2){
			std::cout<<"Choose First Game ex(enter '1' for 1. active game):";
			std::cin>>game1;
			std::cout<<"Choose Second Game:";
			std::cin>>game2;
			
			if(*HexObjects[game1-1]==*HexObjects[game2-1]){
				std::cout<<endl<<"Two boards are equal"<<endl;

			}
			else{
				std::cout<<endl<<"Two boards are not equal"<<endl;		
			}

		}
		else if(select==3)
			exit(1);		
	}


/////**************GLOBAL FUNCTİON***********////
	
	if (isValidSequence(HexObjects,5))
        std::cout << "\n\nValid sequence!\n";
   
    else
        std::cout << "\n\nNot Valid sequence!\n";
    
	
}
