#include "Menu.h"
#include "User.h"
#include <string>
#include "Network.h"
#include "Utilities.h"
#include "Message.h"
#include <iostream>
#include <fstream>
#include "FriendRequest.h"

using namespace std;

User * Menu::u;
/* To load the data of our file we used a weird but working method, pretty much we wrote all the strings 
in the file in the exit() function in a way where we can easily locate everything, e.g. all the users name 
are written normally, after a user's name the email is written with a tab, then all the friends with a tab
until the keyword fr is found, after a fr all the friend requests are written with the format of the toString 
in the FriendRequest class, when the wall keyword is found the friend requests end and the wall messages begin 
again with a tab. After the wall the users' names that have liked that message are written with 2 tabs.
Then whenthe keyword replies indicates the replies that have the same format as wall but again with 2 tabs
as the likes, then the next wall message is written and under it the likes and replies in the same way.
After that this begins again for every user, for reference here is an example:

Alexandros Karagiannhs
	alexkarag@gmail.com
	Michael Avramopoulos
	fr
	Name: Eystratios Pantazaras	state: pending	Fri May 31 22:02:14 2019
	wall
	Alexandros Karagiannhs	Hello	Tue May 28 11:54:15 2019
		replies
	Alexandros Karagiannhs	What's up?	Tue May 28 11:54:15 2019
		Michael Avramopoulos
		replies
		Michael Avramopoulos	Good, you?	Tue May 28 11:54:15 2020
		
so the user is the 1st string, his friends are the next string until the fr keyword and so on.
Also in orded to separte the strings on the messages, replies and friend requests we used a string 
constructor that takes as parameters the beginning of the line, or a tab in as a starting point
in the frined requests and the messages or 2 tabs in the replies and the end of the line, or the number 
of tabs we want the string to end*/
void Menu::loadFile(){
	string line;
	ifstream cppfile1("save.txt");
	/*1st if is for getting users only, this is done so that we can create User objects 
	to save them in a vector and the save their information such as messages on their wall, their email etc*/
	if(cppfile1.is_open()){
		Network * i = Network::getNetwork();
		while(getline(cppfile1, line)){
			if(line.at(0)!='\t'){
				i->addUser(new User(string(line.begin(), line.begin() + line.length())," "));
			}
		}
		cppfile1.close();
	}
	else{
		cout<<"File did not load"<<endl;
		system("PAUSE");
	}
	
	//2nd if for everything else
	ifstream cppfile("save.txt");
	if(cppfile.is_open()){
		Network * i = Network::getNetwork();
		User* user;
		getline(cppfile, line);
		for(int j=0; j<i->getUsers().size(); j++){
			user = Utilities::findUserFromName(string(line.begin(), line.begin() + line.length()));
			if(!getline(cppfile, line))break;
			user->setEmail(string(line.begin() + 1, line.begin() + line.length()));
			if(!getline(cppfile, line))break;
			while(line!="\tfr"){
				User *user1 = Utilities::findUserFromName(string(line.begin() + 1, line.begin() + line.length()));
				
				i->makeFriends(user, user1);
				if(!getline(cppfile, line))break;
			}
			int k=0;
			if(!getline(cppfile, line))break;
			while(line != "\twall"){
				User *user1 = Utilities::findUserFromName(string(line.begin() + 7, line.begin() + line.find("\t",1)));
				
				string timestamp = string(line.begin() + line.find("\t",line.find("\t",1) + 1) + 1 , line.begin() + line.length())+"\n";
				user->sendRequest(user1);
				user->getFriendRequests()[k]->setTimestamp(timestamp);
				k++;	
				if(!getline(cppfile, line))break;		
			}
			
			if(!getline(cppfile, line))break;
			while(string(line.begin(),line.begin() + 1) == "\t" && string(line.begin() + 1,line.begin() + 2) != "\t" ){
					User *user1 = Utilities::findUserFromName(string(line.begin() + 1, line.begin() + line.find("\t",1)));
					
					string text = string((line.begin() + line.find("\t",1)+1),line.begin() + line.find("\t",line.find("\t",1)+1));
					string timestamp1 = string(line.begin() + line.find("\t",line.find("\t",1)+1)+1,line.begin() + line.length())+"\n";
					Message *m = new Message(text, user1);
					m->setTimestamp(timestamp1);
					if(!getline(cppfile, line))break;
					
					while(line!="\t\treplies"){
						User *user2 = Utilities::findUserFromName(string(line.begin() + 2,line.begin() + line.length()));
						m->addLike(user2);
						if(!getline(cppfile, line))break;
					}
					if(!getline(cppfile, line))break;
					
					while(string(line.begin() + 1,line.begin() + 2) == "\t"){
						User *user3 = Utilities::findUserFromName(string( line.begin() + 2,line.begin() + line.find("\t", 3)));
						string text = string((line.begin() + line.find("\t",3)+1),line.begin() + line.find("\t",line.find("\t",3)+1));
						string timestamp2 = string(line.begin() + line.find("\t", line.find("\t",3)+1) + 1,line.begin() + line.length())+"\n";
						
						Message *reply = new Message(text, user3);
						reply->setTimestamp(timestamp2);
						m->addReply(reply);	
						if(!getline(cppfile, line))break;
					
					}
					user1->getWall()->addMessage(m);
					
				
			
		}
		
	}
	cppfile.close();
}
	

	else{
		cout<<"File did not load"<<endl;
		system("PAUSE");
	}
	cout<<"PEOS"<<endl;
}

