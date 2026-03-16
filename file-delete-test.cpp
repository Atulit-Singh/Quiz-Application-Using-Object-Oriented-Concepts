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
	
	int fields = 4;

    protected:
    int score;

	public:

	static int current_score;

    void updatefile(){
        fstream fname;
        string filename1 = "a.txt";
        string filename2 = "temp.txt";
        fname.open(filename1, ios::in);
        if(fname.is_open()){
            fstream temp;
            temp.open(filename2, ios::out);
            if(temp.is_open()){
                string userline;
                while(getline(fname, userline)){
                    stringstream X(userline);
                    string uname;
                    getline(X, uname, ',');
                    if(username == uname){
                        temp<<username<<","<<password<<","<<name<<","<<student::current_score<<endl;
                    }else{
                        temp<<userline<<endl;
                    }
                }
                temp.close();
            }
            fname.close();

        }
        remove(filename1.c_str());
        rename(filename2.c_str(), filename1.c_str());



    }

    void updatescore(){
        display_past_score();
        if(student::current_score > score){
            score = student::current_score;
            updatefile();
        }
        display_past_score();
    }

	void setdata(string n, string sc){
        stringstream ss;
        ss << sc;
        ss >> score;
		name = n;
	}

    void display_past_score(){
        cout<<"YOUR SCORE IS: "<<score<<endl;
    }

    static void display_current_score(){
        cout<<"CURRENT SCORE IS: "<<current_score<<endl;
    }

	void display(){
		cout<<endl<<"USERNAME: "<<username<<endl<<"NAME: "<<name<<endl;
	}

	bool login(){
        string uname;
        fstream fname;
        int flag = 0;
        fname.open("a.txt", ios::in);
        if(fname.is_open()){
            string userline;
            cout<<"FILE OPENED"<<endl;
            cout<<"ENTER USERNAME: ";
            cin>>uname;
            while(getline(fname, userline)){
                stringstream X(userline);
                getline(X, username, ',');
                if(username == uname){
                    flag = 1;
                    string pass;
                    cout<<"ENTER PASSWORD: ";
                    cin>>pass;
                    getline(X, password, ',');
                    if(pass == password){
                        string output;
		                vector <string> data;
                        cout<<"LOGGED IN"<<endl;
                        while(getline(X, output, ',')){
                            data.push_back(output);
                        }
                        setdata(data[0], data[1]);
                        return true;
                    }
                    else{
                        cout<<"INCORRECT PASSWORD"<<endl;
                        return false;
                    }
                }
            }
            if(flag == 0){
                cout<<"USER NOT FOUND"<<endl;
                return false;
            }
            fname.close();
        }

		

	}

    
};


class question : private student{
    string ques;
    string option1;
    string option2;
    string option3;
    string option4;
    char ans;
    char input_ans;
    static int total_questions;
    

    public:
    
    

    void display(){
        cout<<ques<<endl<<option1<<endl<<option2<<endl<<option3<<endl<<option4<<endl;
    }


    static int gettotal(){
        fstream fname;
        fname.open("questions.txt", ios::in);
        if(fname.is_open()){
            string temp;
            getline(fname, temp);
            //cout<<temp;
            stringstream ss;
            ss << temp;
            ss >> total_questions;
            return(total_questions);
            fname.close();
        }
    }


    static vector<question> getquestions(){
        fstream fname;
        fname.open("questions.txt", ios::in);
        if(fname.is_open()){
            question obj;
            string line;
            int count = 0;
            getline(fname, line);       //skip the first line, we dont use the variable line anywhere
            //fname.ignore(1000, '\n');
            vector <question> quesdata;
            while(getline(fname, obj.ques)){
                string temp_ans;
                getline(fname, obj.option1);
                getline(fname, obj.option2);
                getline(fname, obj.option3);
                getline(fname, obj.option4);
                getline(fname, temp_ans);
                obj.ans = temp_ans[0];
                quesdata.push_back(obj);
                getline(fname, line);       //skip the line after reading question, we arent using the variable line anywhere
                
            }
            fname.close();
            return quesdata;

        }

    }


    void getanswer(){
        cout<<endl<<"YOUR ANSWER: ";
        cin>>input_ans;
        if(input_ans == ans){
            //cout<<"CORRECT ANSWER"<<endl;
            student::current_score += 1;
            //cout<<current_score<<endl;
        }
        
    }


    static void takequiz(){
        int tot = question::gettotal();
        vector <question> allquestions = question::getquestions();
        for(int i = 0; i<allquestions.size(); i++){
            allquestions[i].display();
            allquestions[i].getanswer();
        }
        student::display_current_score();
    }

    
   
};

int question::total_questions;
int student::current_score;

int main()
{

	student obj1;
	if(obj1.login() == true){
		cout<<"USER LOGGED IN"<<endl;
        int choice;
        cout<<"1. TAKE QUIZ\n2. VIEW SCORE\n3. VIEW STUDENT DETAILS\nYOUR CHOICE: ";
        cin>>choice;
        switch(choice){
            case 1:
                question::takequiz();
                obj1.updatescore();
                break;

            case 2:
                obj1.display_past_score();
                break;

            case 3:
                obj1.display();
        }
        
		
	}
	return 0;
}
