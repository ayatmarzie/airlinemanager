#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

struct AirPlain
{


public:
    int AAET;
    int FlightNumber;
    int FlightDuration;
    int Fuel;
    int Landing;
    bool SpecialPassenger;
    bool islanded;

    AirPlain(int a1=0, int a2=0, int a3=0, int a4=0, int a5=0 , bool a6=0):AAET(a1),FlightNumber(a2),FlightDuration(a3), Fuel(a4), Landing(a5), SpecialPassenger(a6){islanded=0;}


    void print(int &buffer){
        if(FlightNumber!=buffer){
            cout<<"airplain number:"<<FlightNumber<<endl;
            buffer=FlightNumber;
        }
    }

};

bool uniquecom(AirPlain &struct1,AirPlain &struct2)
{
    return(struct1.FlightNumber==struct2.FlightNumber);
}






bool compareAAET (const AirPlain& struct1, const AirPlain& struct2)
{
    if(struct1.AAET==struct2.AAET){
        return (struct1.SpecialPassenger<struct2.SpecialPassenger);
    }
    return (struct1.AAET < struct2.AAET);
}

bool compareFlightDuration (const AirPlain& struct1, const AirPlain& struct2)
{
    return (struct1.FlightDuration < struct2.FlightDuration);
}


bool compareFuel1 (const AirPlain& struct1, const AirPlain& struct2)
{
    if(struct1.AAET==struct2.AAET&&struct1.SpecialPassenger==struct2.SpecialPassenger)
        return (struct1.Fuel < struct2.Fuel);
    else if (struct1.AAET==struct2.AAET&&struct1.Fuel==struct2.Fuel) {
        return (struct1.SpecialPassenger<struct2.SpecialPassenger);
    }
    else {
        return (struct1.AAET<struct2.AAET);
    }
}
bool compareduration1 (const AirPlain& struct1, const AirPlain& struct2)
{
    if(struct1.AAET==struct2.AAET&&struct1.SpecialPassenger==struct2.SpecialPassenger)
        return (struct1.FlightDuration > struct2.FlightDuration);
    else if (struct1.AAET==struct2.AAET&&struct1.FlightDuration==struct2.FlightDuration) {
        return (struct1.SpecialPassenger<struct2.SpecialPassenger);
    }
    else {
        return (struct1.AAET<struct2.AAET);
    }
}
bool comparefuel2(const AirPlain& struct1, const AirPlain& struct2)
{
    if(struct1.Fuel==struct2.Fuel)
        return (struct1.SpecialPassenger<struct2.SpecialPassenger);
    return(struct1.Fuel<struct2.Fuel);
}
bool compareduration2(const AirPlain& struct1, const AirPlain& struct2)
{
    if(struct1.FlightDuration==struct2.FlightDuration)
        return (struct1.SpecialPassenger<struct2.SpecialPassenger);
    return(struct1.FlightDuration>struct2.FlightDuration);
}

vector<AirPlain> INPUT()
{
    vector<AirPlain> input;

    int a1,a2,a3,a4,a5,a6;
    cout<<"please enter airplane's information in the exact order of:\n AAET,Flight number, flight duraration, fuel remaining, Landing duration, Has special passenger.\n press any letter to exit."<<endl;
    while(cin>>a1&&cin>>a2 &&cin>>a3&& cin>>a4&& cin>>a5&& cin>>a6){
        AirPlain forpush(a1,a2,a3,a4,a5,a6);
        input.push_back(forpush);


    }
    return input;

}


void land(AirPlain &A,int &currenttime,int &buffer ){
    A.print(buffer);
    A.islanded=1;
    currenttime+=A.Landing;
    A.Landing=0;
}
void lessland(AirPlain &m,int &currenttime,int &buffer,int till )
{
    m.Landing-=till;
    currenttime+=till;
    //if (till>0)
    m.print(buffer);
}

