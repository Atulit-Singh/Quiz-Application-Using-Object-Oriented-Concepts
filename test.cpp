#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class student{
	string username;
	string password;
	string name;
	string score;
	
	int fields = 4;

	public:
	
	void setdata(string n, string sc){
		name = n;
		score = sc;
	}
	void display(){
		cout<<endl<<username<<endl<<password<<endl<<name<<endl<<score<<endl;
	}

	bool login(string userline, string uname, int *flag){
		stringstream X(userline);
		//cout<<"INSIDE FUNCTION"<<endl;
		getline(X, username, ',');
		string pass;
		string output;
		vector <string> data;
		if(username == uname){
			*flag = 1;
			cin>>pass;
			getline(X, password, ',');
			if(pass == password){
				cout<<"LOGGED IN"<<endl;
				while(getline(X, output, ',')){
					//cout<<output<<endl;
					data.push_back(output);
				}

				setdata(data[0], data[1]);
				
				return true;
			}else{
				cout<<"INCORRECT PASSWORD"<<endl;
			}
		}
		

	}
};

int main()
{

	student obj1;
	fstream fname;
	int flag = 0;
	fname.open("a.txt", ios::in);
	if(fname.is_open()){
		string line, user;
		cout<<"FILE OPENED"<<endl;
		cin>>user;
		while(getline(fname, line)){
			//cout << line<<endl;
			if(obj1.login(line, user, &flag)){
				cout<<"USER LOGGED IN"<<endl;
				obj1.display();
			}
			
		}
		if (flag == 0){
			cout<<"USER NOT FOUND"<<endl;
		}
	}

	return 0;
}