void Menu::printRegisterLogIn(){
	string choice;
	do{
		system("CLS");
		cout<<"Press 1 to Register or 2 to Log in"<<endl;
		cin>>choice;
		if(choice=="1"){
			Menu::registerUser();
		}
		else if(choice=="2"){
			Menu::logIn();
		}
		else if(choice !="1" && choice!="2" ){
			cout<<"Wrong number, please try again"<<endl;
		}
	}while(choice !="1" && choice!="2");
	
}

void Menu::registerUser(){
	system("CLS");
	string n, e;
	cout<<"Please type Name and Surname"<<endl;
	read(&n);
	cout<<"Please type Email"<<endl;
	cin>>e;
	cout<<e<<endl;
	u = new User(n, e);
	Network * i = Network::getNetwork();
	i->addUser(u);
	cout<<"Welcome User "<<n<<endl;
}

void Menu::logIn(){
	bool f = false;
	string e;
	do{
	system("CLS");
	cout<<"Please type your Email or write 'BACK' to go back"<<endl;
	read(&e);
	Network * i = Network::getNetwork();
	if(e =="BACK")break;
	for(int j=0; j < i->getUsers().size(); j++ ){		
		if(e == i->getUsers()[j]->getEmail()){
			u = i->getUsers()[j];
			f = true;
		}
		
	}
	if(f)
	{
		cout<<"Welcome "<<u->getName()<<"!"<<endl;
		system("PAUSE");
	}
	else{
		cout<<"Non-existing user, please try again"<<endl;
		system("PAUSE");
	}
	}while(!f);
	if(e=="BACK"){printRegisterLogIn();}
}

void Menu::printMenu(){
	int i;
	do{
		system("CLS");
		string n;
		cout<<"To see your Wall press 1"<<endl
			<<"To see a User's wall press 2"<<endl
			<<"To send a Friend Request press 3"<<endl
			<<"To see your Friend Requests press 4"<<endl
			<<"To see your Friends press 5"<<endl
			<<"To log out press 6"<<endl
			<<"To exit press 7"<<endl;
		cin>>i;
		if(i == 1 ){
			seeWall(u);
		}
		else if(i == 2 ){
			do{
				cout<<"Which friend's wall would you like to see?"<<endl;
				read(&n);
				if(Utilities::findUserFromName(n) == NULL){
					cout<<"User doesn't exist"<<endl;
				}
			}while(Utilities::findUserFromName(n) == NULL);	
			seeWall(Utilities::findUserFromName(n));
		}
		else if(i == 3 ){
			sendFriendRequest();
		}
		else if( i == 4 ){
			respondToRequests();
		}
		else if ( i == 5 ){
			seeMyFriends();
		}
		else if( i == 6 ){
			printRegisterLogIn();
		}
		else if( i == 7 ){
			exit();
		}
		else if(i!=1 && i!=2 && i!=3 && i!=4 && i!=5 && i!=6 && i!=7 ){
			cout<<"Wrong number, please try again"<<endl;
			system("PAUSE");
		}
	}while(i!= 7);
}

