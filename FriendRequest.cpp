#include "FriendRequest.h"
#include "User.h"
#include "Date.h"
#include <string>

using namespace std;

FriendRequest::FriendRequest(User *to, User *from){	
	userto=to;
	userfrom=from;
	state="pending"; //All created friend request have a pending state, then a user decides if he wants to accept
	timestamp.updateTime();
}

User* FriendRequest::getUserTo(){
	return userto;
}

User* FriendRequest::getUserFrom(){
	return userfrom;
}

Date FriendRequest::getTimestamp(){
	return timestamp;
}

void FriendRequest::setState(string s){
		if(s=="accept"||s=="decline"){	/*If a friend request gets accepted or declined 
		there is no need for it to exist*/
			state=s;
			userto->removeFriendRequest(this);	
		}
		else{
			state="pending";		 
		}
}

string FriendRequest::toString(){
	string s;
	if(state == "accept"){s="accepted";}
	else if(state == "decline"){s="declined";}
	else {s="pending";}
	return "Name: "+userfrom->getName()+"\tstate: "+ s + "\t" + timestamp.toString();	
}

void FriendRequest::setTimestamp(string t){
	timestamp.setTime(t);
}


