#include "Utilities.h"
#include <vector>
#include "User.h"
#include <string>
#include "Network.h"

using namespace std;

User* Utilities::findUserFromName(string n){
	Network * i = Network::getNetwork();
	
	for(int j = 0; j < i->getUsers().size(); j++){
		if(n == i->getUsers()[j]->getName()){
			return i->getUsers()[j];
		}
	}
	return NULL;
}
