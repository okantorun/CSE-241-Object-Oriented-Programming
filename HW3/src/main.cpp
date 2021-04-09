#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>
#include "myheader.h"
using std::ifstream;
using std::ofstream;
using namespace std;


int main(){
	
	std::vector<Hex> HexObjects;
	int length;
	int game_number;
	int i;
	int select;
	int active_number;
	int game1,game2;

	Hex test(2,1);
	Hex test1(6);
	Hex test2;

	HexObjects.resize(5);
	
	cout<<"NOTE: You have five active games in the beginning"<<endl;
	while(1){
		cout<<endl<<"1)Active Game"<<endl;
		cout<<"2)New Game"<<endl;
		cout<<"3)Compare the number of cells of the two active games"<<endl;
		cout<<"4)Quit"<<endl<<endl;
		cout<<"Selection:";
		cin>>select;
		if(select==1){
			length=HexObjects.size();
			cout<<"You have "<<length<<" active games,"<<"which one do you want to play ?"<<endl;
			cout<<"ex(Enter '1' for 1. active game):";
			cin>>active_number;
			HexObjects[active_number-1].playGame();

		}
		else if(select==2){
			HexObjects.push_back(Hex());
			length=HexObjects.size();
			cout<<"This game is "<<length<<". game of active"<<endl;
			HexObjects[length-1].playGame();

		}
		else if(select==3){
			cout<<"Choose First Game ex(enter '1' for 1. active game):";
			cin>>game1;
			cout<<"Choose Second Game:";
			cin>>game2;
			if(HexObjects[game1-1].Compare(HexObjects[game2-1])==0){
				cout<<"The marked cell of the "<<game2<<". game is more than the "<<game1<<". game."<<endl;
			}
			else if(HexObjects[game1-1].Compare(HexObjects[game2-1])==1){
				cout<<endl<<"The marked cell of the "<<game1<<". game is more than the "<<game2<<". game."<<endl;
			}

		}
		else if(select==4)
			exit(1);		
	}
	
}