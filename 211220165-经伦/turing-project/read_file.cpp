#include<iostream>
#include<fstream>
#include<algorithm>
#include<sstream>
#include<cmath>
#include"read_file.h"
using namespace std;
Simulator simulator;
V_state verbose;
vector<string> split(string a,char b)
{
    vector<string> vec;
    string cur;
    int i=0;
    for(;i<a.size();i++)
    {
        if(a[i]=='{')
        {
            break;
        }
    }
    for(int j=i+1;j<a.size();j++)
    {
        if(a[j]==b||a[j]=='}')
        {
            vec.push_back(cur);
            cout<<cur<<endl;
            cur.clear();
        }
        else
        {
            //cout<<a[j]<<endl;
            cur.push_back(a[j]);
        }
    }
    return vec;
}
bool init_Simulator(string tm,string input)
{
    ifstream ifs;
    ifs.open("palindrome_detector_2tapes.tm",ios::in);
    //cout<<0<<endl;
    if(!ifs.is_open())
    {
        cout<<"syntax error"<<endl;
        return 0;
    }
    //cout<<1<<endl;
    string buf;
    while(getline(ifs,buf))
    {
        //cout<<"buf"<<buf<<endl;
        if(buf.size()==0)
        {
            //cout<<"here"<<endl;
            continue;
        }
        if(buf[0]=='#')
        {
            switch (buf[1])
            {
                case 'Q':{
                simulator.Q=split(buf,',');
                break;
                }
                case 'S':
                {
                //cout<<"here"<<endl;
                vector<string> S=split(buf,',');
                for(auto it=S.begin();it!=S.end();it++)
                {
                    simulator.S.push_back((*it)[0]);
                }
                break;
                }
                case 'G':
                {
                vector<string> G=split(buf,',');
                for(auto it=G.begin();it!=G.end();it++)
                {
                    simulator.G.push_back((*it)[0]);
                }
                break;
                }
                case 'q':{
                buf.push_back('}');
                for(int i=0;;i++)
                {
                    if(buf[i]=='=')
                    {
                        buf.insert(buf.begin()+i+2,'{');
                        break;
                    }

                }
                vector<string> q_=split(buf,',');
                simulator.q0=q_[0];
                break;
                }
                case 'B':
                {
                buf.push_back('}');
                for(int i=0;;i++)
                {
                    if(buf[i]=='=')
                    {
                        buf.insert(buf.begin()+i+2,'{');
                        break;
                    }

                }
                vector<string> B_=split(buf,',');
                simulator.B=B_[0][0];
                break;
                }
                case 'F':
                {
                simulator.F=split(buf,',');
                break;
                }
                case 'N':
                {
                buf.push_back('}');
                for(int i=0;;i++)
                {
                    if(buf[i]=='=')
                    {
                        buf.insert(buf.begin()+2+i,'{');
                        //cout<<buf<<"buf"<<endl;
                        break;
                    }

                }
                vector<string> N_=split(buf,',');
                simulator.N=N_[0];
                break;
                }
            }
        }
        //cout<<2<<endl;
        stringstream ss(buf);
        string a;
        vector<string> delta_;
        while(ss>>a)
        {
            //cout<<a<<endl;
            delta_.push_back(a);
        }
        if(find(simulator.Q.begin(),simulator.Q.end(),delta_[0])!=simulator.Q.end())
        {
            if(delta_.size()==5)
            {
                State new_(delta_[0],delta_[1],delta_[2],delta_[3],delta_[4]);
                simulator.delta.push_back(new_);
            }
        }
    }
    int res=0;
    for(int i=0;i<simulator.N.size();i++)
    {
        res+=(simulator.N[i]-'0')*pow(10,simulator.N.size()-i-1);
    }
    //cout<<res<<"res"<<endl;
    verbose.ttape=new Tape[res];
    return 1;
}
bool mode(string tm,string input)
{
    if(init_Simulator(tm,input)==0)
    {
        return 0;
    }
    return 1;
}
bool v_model(string tm,string input)
{
    ;
}