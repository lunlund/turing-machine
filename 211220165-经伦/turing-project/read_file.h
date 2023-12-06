#include<iostream>
#include<string>
#include<vector>
using namespace std;
struct State
{
    string cur_state;
    string cur_char;
    string new_char;
    string direct;
    string new_state;
    State(string a1,string a2,string a3,string a4,string a5)
    {
        cur_state=a1;
        cur_char=a2;
        new_char=a3;
        direct=a4;
        new_state=a5;
    }
};
class Simulator
{
    public:
    Simulator()
    {
        B='_';
    }
    vector<string> Q;
    vector<char> S;
    vector<char> G;
    string q0;
    char B;
    vector<string> F;
    string N;
    vector<State> delta;
};
struct Double
{
    int start;
    int final;
};
struct Tape
{
    Double index;
    string tape;
    int head;
};
class V_state
{
    public:
    // V_state(int N)
    // {
    //     ttape=new Tape[N];
    //     step=0;
    //     state="";
    //     acc=0;
    // }
    int step;
    string state;
    bool acc;
    Tape *ttape;
};
extern Simulator simulator;
extern V_state verbose;
bool mode(string tm,string input);
bool v_model(string tm,string input);