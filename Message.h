#ifndef MESSAGE_H
#define MESSAGE_H
#include <iostream>
#include "User.h"
#include "Date.h"
#include "Utilities.h"
#include <string>
#include <vector>

using namespace std;
class User; 
class Message
{
	public:
		Message(string, User*); /*Message constructor which has a string parameter for the text 
		and a user parameter for which user's wall is this message written(we use it for the same user and 
		the user's friends) */ 
		int getLikes();	//A function that returns the number of likes on a post(basically the size of likes vector
		void addLike(User*); //A function that add the user that liked a post to the likes vector
		void removeLike(User*); //A function to remove a like from a post
		Date getTimestamp();	//A date type function to get the timestamp for a message
		string getText();	//A get function to access the private string text
		vector<Message*> getReplies();	//A Message type vector for the replies of a message
		User* getUser();	//A get function to return the private user object
		void addReply(Message*);	//A function that add the replies of message
		vector<User*> getLikeArray();	/*A get function that returns a User type vector of 
		the Users that have liked a post*/
		void setTimestamp(string);	//A function to set the timestamp of a message or reply read from the file
	private:
		Date timestamp;
		string text;
		vector<User*> likes; /*We decided to make likes a User type vector so that we would be able
		to check if user has already liked a message, if we want the number of likes we use getLikes*/
		vector<Message*> replies; /*Replies have the same logic of a message(a text, a timestamp and a User)
		so instead of creating a new class for the replies we made the a vector of messages*/
		User* user;
};

#endif
