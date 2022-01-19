#ifndef WALL_H
#define WALL_H
#include "User.h"
#include "Message.h"
#include "Network.h"
#include <vector>

using namespace std;
class User;
class Message;
class Wall
{
	public:
		Wall(User*); //The constructor of Wall uses a User object as a parameter because a User has his own wall
		vector<Message*> getMessages(); //A function that returns the private Message type vector messages
		void addMessage(Message*);	//A function to add Message objects to the vector messages
		bool hasRightToPost(User*); /*A function to check if the user writing 
		the message is a friend of the user's wall*/
	private:
		vector<Message*> messages;	/*A wall has written messages on it, 
		so we use a Message type vector to save these messages*/
		User *user;
		
};

#endif
