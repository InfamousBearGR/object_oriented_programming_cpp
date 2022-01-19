#include "User.h"
#include "FriendRequest.h"
#include "Wall.h"
#include "Message.h"
#include <string>
#include <vector>
#include "Utilities.h"
#include "Network.h"

using namespace std;
	
User::User(string n, string e){
	setName(n);
	setEmail(e);
	wall = new Wall(this);
}

string User::getName(){return name;}
string User::getEmail(){return email;}

void User::setName(string n){name=n;}
void User::setEmail(string e){email=e;}

void User::respondRequest(FriendRequest *fr, string state){
	Network * i = Network::getNetwork();	/*We create a Network object which returns the instance 
	object of network, this is done to access the network functions and we don't create a network instance 
	because only 1 newtwork object must be created */
	fr->setState(state); 
	if(state=="accept"){
		i->makeFriends(this, fr->getUserFrom());	//A network function to make 2 users friends
	}
}

void User::removeFriend(User *u){
	Network * i = Network::getNetwork();
	i->unFriend(this, u);
	i->unFriend(u, this);
}

Wall* User::getWall(){
	return wall;
}

void User::addMessage(Message *m){
	getWall()->addMessage(m);
	
}

void User::like(Message *m){
	m->addLike(this);
}

vector<User*> User::getFriends(){
	Network * i = Network::getNetwork();
	return i->getFriends(this);
	
}

vector<FriendRequest*> User::getFriendRequests(){
	return friendrequests;
}

void User::sendRequest(User *u){
	FriendRequest *fr = new FriendRequest(this, u);
	friendrequests.push_back(fr);
}

void User::removeFriendRequest(FriendRequest *fr){
	int i = Utilities::findPositionVector(friendrequests, fr);
	friendrequests.erase(friendrequests.begin()+i-1);
}
