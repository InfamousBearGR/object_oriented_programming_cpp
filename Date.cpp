#include "Date.h"
#include <string>
#include <ctime>

using namespace std;
		
Date::Date(){
	date = " ";
}

void Date::updateTime(){
	time_t now = time(0);
	date = ctime(&now);	
}

string Date::toString(){return date;}

void Date::setTime(string t){
	date = t;
}
