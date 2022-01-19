#include <iostream>
#include <string>
#include "Menu.h"

using namespace std;


int main(int argc, char** argv) {
	Menu::loadFile(); //Firstly we load all the date from our file
    Menu::printRegisterLogIn();	//Then the programm begins with the first login or registration 
    Menu::printMenu();	//After that the menu loads where the primary calling of functions is
   
	

	return 0;
}