void preemptivefuelrecursive(unsigned j, vector <AirPlain> &input, int &current_time,int &buffer)
{
    unsigned c=j-1;
    auto begin=input.begin()+c;
    for(;j<input.size();j++)
    {
        auto member=input.begin()+j;
        if(member->islanded)
        {
            input.erase(member);
            j--;
        }
        else if(   begin->SpecialPassenger)
        {
            land(*begin,current_time,buffer);
            input.erase(input.begin()+c);                                                             //omadi uncommentesh koni ba c ba ham bokon
            break;                                                                                  //critical
        }
        else if(current_time > member->AAET  &&  begin->Fuel > member->Fuel)

        {
            int tillnextpass=current_time- member->AAET;
            lessland(*member,current_time,buffer,tillnextpass);
            preemptivefuelrecursive(j+1,input,current_time,buffer);
        }
        else if(current_time < member->AAET)
        {
            auto endsort=input.begin()+j;
            sort(input.begin(),endsort,comparefuel2);
            while(current_time < member->AAET )
            {
                if(input.begin()->islanded)
                    input.erase(input.begin());
                else if(current_time+input.begin()->Landing < endsort->AAET)
                {
                    land(*input.begin(),current_time,buffer);
                    input.erase(input.begin());
                }
                else
                {
                    int tillnextpass=current_time- endsort->AAET;
                    lessland(*input.begin(),current_time,buffer,tillnextpass);

                }
                j--;

            }
        }
    }
}

void preemptivedurationrecursive(unsigned j, vector <AirPlain> &input, int &current_time,int &buffer)
{
    unsigned c=j-1;
    auto begin=input.begin()+c;
    for(;j<input.size();j++)
    {
        auto member=input.begin()+j;
        if(member->islanded)
        {
            input.erase(member);
            j--;
        }
        else if( begin->SpecialPassenger)
        {
            land(*begin,current_time,buffer);
            input.erase(input.begin()+c);                                                             //omadi uncommentesh koni ba c ba ham bokon
            break;                                                                                  //critical
        }
        else if(current_time > member->AAET  &&  begin->FlightDuration < member->FlightDuration)

        {
            int tillnextpass=current_time- member->AAET;
            lessland(*member,current_time,buffer,tillnextpass);
            preemptivedurationrecursive(j+1,input,current_time,buffer);
        }
        else if(current_time < member->AAET)
        {
            auto endsort=input.begin()+j;
            sort(input.begin(),endsort,compareduration2);

            while(current_time < member->AAET )
            {
                if(input.begin()->islanded)
                    input.erase(input.begin());
                else if(current_time+input.begin()->Landing < endsort->AAET)
                {
                    land(*input.begin(),current_time,buffer);
                    input.erase(input.begin());
                }
                else
                {
                    int tillnextpass=current_time- endsort->AAET;
                    lessland(*input.begin(),current_time,buffer,tillnextpass);
                    j--;
                }

            }
        }
    }
}
void FCFS(vector<AirPlain> &input){
     sort(input.begin() , input.end() , compareAAET);
    int currenttime=input.begin()->AAET;
    int buffer=-1;
    map<int,AirPlain> check;
    queue<AirPlain> qu_of_numbers;
    for(auto i:input){

        check[i.FlightNumber]=i;
    }
    for (int i=0;i<input.size();i++)
    {
        auto member = input.begin()+i;
        if (member->islanded)
        {
            input.erase(member);
            i--;
            continue;
        }
        if(member->AAET<=currenttime)
        {
            if(!member->islanded)
            {
                if (member->SpecialPassenger)
                {
                    land(*member,currenttime,buffer);
                    check.erase(member->FlightNumber);
                }
                else
                {
                    qu_of_numbers.push(*member);
                    int nexthaspass;
                    for (auto j=i+1;j<input.size();j++)
                    {
                        if((input.begin()+j)->SpecialPassenger){
                            nexthaspass=j;
                            break;
                        }
                    }
                    auto tillnext=(input.begin()+nexthaspass)->AAET-currenttime;
                    if(tillnext>0)
                    {
                        if(qu_of_numbers.front().Landing<=tillnext)
                        {
                            land(qu_of_numbers.front(),currenttime,buffer);
                            check.erase(qu_of_numbers.front().FlightNumber);
                            qu_of_numbers.pop();


                        }
                        else
                        {

                            lessland(qu_of_numbers.front(),currenttime,buffer,tillnext);
                            check[qu_of_numbers.front().FlightNumber]=qu_of_numbers.front();


                            for (auto j=i+1;j<nexthaspass;j++)
                            {
                                qu_of_numbers.push(*(input.begin()+i));
                            }
                        }
                    }
                    else
                    {

                        i=nexthaspass;
                        i--;

                    }

                }

            }
        }
        else {
            auto tillnext=member->AAET-currenttime;
            while(currenttime<member->AAET)
            {
                if(qu_of_numbers.front().Landing<=tillnext)
                {
                    land(qu_of_numbers.front(),currenttime,buffer);
                    check.erase(qu_of_numbers.front().FlightNumber);
                    qu_of_numbers.pop();

                }
                else {
                    lessland(qu_of_numbers.front(),currenttime,buffer,tillnext);
                    check[qu_of_numbers.front().FlightNumber]=qu_of_numbers.front();
                }
                if(!member->SpecialPassenger)
                    qu_of_numbers.push(*member);
                else {
                    land(*member,currenttime,buffer);
                }

            }
        }
    }
    while(!qu_of_numbers.empty())
    {
        if(check.find( qu_of_numbers.front().FlightNumber)!=check.end())
        {
            land(qu_of_numbers.front(),currenttime,buffer);
            check.erase(qu_of_numbers.front().FlightNumber);
            qu_of_numbers.pop();
        }
        else{
            while(check.find( qu_of_numbers.front().FlightNumber)==check.end())
                qu_of_numbers.pop();
        }
    }





}




