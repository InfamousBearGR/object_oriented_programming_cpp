#ifndef MENU_H
#define MENU_H
#include "User.h"
#include <string>
#include "Network.h"
#include "Utilities.h"
#include "Message.h"
#include <iostream>
#include <fstream>
#include "FriendRequest.h"

using namespace std;
class User;
class Menu
{
	public:
		void static printRegisterLogIn();	//The message that prompths the user to login or register
		void static registerUser();	//The function for registering a new User
		void static logIn();	//The function to connect the email given to an existing User
		void static printMenu();	//The basic menu that the user interacts with
		void static seeWall(User*);	//The function to see a user's wall or his own wall
		void static sendFriendRequest();	//A function for creating friend requests
		void static respondToRequests();	//A function to respond to friend requests
		void static seeMyFriends();	//A function that prints a user's friends
		void static exit();	//The method that ends the programm but also saves all the information to our file
		void static read(string*);	/*cin does not allow spaces in a single string, so we created this method
		to be able to do that*/
		void static loadFile();	//The function that loads the file's data
		static User *u;
		
};


#endif
