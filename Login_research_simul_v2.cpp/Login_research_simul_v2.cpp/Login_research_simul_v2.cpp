#include <iostream>
#include<string>
#include <vector>
#include<algorithm>
//v1 std:undordered_map�� ����غ����ٰ� Ư���� ����� �ľ����� �ʰ� ����� ���, ������ �����ؼ� ���ͷ� �ٽ� ����� ���� �����.
//v2 ����� �迡 �ƿ� ���� ������ �÷��� ���� �� �ֵ��� �ƿ� ������ ����� ���� �޴� �������� ����.

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
std::vector<std::string> question_list = { "�ȳ��ϼ���?","�뷡�ҷ�!" };

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
                std::cout << "\n�ùٸ��� ���� �Է°��Դϴ�.";
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
            while (a != "����") {
                std::cout << "�����ڴ�, �������. 1.�����߰� 2.�������� 3.���Ȯ��4.����" << std::endl;
                std::cin >> a;
                if (a == "�����߰�") {
                    std::string a="";
                    std::cout << "�߰��Ͻ� ������ �ۼ����ֽʽÿ�.";
                    std::cin >> a;
                    add(a);

                }
                if (a == "��������") {
                    std::string a="";
                    std::cout << "�����Ͻ� ������ �ۼ����ֽʽÿ�.";
                    std::cin >> a;
                    del(a);

                }
                if (a == "���Ȯ��") {
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
                else { std::cout << "�ùٸ��� ���� �ڵ��Դϴ�." << std::endl; }

            }
        }
        for (Acc &user : Acc::userList) {
            if ((user.id == a) && (user.pw == b)) {
                std::cout << "�α��ο� �����ϼ̽��ϴ�.\n";
                user.Research();
                c = 1;
            }
        }
        if (c == 0){ std::cout << "error! �߸��� �����Դϴ�." << std::endl; }
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

    std::cout << "�ȳ��ϼ���. �������� ���α׷��� ���� ���� ȯ���մϴ�." << std::endl;
    std::string a="";
    std::string i, p;
    while (a != "����") {
        std::cout << "�������縦 ���� ������ �����Ͻ÷��� ''����''�� ������ �����Ͻ� ���� ������ �����̽ö�� ''�α���''�� �Է����ּ���." << std::endl;
        std::cin >> a;
        if (a == "����") {
            std::cout << "���Կ� ����Ͻ� ���̵� �Է����ּ���:";
            std::cin >> i;
            std::cout << "���Կ� ����Ͻ� ��й�ȣ�� �Է����ּ���:";
            std::cin >> p;
            Acc(i, p);

        }
        if (a == "�α���") {
            std::cout << "���̵� �Է����ּ���:";
            std::cin >> i;
            std::cout << "��й�ȣ�� �Է����ּ���:";
            std::cin >> p;
            Acc::Login(i, p);
        }
        if (a == "���") {
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
        else { std::cout << "�ùٸ��� ���� �ڵ��Դϴ�." << std::endl; }

    }
}

int main() {
    System();
}