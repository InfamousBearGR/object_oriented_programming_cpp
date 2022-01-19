#ifndef UTILITIES_H
#define UTILITIES_H
#include <vector>
#include "User.h"
#include <string>
#include "Network.h"

/* The Utilities class has 2 functions which are vital for our programm and are used so much that
we decided to write them in a separate class and call them whenever we need them*/
using namespace std;

class User;
class Utilities
{
	public:
		template <typename T> /* We use templates in order to use findPositionVector
		for every type of objects*/
		static int findPositionVector(vector<T*>, T*);	/* A function that returns the 
		position of a specific object in a vector of that object*/
		static User* findUserFromName(string);	/* A function that returns a user from the user vector 
		in the Netowrk class by giving only the user's name*/ 
};

template <typename T>
int Utilities::findPositionVector(vector<T*> array, T*temp){
	int i;
	if(array.size()!=0){
	
		for(i=0; i<array.size(); i++){
			if(array[i]==temp){
				return i;
			}
		
		}
	}
	i=-1;

	return i;
}

#endif

