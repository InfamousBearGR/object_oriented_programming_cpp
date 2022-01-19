#ifndef USER_H
#define USER_H
#include "FriendRequest.h"
#include "Wall.h"
#include "Message.h"
#include <string>
#include <vector>
#include "Utilities.h"
#include "Network.h"


using namespace std;

class Wall;
class FriendRequest;
class User
{
	public:
		User(string, string);	//User constructor gets 2 strings as parameters: name and email
		string getName();	//getName function to return private string name
		string getEmail();	//getEmail function to return private string email
		void setName(string);	//setName function for setting private string name
		void setEmail(string);	//setEmail function for setting private string email
		void sendRequest(User*);	//Function to send a friend request
		void respondRequest(FriendRequest*, string);	//Function to respond to a friend request
		void removeFriend(User*);	//Function to remove a User who is a Friend
		void removeFriendRequest(FriendRequest*);	//Function to remove a recieved frined request
		void addMessage(Message*);	//Function to add a message to our wall
		void like(Message*);	//Function to like a message on our wall
		Wall* getWall();	//Function to return the private Wall type wall object
		vector<User*> getFriends();	//A User vector type function to return the User's friends
		vector<FriendRequest*>	getFriendRequests(); //A FriendRequest vector type to return the user's friend requests
	private:
		string name;
		string email;
		vector<FriendRequest*> friendrequests;
		Wall *wall;		
};

#endif
