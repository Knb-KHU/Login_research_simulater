#include <iostream>
#include<string.h>
#include <unordered_map>
//잘 알지 못하는 std:undordered_map을 특성을 제대로 파악하지 않고 사용한 결과, 에러가 난무해서 벡터로 다시 만들기 위해 폐기함.
class Id{
private:
    int a;
    std::string id;
public:
    Id(std::string id, int a=0):id(id),a(a){}
    int Get() {return a;}
    std::string GetId(){return id;}
};

class PW{
private:
    int a;
    std::string pw;
public:
    PW(std::string pw, int a=0):pw(pw),a(a){}
    int Get() {return a;}
    std::string GetPW(){return pw;}
};


Acc Research(Acc acc, Id id, PW pw){
    int a,b;
    std::cout<<"자신의 이름에 대해 어떻게 생각하시나요?(1-5)";
    std::cin>>a;
    while (typeid(a)!=typeid(int)){
        std::cout<<"\n올바르지 않은 입력값입니다.\n";
        std::cout<<"자신의 이름에 대해 어떻게 생각하시나요?(1-5)";
        std::cin>>a;
    }
    Id id(id.GetId(),a);
    std::cout<<"자신의 비밀번호에 대해 어떻게 생각하시나요?(1-5)";
    std::cin>>b;
    while (typeid(b)!=typeid(int)){
        std::cout<<"\n올바르지 않은 입력값입니다.\n";
        std::cout<<"자신의 비밀번호에 대해 어떻게 생각하시나요?(1-5)";
        std::cin>>b;
    }
    PW pw(pw.GetPW(),b);
    Acc acc(id,pw);
    return acc;
}


class Acc{
private:
    Id id;
    PW pw;
    public:static std::unordered_map<std::string,std::string,int,int> userList;
public:
    Acc(Id id,PW pw):id(id),pw(pw){
        userList[id.GetId()]=pw.GetPW(),id.Get(),pw.Get();
    }
    Acc(std::string a, std::string b):id(Id(a)),pw(PW(b)){
        Acc(Id(a),PW(b));
    }
    static void Login(std::string a, std::string b){
        if (userList[a]!=b){
            std::cout<<"error! 잘못된 계정입니다."<<std::endl;
        }
        else{
            Research(Acc(Id(a),PW(b)),Id(a),PW(b));
        }
    }
    public:std::unordered_map<std::string,std::string,int,int>& GetList(){
        return userList;
    }
};

void System(){
    std::cout<<"안녕하세요. 설문조사 프로그램에 오신 것을 환영합니다."<<std::endl;
    std::string a;
    std::string i,p;
    while(0){
        std::cout<<"설문조사를 위해 가입을 진행하시려면 ''가입''을 기존에 가입하신 적이 있으신 고객님이시라면 ''로그인''을 입려해주세요."<<std::endl;
        std::cin>>a;
        if (a=="가입"){
            std::cout<<"가입에 사용하실 아이디를 입력해주세요:";
            std::cin>>i;
            std::cout<<"가입에 사용하실 비밀번호를 입력해주세요:";
            std::cin>>p;
            Acc(i,p);
            Acc::userList[i]=p,0,0;
        }
        if (a=="로그인"){
            std::cout<<"아이디를 입력해주세요:";
            std::cin>>i;
            std::cout<<"비밀번호를 입력해주세요:";
            std::cin>>p;
            Acc::Login(i,p);
        }
        if (a=="결과 확인"){
            int c,d;
            for (const auto& user : Acc::userList) {
                std::cout << "ID: " << user.first << ", Password: " << user.second << ", namesatisfaction: " << ", Passwordsatifion: " << user.second << std::endl;
    }
        } 

    }
}