void LFDFnonemptive(vector<AirPlain> &input)
{
    sort(input.begin(),input.end(),compareduration1);
    int current_time=input.begin()->AAET;
    int buffer=-1;
    map<int,AirPlain>check;
    int nextpass=-1;
    int tillnextpass=-1;
    vector<AirPlain> vec;
    for(auto i:input){

        check[i.FlightNumber]=i;
    }
    for (int i=0;i<input.size();i++)
    {
        auto member=input.begin()+i;
        if(check.find(member->FlightNumber)!=check.end())
        {
            if(current_time>=member->AAET)
            {
                for(auto k=i;(input.begin()+k)->AAET<=current_time;k++)
                vec.push_back(*(input.begin()+k));
                auto end_unique=unique(vec.begin(),vec.end(),uniquecom);
                vec.erase(end_unique,vec.end());
                sort(vec.begin(),vec.end(),comparefuel2);
                for(int j=0;j<vec.size();j++)
                {
                    if(check.find((vec.begin()+j)->FlightNumber)==check.end())
                    {
                        vec.erase(vec.begin()+j);
                        j--;
                    }
                    else if((vec.begin()+j)->SpecialPassenger)
                    {
                        nextpass=j;
                        break;
                    }
                }
                if(nextpass!=-1)
                {
                    if((vec.begin()+nextpass)->FlightNumber==member->FlightNumber)
                    {
                        land(*vec.begin(),current_time,buffer);
                        check.erase(vec.begin()->FlightNumber);
                        vec.erase(vec.begin());
                    }
                    else {
                        tillnextpass=(vec.begin()+nextpass)->AAET-current_time;
                        if(tillnextpass)
                            lessland(*vec.begin(),current_time,buffer,tillnextpass);

                    }
                }
                else {
                    land(*vec.begin(),current_time,buffer);
                    check.erase(vec.begin()->FlightNumber);
                    vec.erase(vec.begin());
                }
            }
            else
            {
                sort(vec.begin(),vec.end(),compareduration2);
                tillnextpass=member->AAET-current_time;
                while(current_time<member->AAET)
                {
                    if((vec.begin())->Landing<=tillnextpass)
                    {
                        land(*vec.begin(),current_time,buffer);
                        check.erase(vec.begin()->FlightNumber);
                        vec.erase(vec.begin());

                    }
                    else {
                        lessland(*vec.begin(),current_time,buffer,tillnextpass);
                        check[vec.begin()->FlightNumber]=*vec.begin();
                    }
                    if(!member->SpecialPassenger)
                        vec.push_back(*member);
                    else
                    {
                        land(*member,current_time,buffer);

                    }

                }
            }
        }

    }
    while (!vec.empty())
    {
        if(check.find(vec.begin()->FlightNumber)!=check.end())
        {
            land(*vec.begin(),current_time,buffer);
            check.erase(vec.begin()->FlightNumber);
            vec.erase(vec.begin());
        }
        else{
            while(check.find(vec.begin()->FlightNumber)==check.end())
                vec.erase(vec.begin());
        }
    }

}

