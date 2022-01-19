#ifndef NETWORK_H
#define NETWORK_H
#include "User.h"
#include <string>
#include <vector>
#include <map> 
using namespace std;
class User;
class Network
{
	public:
		void addUser(User*);	//Function to add a User object to the social media network
		void deleteUser(User*);	//Function to delete a User object from the network
		vector<User*> getUsers();	//Fuction to return the private User type vector users
		void makeFriends(User*,User*);	//Function to make 2 Users friends in the network which is then saved to the map friends
		vector<User*> getFriends(User*); //Function to return the Friends of a User
		bool checkFriends(User*, User*);	//A fuction to check if 2 users are friends for ifs
		vector<User*> getMutualFriends(User*, User*);	//Fuction that returns a vector of Mutual Friends for 2 Users
		static Network* getNetwork();	//Function to return private static Network object instance
		void unFriend(User*, User*);	//Function for unfriending 2 users
	private:
		Network();
		vector<User*> users;
		static Network *instance;
		map<User*, vector<User*> > friends;
		void addFriend(User*, User*);	//Function that adds a user to the map of a user's friends
};

#endif
