#include "Message.h"
#include <iostream>
#include "User.h"
#include "Date.h"
#include "Utilities.h"
#include <string>
#include <vector>

using namespace std;

Message::Message(string m, User *u){
	text=m;
	timestamp.updateTime();
	user = u;
}

int Message::getLikes(){
	return likes.size();
}

void Message::addLike(User *u){
		int i = Utilities::findPositionVector(likes, u);
	if(i==-1){
		likes.push_back(u);
	}
	else{
		cout<<"You have already liked this message"<<endl;
		system("PAUSE");
	}
	
}

void Message::removeLike(User *u){
	int i = Utilities::findPositionVector(likes, u);
	if(i!=-1){
		likes.erase(likes.begin()+i-1);
	}
	else{
		cout<<"User hasn't liked this message!"<<endl;
		system("PAUSE");
	}
}

Date Message::getTimestamp(){
	return timestamp;
}

string Message::getText(){
	return text;
}

vector<Message*> Message::getReplies(){
	return replies;
}

void Message::addReply(Message *m){
	replies.push_back(m);
}

User* Message::getUser(){
	return user;
}

vector<User*> Message::getLikeArray(){
	return likes;
}

void Message::setTimestamp(string t){

	timestamp.setTime(t);
}
