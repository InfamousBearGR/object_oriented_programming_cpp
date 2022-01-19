#include "Wall.h"
#include "User.h"
#include "Message.h"
#include "Network.h"
#include <vector>


using namespace std;


Wall::Wall(User *u){
	user = u;
}

vector<Message*> Wall::getMessages(){
	return messages;
}

void Wall::addMessage(Message *m){
	messages.push_back(m);
}

bool Wall::hasRightToPost(User *u){
	Network *net;
	net = Network::getNetwork();
	if(net->checkFriends(user, u)){
		return true;
	}
	return false;
}