void LFDFpre(vector<AirPlain> &input)
{
    sort(input.begin(),input.end(),compareduration1);
    int current_time=input.begin()->AAET;
    int buffer=-1;
    for(int i=0;i<input.size();i++){
        auto member = input.begin()+i;
        if (member->islanded)
        { input.erase(member);
            i--;
        }

        else{
            preemptivedurationrecursive(i+1,input,current_time,buffer);
        }
    }
    sort(input.begin(),input.end(),compareduration2);
    for (auto i:input)
    {
        land(i,current_time,buffer);
    }

}
void LRFFpreemptive(vector<AirPlain> &input)
{
    sort(input.begin(),input.end(),compareFuel1);
    int current_time=input.begin()->AAET;
    int buffer=-1;
    for(int i=0;i<input.size();i++){
        auto member = input.begin()+i;
        if (member->islanded)
        { input.erase(member);
            i--;
        }

        else{
            preemptivefuelrecursive(i+1,input,current_time,buffer);
        }
    }
    sort(input.begin(),input.end(),comparefuel2);
    for (auto i:input)
    {
        land(i,current_time,buffer);
    }

}
void LRFFnoneemptive(vector<AirPlain> &input)
{
    sort(input.begin(),input.end(),compareFuel1);
    int current_time=input.begin()->AAET;
    int buffer=-1;
    map<int,AirPlain>check;
    int nextpass=-1;
    int tillnextpass=-1;
    vector<AirPlain> vec;
    for(auto i:input){

        check[i.FlightNumber]=i;
    }
    for (int i=0;i<input.size();i++)
    {
        auto member=input.begin()+i;
        if(check.find(member->FlightNumber)!=check.end())
        {
            if(current_time>=member->AAET)
            {
                for(auto k=i;(input.begin()+k)->AAET<=current_time;k++)
                vec.push_back(*(input.begin()+k));
                auto end_unique=unique(vec.begin(),vec.end(),uniquecom);
                vec.erase(end_unique,vec.end());
                sort(vec.begin(),vec.end(),comparefuel2);
                for(int j=0;j<vec.size();j++)
                {
                    if(check.find((vec.begin()+j)->FlightNumber)==check.end())
                    {
                        vec.erase(vec.begin()+j);
                        j--;
                    }
                    else if((vec.begin()+j)->SpecialPassenger)
                    {
                        nextpass=j;
                        break;
                    }
                }
                if(nextpass!=-1)
                {
                    if((vec.begin()+nextpass)->FlightNumber==member->FlightNumber)
                    {
                        land(*vec.begin(),current_time,buffer);
                        check.erase(vec.begin()->FlightNumber);
                        vec.erase(vec.begin());
                    }
                    else {
                        tillnextpass=(vec.begin()+nextpass)->AAET-current_time;
                        if(tillnextpass)
                            lessland(*vec.begin(),current_time,buffer,tillnextpass);

                    }
                }
                else {
                    land(*vec.begin(),current_time,buffer);
                    check.erase(vec.begin()->FlightNumber);
                    vec.erase(vec.begin());
                }
            }
            else
            {
                sort(vec.begin(),vec.end(),comparefuel2);
                tillnextpass=member->AAET-current_time;
                while(current_time<member->AAET)
                {
                    if((vec.begin())->Landing<=tillnextpass)
                    {
                        land(*vec.begin(),current_time,buffer);
                        check.erase(vec.begin()->FlightNumber);
                        vec.erase(vec.begin());

                    }
                    else {
                        lessland(*vec.begin(),current_time,buffer,tillnextpass);
                        check[vec.begin()->FlightNumber]=*vec.begin();
                    }
                    if(!member->SpecialPassenger)
                        vec.push_back(*member);
                    else
                    {
                        land(*member,current_time,buffer);

                    }

                }
            }
        }

    }
    while (!vec.empty())
    {
        if(check.find(vec.begin()->FlightNumber)!=check.end())
        {
            land(*vec.begin(),current_time,buffer);
            check.erase(vec.begin()->FlightNumber);
            vec.erase(vec.begin());
        }
        else{
            while(check.find(vec.begin()->FlightNumber)==check.end())
                vec.erase(vec.begin());
        }
    }

}

int main()
{
    int i;
    vector< AirPlain> a;
    cout<<"please enter a flight policy\n 1-FCFS \n 2-pre-emptive LRFF\n 3-non-emptive LRFF \n 4- pre-emptive LFDF \n 5-non-emptive LFDF"<<endl;
    cin>>i;
  a=INPUT();




    switch(i){
    case 1:
        FCFS(a);
        break;
    case 2:
        LRFFpreemptive(a);
        break;
    case 3:
        LRFFnoneemptive(a);
        break;
    case 4:
        LFDFpre(a);
        break;
    case 5:
        LFDFnonemptive(a);
        break;
//    default:
//        cout<<"policy not found"<<endl;

    }

}