void Menu::seeWall(User *user){
	system("CLS");
	int choice;
	int choice1;
	string text;
	for(int i = 0; i < user->getWall()->getMessages().size(); i++ ){
		cout<<i+1<<". "<<user->getWall()->getMessages()[i]->getText()<<"\t(Likes: "<<user->getWall()->getMessages()[i]->getLikes()<<")\t-" << user->getWall()->getMessages()[i]->getUser()->getName()<< " " <<user->getWall()->getMessages()[i]->getTimestamp().toString();
		for(int k = 0; k < user->getWall()->getMessages()[i]->getReplies().size(); k++){
			cout<<"\t"<<k+1<<". "<<user->getWall()->getMessages()[i]->getReplies()[k]->getText()<< "\t-" << user->getWall()->getMessages()[i]->getReplies()[k]->getUser()->getName()<< " "<< user->getWall()->getMessages()[i]->getReplies()[k]->getTimestamp().toString();
		}
		
	}
	cout<<endl;
	cout<<"Press 1 to post a message"<<endl
		<<"Press 2 to reply to a message"<<endl
		<<"Press 3 to like a message"<<endl
		<<"Press 4 to go back"<<endl;
	cin>>choice;
	if(choice == 1 ){
		if(user->getWall()->hasRightToPost(u) || user==u){
			cout<<"Type your message"<<endl;
			read(&text);
			user->getWall()->addMessage(new Message(text, u));
			seeWall(user);
		}
		else{
			cout<<"You are not friends with the user "<<user->getName()<<endl;
			system("PAUSE");
			seeWall(user);
		}
	}
	else if(choice == 2 ){
		if(user->getWall()->hasRightToPost(u) || user==u){
			cout<<"Choose a message"<<endl;
			cin>>choice1;
			cout<<"Type your reply"<<endl;
			read(&text);
			user->getWall()->getMessages()[choice1-1]->addReply(new Message(text, u));
			seeWall(user);	
		}
		else{
			cout<<"You are not friends with the user "<<user->getName()<<endl;
			system("PAUSE");
			seeWall(user);
		}
	}
	else if(choice == 3){
		int i;
		if(user->getWall()->hasRightToPost(u) || user==u){
			do{		
				cout<<"Choose a message"<<endl;
				cin>>choice1;
				if(choice1>user->getWall()->getMessages().size()){cout<<"Non-existing message, please try again!"<<endl;}
	 	}while(choice1>user->getWall()->getMessages().size());
			cout<<"Press 1 to like or 2 to remove like"<<endl;
			cin>>i;
			if(i==1){
				user->getWall()->getMessages()[choice1-1]->addLike(u);	
				seeWall(user);
			}
			else if(i==2){
				user->getWall()->getMessages()[choice1-1]->removeLike(u);	
				seeWall(user);
			}
		}
		else{
			cout<<"You are not friends with the user "<<user->getName()<<endl;
			system("PAUSE");
			seeWall(user);
		}
	}
}

void Menu::sendFriendRequest(){
	string n;
	int choice;
	do
	{
		system("CLS");
		cout<<"Press 1 to type the user's name"<<endl
			<<"Press 2 to go back"<<endl;
		cin>>choice;
		if(choice == 1){
			cout<<"Type the user's name"<<endl;
			read(&n);
			User *uto = Utilities::findUserFromName(n);
			if(uto!=NULL){
				uto->sendRequest(u);
				cout<<"Friend Request sent!"<<endl;
				system("PAUSE");
			}
			else{
				cout<<"User not found"<<endl;
				system("PAUSE");
			}
		}
		else if(choice!=1 && choice!=2)
		{
			cout<<"Wrong number, please try again"<<endl;
			system("PAUSE");
		}
	}while(choice!=1 && choice!=2);
	
}

