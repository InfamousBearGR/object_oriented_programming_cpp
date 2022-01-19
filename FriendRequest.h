#ifndef FRIENDREQUEST_H
#define FRIENDREQUEST_H
#include "User.h"
#include "Date.h"
#include <string>

using namespace std;
class User;
class FriendRequest
{
	public:
		FriendRequest(User*, User*);	/*The constructor for FriendRequests uses 2 User objects as parameters,
		the user who sent the friend request and the user that recieved it*/ 
		User* getUserTo();	//A get function that returns the private User object userto
		User* getUserFrom();	//A get function that returns the private User object userfroim
		Date getTimestamp();
		void setState(string);	//A function to set the state of a friend request (accepted, declined or pending)
		string toString();	//A toString function for printing the format of a friend request
		void setTimestamp(string);
		
	private:
		User *userto;	//The user that recieved the friend request
		User *userfrom;	//The User that send the friend request
		Date timestamp;	//Friend requests have a timestamp to see when they were sent
		string state;
};

#endif

