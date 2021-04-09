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

	Hex test2;

	HexObjects.resize(5);
	
	cout<<"NOTE: You have five active games in the beginning"<<endl;
	while(1){
		cout<<endl<<"1)Active Game"<<endl;
		cout<<"2)Compare the number of cells of the two active games"<<endl;
		cout<<"3)Quit"<<endl<<endl;
		cout<<"Selection:";
		cin>>select;
		if(select==1){
			length=HexObjects.size();
			cout<<"You have "<<length<<" active games,"<<"which one do you want to play ?"<<endl;
			cout<<"ex(Enter '1' for 1. active game):";
			cin>>active_number;
			while(active_number>length){
				cout<<endl<<"Please open one of the active games."<<endl;
				cout<<"ex(Enter '1' for 1. active game):";
				cin>>active_number;
			}
			HexObjects[active_number-1].playGame();

		}
		else if(select==2){
			cout<<"Choose First Game ex(enter '1' for 1. active game):";
			cin>>game1;
			cout<<"Choose Second Game:";
			cin>>game2;
			HexObjects[game1-1].set_Marked_Compare(HexObjects[game1-1].Marked_Compare());
			HexObjects[game2-1].set_Marked_Compare(HexObjects[game2-1].Marked_Compare());
			if(HexObjects[game1-1]>HexObjects[game2-1]){
				cout<<endl<<"The marked cell of the "<<game1<<". game is more than the "<<game2<<". game."<<endl;
			}
			else if(HexObjects[game1-1]<HexObjects[game2-1]){
				cout<<endl<<"The marked cell of the "<<game2<<". game is more than the "<<game1<<". game."<<endl;
			}
			else if(HexObjects[game1-1]==HexObjects[game2-1]){
				cout<<endl<<"The marked cell of the "<<game1<<". game is equals the "<<game2<<". game."<<endl;

			}

		}
		else if(select==3)
			exit(1);		
	}
	
}