void Menu::respondToRequests(){
	vector<FriendRequest*> fr = u->getFriendRequests();
	int j, choice;
	choice=1;
	do{
		do{
			system("CLS");
			cout<<"These are your friend request "<<endl;
			for(int i = 0; i < fr.size(); i++)
			{
				cout<< i+1 <<". " << fr[i]->toString() << endl;
			}
			cout<< "Type the number corresponding to the friend request you would like to accept or decline, or -1 to exit"<<endl;
			cin>>j;
		}while(j!=-1 && j>fr.size());
		if(j!=-1)
		{
			system("CLS");
			cout<<"These are your friend request "<<endl;
			for(int i = 0; i < fr.size(); i++)
			{
				cout<< i+1 <<". " << fr[i]->toString() << endl;
			}
			cout<<"Press 1 to Accept"<<endl
			<<"Press 2 to Decline"<<endl
			<<"Press 3 to go Back"<<endl;
			cin>>choice;
			if(choice == 1){
				u->respondRequest(fr[j-1], "accept");
			}	
			else if(choice == 2){
				u->respondRequest(fr[j-1], "decline");
			}
		}
	}while(choice!=1 && choice!=2 && choice!=3 && j!=-1);
}

void Menu::seeMyFriends(){
	system("CLS");
	int j;
	vector<User*> ufr = u->getFriends();
	cout<< "These are your friends" << endl;
	for(int i = 0; i < ufr.size(); i++){
		cout<< i+1 << ". " << ufr[i]->getName() << endl;
	}
	cout<<endl;
	cout<<"Press 0 to go back, or type a number to remove a friend"<<endl;
	cin>>j;
	if(j!=0){	
		u->removeFriend(ufr[j-1]);
		cout<<"User "<<ufr[j-1]->getName()<<" was removed from your friends"<<endl;
		system("PAUSE");
	}
	
}

void Menu::exit(){
	system("CLS");	
	ofstream cppfile;
	cppfile.open("save.txt");
	if(cppfile.is_open()){
		Network * i = Network::getNetwork();
		vector<User*> users = i->getUsers();
		for(int j=0; j<users.size(); j++){
			cppfile<<users[j]->getName()<<endl;
			cppfile<<"\t"<<users[j]->getEmail()<<endl;
			
			vector<User*> friends = i->getFriends(users[j]);
			for(int k=0; k<friends.size(); k++){
				cppfile<<"\t"<<friends[k]->getName()<<endl;	
			}
			
			cppfile<<"\tfr"<<endl;	
			vector<FriendRequest*> fr = users[j]->getFriendRequests();
			for(int z=0; z<fr.size(); z++){
				cppfile<<"\t"<<fr[z]->toString();
			}
			
			cppfile<<"\twall"<<endl;
			vector<Message*> messages = users[j]->getWall()->getMessages();
			for(int w=0; w<messages.size(); w++){
				cppfile<<"\t"<<messages[w]->getUser()->getName()<<"\t"<<messages[w]->getText()<<"\t"<<messages[w]->getTimestamp().toString();
				vector<User*> likes = messages[w]->getLikeArray();
				vector<Message*> replies = messages[w]->getReplies();
				for(int q=0; q<likes.size(); q++){
					cppfile<<"\t\t"<<likes[q]->getName()<<endl;
				}
				cppfile<<"\t\treplies"<<endl;
				for(int t=0; t<replies.size(); t++){
					cppfile<<"\t\t"<<replies[t]->getUser()->getName()<<"\t"<<replies[t]->getText()<<"\t"<<replies[t]->getTimestamp().toString();
				}
				
			}
		}
		cppfile.close();
	}
	else{
		cout<<"File could not open"<<endl;
		system("PAUSE");
	}
	
}

void Menu::read(string *s){
	getline(cin, *s);
	if(s->length()<2){
		getline(cin, *s);
	}
}
