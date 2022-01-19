#include "Network.h"
#include "User.h"
#include <string>
#include <vector>
#include <map> 

using namespace std;

Network* Network::instance = 0;

Network::Network(){
	
}

vector<User*> Network::getUsers(){
	return users;
}

void Network::addUser(User *u){
	int i = Utilities::findPositionVector(users, u);
	if(i==-1){
		users.push_back(u);
	}
	else{
	
		cout<<"The user already exists!"<<endl;
	}
}

void Network::deleteUser(User *u){
	int i = Utilities::findPositionVector(users, u);
	if(i!=-1){
		users.erase(users.begin()+i-1);
	}
	else{
	
		cout<<"The user doesn't exist!"<<endl;
	}
}

void Network::makeFriends(User *u1, User *u2){
	int i = Utilities::findPositionVector(u1->getFriends(), u2);
	if(i==-1){
		addFriend(u1, u2);
		addFriend(u2, u1);
	}
}

vector<User*> Network::getFriends(User *u){
	return friends[u];
}

bool Network::checkFriends(User *u1, User *u2){
	
	if(Utilities::findPositionVector(u2->getFriends(), u1) != -1){
		return true;
	}
	
	return false;
}

vector<User*> Network::getMutualFriends(User *u1, User *u2){
	vector<User*> mutuals;
	int i, j;
	
	for(i=0; i < u1->getFriends().size(); i++){
		for(j=0; j < u2->getFriends().size(); j++){
			if(u1->getFriends()[i]==u2->getFriends()[j]){
				mutuals.push_back(u1->getFriends()[i]);
			}
		}
	}
	return mutuals;
}

Network* Network::getNetwork(){
	if(instance==0){ /*If no instance has been created the initiation of the programm, 
	then a new a Network object is created */
		
		instance = new Network();
	}
	return instance; /*After the creation or call of getNetwork in any classes
	 the instance is returned for uses in other classes*/
}

void Network::addFriend(User *u1, User *u2){
	friends[u1].push_back(u2);
	
}

void Network::unFriend(User *u, User *removed){
	int i = Utilities::findPositionVector(friends[u], removed);
	friends[u].erase(friends[u].begin()+i);
	
}
