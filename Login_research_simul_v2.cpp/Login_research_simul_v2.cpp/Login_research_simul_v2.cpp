#include <iostream>
#include<string>
#include <vector>
#include<algorithm>
//v1 std:undordered_map을 사용해보려다가 특성을 제대로 파악하지 않고 사용한 결과, 에러가 난무해서 벡터로 다시 만들기 위해 폐기함.
//v2 만드는 김에 아예 설문 개수를 늘려도 받을 수 있도록 아예 설문의 답안을 따로 받는 형식으로 변경.

class Id {
private:
    std::string id;
public:
    Id(std::string id) :id(id) {}
    std::string GetId() { return id; }
    bool operator== (const Id& other)const {
        return id == other.id;
    }

};

class PW {
private:
    std::string pw;
public:
    PW(std::string pw) :pw(pw) {}
    std::string GetPW() { return pw; }
    bool operator== (const PW& other) { return pw == other.pw; }

};


//question
std::vector<std::string> question_list = { "안녕하세요?","노래불러!" };

void add(std::string a) {
    question_list.push_back(a);
}
void del(std::string a) {

    question_list.erase(std::find(question_list.begin(), question_list.end(), a));
}

class Acc {
private:
    Id id;
    PW pw;
    std::vector<int> survey_score;
public:
    static std::vector<Acc> userList;
    Acc(Id id, PW pw, std::vector<int> ss = {}) :id(id), pw(pw), survey_score(ss) {
        userList.push_back(*this);
    }
    Acc(std::string a, std::string b) :id(Id(a)), pw(PW(b)),survey_score() {
        userList.push_back(*this);
    }

    bool operator== (const Acc& other) {
        return (id == other.id) && (pw == other.pw);
    }

    std::vector<int> Research() {
        int b;
        survey_score.clear();
        for (int a = 0; a < question_list.size(); a++) {
            std::cout << "\n\n" << question_list[a] << "(1-5):";
            std::cin >> b;
            while (typeid(b) != typeid(int)) {
                std::cout << "\n올바르지 않은 입력값입니다.";
                std::cout << "\n" << question_list[a] << "(1-5):";
                std::cin >> b;
            }
            survey_score.push_back(b);
        }
        Printscore();
        return survey_score;

    }

    static void Login(std::string& a, std::string& b) {
        int c=0;
        if (a == "admin" && b == "admin") {
            while (a != "종료") {
                std::cout << "관리자님, 어서오세요. 1.질문추가 2.질문제거 3.결과확인4.종료" << std::endl;
                std::cin >> a;
                if (a == "질문추가") {
                    std::string a="";
                    std::cout << "추가하실 질문을 작성해주십시요.";
                    std::cin >> a;
                    add(a);

                }
                if (a == "질문제거") {
                    std::string a="";
                    std::cout << "제거하실 질문을 작성해주십시요.";
                    std::cin >> a;
                    del(a);

                }
                if (a == "결과확인") {
                    int c, d;
                    for (Acc user : Acc::userList) {
                        user.Results();
                    }
                    for (int i = 0; i < question_list.size(); i++) {
                        std::cout << question_list[i] << ":";
                        int p = 0;
                        for (Acc user : Acc::userList) {
                            p += user.Scoreturn()[i];
                        }
                        std::cout << p / Acc::userList.size() << std::endl;
                    }
                }
                else { std::cout << "올바르지 않은 코드입니다." << std::endl; }

            }
        }
        for (Acc &user : Acc::userList) {
            if ((user.id == a) && (user.pw == b)) {
                std::cout << "로그인에 성공하셨습니다.\n";
                user.Research();
                c = 1;
            }
        }
        if (c == 0){ std::cout << "error! 잘못된 계정입니다." << std::endl; }
    }
public:std::vector<Acc>& GetList() {
    return userList;
    }
    void Printscore() {
        for (int i = 0; i < survey_score.size();i++) {
            std::cout << survey_score[i]<<",";
        }
    }
    void Results() {
        std::cout << "ID: " << id.GetId() << ", Password: " <<pw.GetPW()<< ", results ";
        Printscore();
        std::cout<<std::endl;
    }
      std::vector<int> Scoreturn() {
          return survey_score;
      }
};
//userList
std::vector<Acc> Acc::userList;
void System() {

    std::cout << "안녕하세요. 설문조사 프로그램에 오신 것을 환영합니다." << std::endl;
    std::string a="";
    std::string i, p;
    while (a != "종료") {
        std::cout << "설문조사를 위해 가입을 진행하시려면 ''가입''을 기존에 가입하신 적이 있으신 고객님이시라면 ''로그인''을 입려해주세요." << std::endl;
        std::cin >> a;
        if (a == "가입") {
            std::cout << "가입에 사용하실 아이디를 입력해주세요:";
            std::cin >> i;
            std::cout << "가입에 사용하실 비밀번호를 입력해주세요:";
            std::cin >> p;
            Acc(i, p);

        }
        if (a == "로그인") {
            std::cout << "아이디를 입력해주세요:";
            std::cin >> i;
            std::cout << "비밀번호를 입력해주세요:";
            std::cin >> p;
            Acc::Login(i, p);
        }
        if (a == "결과") {
            int c, d;
            for (Acc user : Acc::userList) {
                user.Results();
            }
            for (int i = 0; i < question_list.size(); i++) {
                std::cout << question_list[i] << ":";
                int p=0;
                for (Acc user : Acc::userList) {
                    p += user.Scoreturn()[i];
                }
                std::cout << p / Acc::userList.size() << std::endl;
            }
        }
        else { std::cout << "올바르지 않은 코드입니다." << std::endl; }

    }
}

int main() {
    System();
}