#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

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

    void register_new_user(){
        fstream fname;
        fname.open("users.txt", ios::app);
        if(fname.is_open()){
            cout<<"ENTER USERNAME: ";
            cin>>username;
            cout<<"ENTER PASSWORD: ";
            cin>>password;
            cout<<"ENTER NAME: ";
            cin.ignore();
            getline(cin, name);
            fname<<endl<<username<<","<<password<<","<<name<<","<<0;
            fname.close();
        }
    }

    static void leaderboard(){
        fstream fname;
        
        vector <student> user_objects;
        fname.open("users.txt", ios::in);
        if(fname.is_open()){
            string userline;
            while(getline(fname, userline)){
                vector <string> data;
                //cout<<userline<<endl;
                student obj;
                stringstream X(userline);
                string output;
                while(getline(X, output, ',')){
                    data.push_back(output);
                }
                obj.username = data[0];
                //cout<<obj.username;
                obj.password = data[1];
                obj.setdata(data[2], data[3]);
                user_objects.push_back(obj);
            }

            fname.close();
        }

        for(int i = 1; i < user_objects.size(); i++){
            for(int j = 0; j <= user_objects.size()-i-1; j++){
                if(user_objects[j].score < user_objects[j+1].score){
                    student temp = user_objects[j];
                    user_objects[j] = user_objects[j+1];
                    user_objects[j+1] = temp;
                }
            }
        }

        for(int i = 0; i<user_objects.size(); i++){
            cout<<user_objects[i].name<<endl<<user_objects[i].username<<endl<<user_objects[i].score<<endl<<endl;
        }
    }

    void updatefile(){
        fstream fname;
        string filename1 = "users.txt";
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

    void setalldata(string uname, string pass, string n, string sc){
        username = uname;
        password = pass;
        name = n;
        stringstream ss;
        ss << sc;
        ss >> score;
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

    void displayalldata(){
        cout<<username<<"\t\t"<<name<<"\t\t"<<score<<endl;
    }

	bool login(){
        string uname;
        fstream fname;
        int flag = 0;
        fname.open("users.txt", ios::in);
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
    
    void get_new_question(){
        cout<<"ENTER QUESTION: ";
        cin.ignore();
        getline(cin, ques);
        cout<<"ENTER OPTION 1: ";
        getline(cin, option1);
        cout<<"ENTER OPTION 2: ";
        getline(cin, option2);
        cout<<"ENTER OPTION 3: ";
        getline(cin, option3);
        cout<<"ENTER OPTION 4: ";
        getline(cin, option4);
        cout<<"ENTER ANSWER ";
        cin>>ans;
    }

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
        //SHUFFLE THE QUESTIONS VECTOR HERE
        random_shuffle(allquestions.begin(), allquestions.end());       //random_shuffle is defined in the algorithm library
        for(int i = 0; i<allquestions.size(); i++){
            allquestions[i].display();
            allquestions[i].getanswer();
        }
        student::display_current_score();
    }

    void input_new_questions(){
        fstream fname;
        fname.open("questions.txt", ios::app);
        if(fname.is_open()){
            fname<<endl<<endl<<ques<<endl<<"a) "<<option1<<endl<<"b) "<<option2<<endl<<"c) "<<option3<<endl<<"d) "<<option4<<endl<<ans;
            fname.close();
        }
        
    }
   
};

class admin{
    string username;
	string password;
	string name;

    public:

    void setdata(string n){
	    name = n;
	}

    void display(){
	    cout<<endl<<"USERNAME: "<<username<<endl<<"NAME: "<<name<<endl;
	}

    bool login(){
        string uname;
        fstream fname;
        int flag = 0;
        fname.open("admins.txt", ios::in);
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
                        setdata(data[0]);
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

    void addquestions(){ 
        int questions_choice;
        do{
            question question_obj;
            question_obj.get_new_question();
            question_obj.input_new_questions();
            cout<<"Do you want to add more questions? 1 for yes: ";
            cin>>questions_choice;
        }while(questions_choice == 1);

    }

    void viewscores(){
        fstream fname;
        
        vector <student> user_objects;
        fname.open("users.txt", ios::in);
        if(fname.is_open()){
            string userline;
            while(getline(fname, userline)){
                vector <string> data;
                //cout<<userline<<endl;
                student obj;
                stringstream X(userline);
                string output;
                while(getline(X, output, ',')){
                    data.push_back(output);
                }
                obj.setalldata(data[0], data[1], data[2], data[3]);
                user_objects.push_back(obj);
            }

            fname.close();
        }

        for(int i = 0; i<user_objects.size(); i++){
           user_objects[i].displayalldata();
        }
    }
};

int question::total_questions;
int student::current_score;

void student_functions(){
    student obj1;
    int choice;
    cout<<endl<<"1. Register\n2. Login\nEnter Your Choice: ";
    cin>>choice;
    if(choice == 1){
        obj1.register_new_user();
    }else if(choice == 2){
        if(obj1.login() == true){
        cout<<"USER LOGGED IN"<<endl;
        int choice;
        cout<<"1. TAKE QUIZ\n2. VIEW SCORE\n3. VIEW STUDENT DETAILS\n4. VIEW LEADERBOARD\nYOUR CHOICE: ";
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
                break;
            
            case 4:
                student::leaderboard();
                break;
            
            default:
                cout<<endl<<"Incorrect Option"<<endl;
        }
        
        
        }
    }
    

}


void admin_functions(){
    admin obj2;
    if(obj2.login()==true){
        cout<<"ADMIN LOGGED IN "<<endl;
        int choice;
        cout<<"1. ADD QUESTIONS\n2. VIEW SCORES\n3. VIEW LEADERBOARD\nYOUR CHOICE: ";
        cin>>choice;
        switch(choice){
            case 1:
                obj2.addquestions();
                break;
            case 2:
                obj2.viewscores();
                break;
            case 3:
                student::leaderboard();
                break;
            default:
                cout<<endl<<"Incorrect Option"<<endl;                    
        }
        //obj2.display();
        //obj2.addquestions();
        //student::leaderboard();
        //add functions to remove questions and remove a students data
    }
    
}


int main()
{

	//student obj1;
    admin obj2;
    int login_choice;
    cout<<"LOGIN AS:\n1. Student\n2. Admin\nYour Choice: ";
    cin>>login_choice;
    if(login_choice == 1){
        student_functions();
        /*
        if(obj1.login() == true){
            cout<<"USER LOGGED IN"<<endl;
            int choice;
            cout<<"1. TAKE QUIZ\n2. VIEW SCORE\n3. VIEW STUDENT DETAILS\n4. VIEW LEADERBOARD\nYOUR CHOICE: ";
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
                    break;
                
                case 4:
                    student::leaderboard();
                    break;
                
                default:
                    cout<<endl<<"Incorrect Option"<<endl;
            }
            
            
        }*/
    }else{
        admin_functions();
        /*
        if(obj2.login()==true){
            cout<<"ADMIN LOGGED IN "<<endl;
            int choice;
            cout<<"1. ADD QUESTIONS\n2. VIEW SCORES\n3. VIEW LEADERBOARD\nYOUR CHOICE: ";
            cin>>choice;
            switch(choice){
                case 1:
                    obj2.addquestions();
                    break;

                case 2:
                    obj2.viewscores();
                    break;

                case 3:
                    student::leaderboard();
                    break;

                default:
                    cout<<endl<<"Incorrect Option"<<endl;                    
            }

            //obj2.display();
            //obj2.addquestions();
            //student::leaderboard();
        }*/
    }
	return 0;
}
