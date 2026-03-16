#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class question{
    string ques;
    string option1;
    string option2;
    string option3;
    string option4;
    char ans;
    int score;
    static int total_questions;

    public:
    

    void display(){
        cout<<ques<<endl<<option1<<endl<<option2<<endl<<option3<<endl<<option4<<endl<<ans<<endl;
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
            //getline(fname, line);       //skip the first line, we dont use the variable line anywhere
            fname.ignore(1000, '\n');
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
                fname.ignore(1000, '\n');
                //getline(fname, line);       //skip the line after reading question, we arent using the variable line anywhere
                
            }
            cout<<quesdata.size()<<endl;
            fname.close();
            return quesdata;
        }

    }

   
};



int question::total_questions;


int main(){
    int tot = question::gettotal();
    cout<<tot<<endl;
    vector <question> allquestions = question::getquestions();
    cout<<allquestions.size()<<endl;
    random_shuffle(allquestions.begin(), allquestions.end());
    for(int i = 0; i<allquestions.size(); i++){
        allquestions[i].display();
    }

    return 0;
}