#include<iostream>
#include<fstream>
#include<algorithm>
#include<sstream>
#include<cmath>
#include"read_file.h"
using namespace std;
Simulator simulator;
V_state verbose;
void space(int a)
{
    for(int i=0;i<a;i++)
    {
        cout<<" ";
    }
}
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
            //cout<<cur<<endl;
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
                int i=0;
                for(;;i++)
                {
                    if(buf[i]=='=')
                    {
                        //buf.insert(buf.begin()+i+2,'{');
                        break;
                    }
                }
                i+=2;
                string q_;
                for(int j=i;j<buf.size();j++)
                {
                    if(buf[j]==' ')
                    {
                        break;
                    }
                    q_.push_back(buf[j]);
                }
                simulator.q0=q_;
                break;
                }
                case 'B':
                {
                int i=0;
                for(;;i++)
                {
                    if(buf[i]=='=')
                    {
                        //buf.insert(buf.begin()+i+2,'{');
                        break;
                    }
                }
                i+=2;
                string q_;
                for(int j=i;j<buf.size();j++)
                {
                    if(buf[j]==' ')
                    {
                        break;
                    }
                    q_.push_back(buf[j]);
                }
                simulator.B=q_[0];
                break;
                }
                case 'F':
                {
                simulator.F=split(buf,',');
                break;
                }
                case 'N':
                {
                int i=0;
                for(;;i++)
                {
                    if(buf[i]=='=')
                    {
                        //buf.insert(buf.begin()+i+2,'{');
                        break;
                    }
                }
                i+=2;
                string q_;
                for(int j=i;j<buf.size();j++)
                {
                    if(buf[j]==' ')
                    {
                        break;
                    }
                    q_.push_back(buf[j]);
                }
                simulator.N=q_;
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
            
            State new_(delta_[0],delta_[1],delta_[2],delta_[3],delta_[4]);
            simulator.delta.push_back(new_);
            //cout<<delta_[0]<<delta_[1]<<delta_[2]<<delta_[3]<<delta_[4]<<endl;
        }
    }
    int res=0;
    for(int i=0;i<simulator.N.size();i++)
    {
        res+=(simulator.N[i]-'0')*pow(10,simulator.N.size()-i-1);
    }
    verbose.N=res;
    //cout<<res<<"res"<<endl;
    verbose.ttape=new Tape[res];
    verbose.state=simulator.q0;
    if(find(simulator.F.begin(),simulator.F.end(),verbose.state)==simulator.F.end())
    {
        verbose.acc=0;
    }
    else
    {
        verbose.acc=1;
    }
    for(int i=0;i<res;i++)
    {
        if(i==0)
        {
            verbose.ttape[i].tape=input;
            verbose.ttape[i].index.start=0;
            if(input.size()!=0)
            {
                verbose.ttape[i].index.final=input.size()-1;
            }
            else
            {
                verbose.ttape[i].tape="_";
                verbose.ttape[i].index.final=0;

            }
            verbose.ttape[i].head=0;
        }
        else
        {
            verbose.ttape[i].tape="_";
            verbose.ttape[i].index.start=0;
            verbose.ttape[i].index.final=0;
            verbose.ttape[i].head=0;
        }
    }

    return 1;
}
bool mode(string tm,string input)
{
    if(init_Simulator(tm,input)==0)
    {
        return 0;
    }
    for(auto it=input.begin();it!=input.end();it++)
    {
        if(find(simulator.S.begin(),simulator.S.end(),(*it))==simulator.S.end())
        {
            cout<<"illegal input string"<<endl;
            return 0;
        }
    }
    int flag=0;
    while(1)
    {   
        if(find(simulator.F.begin(),simulator.F.end(),verbose.state)!=simulator.F.end())
        {
            flag=1;
        }
        int i=0;
        //cout<<simulator.delta.size()<<endl;
        for(;i<simulator.delta.size();i++)
        {
            //cout<<verbose.state<<endl;
            if(simulator.delta[i].cur_state==verbose.state)
            {
                int j=0;
                for(;j<verbose.N;j++)
                {
                    //cout<<verbose.ttape[j].tape[verbose.ttape[j].head-verbose.ttape[j].index.start]<<" "<<simulator.delta[i].cur_char[j]<<endl;
                    if(verbose.ttape[j].tape[verbose.ttape[j].head-verbose.ttape[j].index.start]!=simulator.delta[i].cur_char[j]&&simulator.delta[i].cur_char[j]!='*')
                    {
                        //cout<<"here2"<<endl;
                        //cout<<verbose.ttape[j].tape[verbose.ttape[j].head]<<"equals"<<simulator.delta[i].cur_char[j]<<endl;
                        goto A;
                    }
                }
                if(j==verbose.N)
                {
                    goto B;
                }
            }
            A://change a delta
            ;
        }
        if(i==simulator.delta.size())
        {
            //cout<<"halt"<<endl;
            break;
        }
        //cout<<i<<"io"<<endl;
        B://find this delta
        //cout<<simulator.delta[i].cur_state<<" "<<simulator.delta[i].cur_char<<" "<<verbose.ttape[0].tape<<" "<<verbose.ttape[1].tape<<endl;
        verbose.step++;
        verbose.state=simulator.delta[i].new_state;
        if(find(simulator.F.begin(),simulator.F.end(),verbose.state)==simulator.F.end())
        {
            verbose.acc=0;
        }
        else
        {
            verbose.acc=1;
        }
        for(int p=0;p<verbose.N;p++)
        {    
            if(simulator.delta[i].cur_char[p]=='*')
            {
                if(simulator.delta[i].new_char[p]=='*')
                {
                    ;
                }
                else
                {
                    verbose.ttape[p].tape[verbose.ttape[p].head-verbose.ttape[p].index.start]=simulator.delta[i].new_char[p];
                }
            }
            else
            {
                verbose.ttape[p].tape[verbose.ttape[p].head-verbose.ttape[p].index.start]=simulator.delta[i].new_char[p];
            }
        }
        for(int p=0;p<verbose.N;p++)
        {
            if(simulator.delta[i].direct[p]=='l')
            {
                verbose.ttape[p].head--;
                if(verbose.ttape[p].head<verbose.ttape[p].index.start)
                {
                    verbose.ttape[p].index.start=verbose.ttape[p].head;
                    verbose.ttape[p].tape='_'+verbose.ttape[p].tape;
                }
                // else if(verbose.ttape[p].head+1==verbose.ttape[p].index.final&&verbose.ttape[p].tape[verbose.ttape[p].index.final]=='_')
                // {
                //     verbose.ttape[p].index.final--;
                //     verbose.ttape[p].tape.erase(verbose.ttape[p].tape.begin()+verbose.ttape[p].tape.size()-1);
                // }
            }
            else if(simulator.delta[i].direct[p]=='r')
            {
                verbose.ttape[p].head++;
                if(verbose.ttape[p].head>verbose.ttape[p].index.final)
                {
                    verbose.ttape[p].index.final=verbose.ttape[p].head;
                    verbose.ttape[p].tape=verbose.ttape[p].tape+'_';
                }
                // else if(verbose.ttape[p].head-1==verbose.ttape[p].index.start&&verbose.ttape[p].tape[verbose.ttape[p].index.start]=='_')
                // {
                //     verbose.ttape[p].index.start++;
                //     verbose.ttape[p].tape.erase(verbose.ttape[p].tape.begin());
                // }
            }
            else
            {
                ;
            }
            if(verbose.ttape[p].tape[0]=='_'&&verbose.ttape[p].head!=verbose.ttape[p].index.start)
            {
                verbose.ttape[p].index.start++;
                verbose.ttape[p].tape.erase(verbose.ttape[p].tape.begin());
            }
            else if(verbose.ttape[p].tape[verbose.ttape[p].index.final-verbose.ttape[p].index.start]=='_'&&verbose.ttape[p].head!=verbose.ttape[p].index.final)
            {
                verbose.ttape[p].index.final--;
                verbose.ttape[p].tape.erase(verbose.ttape[p].tape.begin()+verbose.ttape[p].tape.size()-1);
            }
        }
    }
    if(flag==0)
    {
        cout<<"(UNACCEPTED) "<<verbose.ttape[0].tape<<endl;
    }
    else
    {
        cout<<"(ACCEPTED) "<<verbose.ttape[0].tape<<endl;
    }
    return 1;
}
bool v_model(string tm,string input)
{
    if(init_Simulator(tm,input)==0)
    {
        return 0;
    }
    for(auto it=input.begin();it!=input.end();it++)
    {
        if(find(simulator.S.begin(),simulator.S.end(),(*it))==simulator.S.end())
        {
            cout<<"Input: "<<input<<endl;
            cout<<"==================== ERR ===================="<<endl;
            cout<<"error: Symbol "<<(*it)<<" in input is not defined in the set of input symbols"<<endl;
            cout<<"Input: "<<input<<endl;
            space(7+it-input.begin());
            cout<<"^"<<endl;
            cout<<"==================== END ===================="<<endl;
            return 0;
        }
    }
    cout<<"Input: "<<input<<endl;
    cout<<"==================== RUN ===================="<<endl;
    int flag=0;
    int sum=5+(verbose.N<10)+2;
    while(1)
    {   
        cout<<"Step";
        space(sum-4);
        cout<<": "<<verbose.step<<endl;

        cout<<"State";
        space(sum-5);
        cout<<": "<<verbose.state<<endl;
        
        cout<<"Acc";
        space(sum-3);
        if(verbose.acc==0)
        {
            cout<<": No"<<endl;
        }
        else
        {
            cout<<": Yes"<<endl;
        }
            
        for(int i=0;i<verbose.N;i++)
        {
            cout<<"Index"<<i;
            if(i<10)
            {
                space(sum-6);
            }
            else
            {
                space(sum-7);
            }
            cout<<": ";
            for(int j=verbose.ttape[i].index.start;j<=verbose.ttape[i].index.final;j++)
            {
                cout<<abs(j)<<" ";
            }
            cout<<endl;

            cout<<"Tape"<<i;
            if(i<10)
            {
                space(sum-5);
            }
            else
            {
                space(sum-6);
            }
            cout<<": ";
            for(int j=verbose.ttape[i].index.start;j<=verbose.ttape[i].index.final;j++)
            {
                cout<<verbose.ttape[i].tape[j-verbose.ttape[i].index.start];
                if(j<10)
                {
                    space(1);
                }
                else
                {
                    space(2);
                }
            }
            cout<<endl;

            cout<<"Head"<<i;
            if(i<10)
            {
                space(sum-5);
            }
            else
            {
                space(sum-6);
            }
            cout<<": ";
            for(int j=verbose.ttape[i].index.start;j<=verbose.ttape[i].index.final;j++)
            {
                if(j==verbose.ttape[i].head)
                {
                    cout<<"^";
                    break;
                }
                if(j<10)
                {
                    space(2);
                }
                else
                {
                    space(3);
                }
            }
            cout<<endl;
        }
        cout<<"---------------------------------------------"<<endl;
        
        if(find(simulator.F.begin(),simulator.F.end(),verbose.state)!=simulator.F.end())
        {
            flag=1;
        }
        int i=0;
        //cout<<simulator.delta.size()<<endl;
        for(;i<simulator.delta.size();i++)
        {
            //cout<<verbose.state<<endl;
            if(simulator.delta[i].cur_state==verbose.state)
            {
                int j=0;
                for(;j<verbose.N;j++)
                {
                    //cout<<verbose.ttape[j].tape[verbose.ttape[j].head-verbose.ttape[j].index.start]<<" "<<simulator.delta[i].cur_char[j]<<endl;
                    if(verbose.ttape[j].tape[verbose.ttape[j].head-verbose.ttape[j].index.start]!=simulator.delta[i].cur_char[j]&&simulator.delta[i].cur_char[j]!='*')
                    {
                        //cout<<"here2"<<endl;
                        //cout<<verbose.ttape[j].tape[verbose.ttape[j].head]<<"equals"<<simulator.delta[i].cur_char[j]<<endl;
                        goto A;
                    }
                }
                if(j==verbose.N)
                {
                    goto B;
                }
            }
            A://change a delta
            ;
        }
        if(i==simulator.delta.size())
        {
            //cout<<"halt"<<endl;
            break;
        }
        //cout<<i<<"io"<<endl;
        B://find this delta
        //cout<<simulator.delta[i].cur_state<<" "<<simulator.delta[i].cur_char<<" "<<verbose.ttape[0].tape<<" "<<verbose.ttape[1].tape<<endl;
        verbose.step++;
        verbose.state=simulator.delta[i].new_state;
        if(find(simulator.F.begin(),simulator.F.end(),verbose.state)==simulator.F.end())
        {
            verbose.acc=0;
        }
        else
        {
            verbose.acc=1;
        }
        for(int p=0;p<verbose.N;p++)
        {    
            if(simulator.delta[i].cur_char[p]=='*')
            {
                if(simulator.delta[i].new_char[p]=='*')
                {
                    ;
                }
                else
                {
                    verbose.ttape[p].tape[verbose.ttape[p].head-verbose.ttape[p].index.start]=simulator.delta[i].new_char[p];
                }
            }
            else
            {
                verbose.ttape[p].tape[verbose.ttape[p].head-verbose.ttape[p].index.start]=simulator.delta[i].new_char[p];
            }
        }
        for(int p=0;p<verbose.N;p++)
        {
            if(simulator.delta[i].direct[p]=='l')
            {
                verbose.ttape[p].head--;
                if(verbose.ttape[p].head<verbose.ttape[p].index.start)
                {
                    verbose.ttape[p].index.start=verbose.ttape[p].head;
                    verbose.ttape[p].tape='_'+verbose.ttape[p].tape;
                }
                // else if(verbose.ttape[p].head+1==verbose.ttape[p].index.final&&verbose.ttape[p].tape[verbose.ttape[p].index.final]=='_')
                // {
                //     verbose.ttape[p].index.final--;
                //     verbose.ttape[p].tape.erase(verbose.ttape[p].tape.begin()+verbose.ttape[p].tape.size()-1);
                // }
            }
            else if(simulator.delta[i].direct[p]=='r')
            {
                verbose.ttape[p].head++;
                if(verbose.ttape[p].head>verbose.ttape[p].index.final)
                {
                    verbose.ttape[p].index.final=verbose.ttape[p].head;
                    verbose.ttape[p].tape=verbose.ttape[p].tape+'_';
                }
                // else if(verbose.ttape[p].head-1==verbose.ttape[p].index.start&&verbose.ttape[p].tape[verbose.ttape[p].index.start]=='_')
                // {
                //     verbose.ttape[p].index.start++;
                //     verbose.ttape[p].tape.erase(verbose.ttape[p].tape.begin());
                // }
            }
            else
            {
                ;
            }
            if(verbose.ttape[p].tape[0]=='_'&&verbose.ttape[p].head!=verbose.ttape[p].index.start)
            {
                verbose.ttape[p].index.start++;
                verbose.ttape[p].tape.erase(verbose.ttape[p].tape.begin());
            }
            else if(verbose.ttape[p].tape[verbose.ttape[p].index.final-verbose.ttape[p].index.start]=='_'&&verbose.ttape[p].head!=verbose.ttape[p].index.final)
            {
                verbose.ttape[p].index.final--;
                verbose.ttape[p].tape.erase(verbose.ttape[p].tape.begin()+verbose.ttape[p].tape.size()-1);
            }
        }
    }
    if(flag==0)
    {
        cout<<"UNACCEPTED"<<endl;
        cout<<"Result: "<<verbose.ttape[0].tape<<endl;
    }
    else
    {
        cout<<"ACCEPTED"<<endl;
        cout<<"Result: "<<verbose.ttape[0].tape<<endl;
    }
    cout<<"==================== END ===================="<<endl;
    return 1;
}