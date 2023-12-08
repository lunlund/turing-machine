#include <iostream>
#include <string>
#include "read_file.h"
using namespace std;
int main(int argc, char* argv[]){
    bool help=0;
    bool verbose=0;
    string tm;
    string input;
    if(argc==1||argc>5)
    {
        cout<<"syntax error"<<endl;
        exit(FORMAT_ERROR);
        return 1;
    }
    if((string)argv[0]!=(string)"./turing")
    {   
        cout<<"syntax error"<<endl;
        exit(FORMAT_ERROR);
        return 1;
    }
    if(argc==2)
    {
        if((string)argv[1]==(string)"-h"||(string)argv[1]==(string)"--help")
        {
            cout<<"usage: turing [-v|--verbose] [-h|--help] <tm> <input>"<<endl;
        }
        else
        {
            cout<<"syntax error"<<endl;
            exit(FORMAT_ERROR);
        }
        return 1;
    }
    else if(argc==3)
    {
        if(argv[1]=="-h"||argv[1]=="--help")
        {
            cout<<"usage: turing [-v|--verbose] [-h|--help] <tm> <input>"<<endl;
            return 1;
        }
        tm=argv[1];
        input=argv[2];
        //tm input function
        mode(tm,input);
        //cout<<"tm inout"<<endl;
    }
    else if(argc==4)
    {
        if((string)argv[1]==(string)"-v"||(string)argv[1]==(string)"--verbose")
        {
            //v mode
            tm=argv[2];
            input=argv[3];
            v_model(tm,input);
            //cout<<"v mode"<<endl;
        }
        else if((string)argv[1]==(string)"-h"||(string)argv[1]==(string)"--help")
        {
            cout<<"usage: turing [-v|--verbose] [-h|--help] <tm> <input>"<<endl;
            return 1;
        }
        else
        {
            cout<<"syntax error"<<endl;
            exit(FORMAT_ERROR);
            return 1;
        }
    }
    else
    {
        if((string)argv[1]!=(string)"-v"&&(string)argv[1]!=(string)"--verbose")
        {
            cout<<"syntax error"<<endl;
            exit(FORMAT_ERROR);
            return 1;
        }
        if((string)argv[2]!=(string)"-h"&&(string)argv[2]!=(string)"--help")
        {
            cout<<"syntax error"<<endl;
            exit(FORMAT_ERROR);
            return 1;
        }
        cout<<"usage: turing [-v|--verbose] [-h|--help] <tm> <input>"<<endl;
        return 1;
    }


}