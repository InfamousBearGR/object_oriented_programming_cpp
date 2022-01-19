#ifndef DATE_H
#define DATE_H
#include <string>
#include <ctime>

using namespace std;

class Date
{
	public:
		Date();
		string toString();
		void updateTime();	//This function is used for the creation of new Messages
		void setTime(string);	//This function is used for already created objects read from the file
	private:
		string date;
		
};

#endif
