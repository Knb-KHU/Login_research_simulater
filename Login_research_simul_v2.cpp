#include <iostream>
#include<string>
#include <vector>
#include<algorithm>
//v1 std:undordered_map을 사용해보려다가 특성을 제대로 파악하지 않고 사용한 결과, 에러가 난무해서 벡터로 다시 만들기 위해 폐기함.
//v2 만드는 김에 아예 설문 개수를 늘려도 받을 수 있도록 아예 설문의 답안을 따로 받는 형식으로 변경.

class Id{
private:
    std::string id;
public:
    Id(std::string id):id(id){}
    std::string GetId(){return id;}
    bool operator== (const Id& other)const{
        return id==other.id;
    }
    
};

class PW{
private:
    std::string pw;
public:
    PW(std::string pw):pw(pw){}
    std::string GetPW(){return pw;}
    bool operator== (const PW& other){return pw==other.pw;}
    
};


//question
std::vector<std::string> question_list={"안녕하세요?","노래불러!"};

void add(std::string a){
    question_list.push_back(a);
}
void del(std::string a){
        
     question_list.erase(std::find(question_list.begin(),question_list.end(),a));
}

class Acc{
private:
    Id id;
    PW pw;
    std::vector<int> survey_score;
public:
    static std::vector<Acc> userList;
    Acc(Id id,PW pw):id(id),pw(pw){
        userList.push_back(*this);
    }
    Acc(std::string a, std::string b):id(Id(a)),pw(PW(b)){
        userList.push_back(*this);
    }
    
    bool operator== (const Acc& other){
        return (id==other.id)&&(pw==other.pw);
    }

    void Research(){
        int b;

        for (int a=0;a<question_list.size();a++){
            std::cout<<"\n\n"<<question_list[a]<<"(1-5):";
            std::cin>>b;
            while (typeid(b)!=typeid(int)){
                std::cout<<"\n올바르지 않은 입력값입니다.";
                std::cout<<"\n"<<question_list[a]<<"(1-5):";
                std::cin>>b;
            }
            survey_score.push_back(b);
        }
    }

    static void Login(std::string a, std::string b){
        if (std::find(userList.begin(),userList.end(),Acc(a,b))==userList.end()){
            std::cout<<"error! 잘못된 계정입니다."<<std::endl;
        }
        else{
            Acc(Id(a),PW(b)).Research();
        }
    }
    public:std::vector<Acc>& GetList(){
        return userList;
    }
    std::vector<int> scoreturn(){
        return survey_score;
    }

};
//userList
std::vector<Acc> Acc::userList;
void System(){

    std::cout<<"안녕하세요. 설문조사 프로그램에 오신 것을 환영합니다."<<std::endl;
    std::string a;
    std::string i,p;
    while(a!="종료"){
        std::cout<<"설문조사를 위해 가입을 진행하시려면 ''가입''을 기존에 가입하신 적이 있으신 고객님이시라면 ''로그인''을 입려해주세요."<<std::endl;
        std::cin>>a;
        if (a=="가입"){
            std::cout<<"가입에 사용하실 아이디를 입력해주세요:";
            std::cin>>i;
            std::cout<<"가입에 사용하실 비밀번호를 입력해주세요:";
            std::cin>>p;
            Acc(i,p);

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
            for (Acc user : Acc::userList) {
                std::cout << "ID: " << user.scoreturn()[0]<< ", Password: "  << ", namesatisfaction: " << ", Passwordsatifion: " << std::endl;
            }
        } 
        else{std::cout<<"올바르지 않은 코드입니다."<<std::endl;}

    }
}

int main(){
    System();
}
