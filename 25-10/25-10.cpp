#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <chrono>

class Main {
private:
    std::map <std::string, double> GPA;
    std::map <std::string, double> attendance;
    std::map <std::string, double> rating;
    std::map<std::string, std::string> user;
    std::map <std::string, std::string> name;
    std::map <std::string, std::string> login;
    std::map <std::string, std::string> password;
    std::vector<int> assessments;


    void set_login(std::string new_login) {
        login = new_login;
    }
    void set_password(std::string new_password) {
        password = new_password;
    }
    void set_user() {
        user[login] = password;
        set_all();
    }
    void set_name(std::string new_name) {
        name = new_name;
    }
    void set_assessments(int new_assessments) {
        assessments.push_back(new_assessments);
    }
    void set_attendance(double new_attendance) {
        attendance = new_attendance;
    }
    void set_all() {
        int set_user{};
        double set_double;
        std::string set_string;
        std::cout << "Name: " << std::endl;
        std::cin >> set_string;
        set_name(set_string);
        std::cout << "Attendance: " << std::endl;
        std::cin >> set_double;
        set_attendance(set_double);
        do {
            std::cout << "Assessments: " << std::endl;
            std::cin >> set_double;
            set_assessments(set_double);
            std::cout << "It`s all? \n1 = yes\n2 - no" << std::endl;
            std::cin >> set_user;
        } while (set_user != 1);
    }

    double get_GPA() {
        double temp;
        double temp_try;
        for (int i{}; i < assessments.size(); i++) {
            temp += assessments[i];
            temp_try++;
        }
        GPA = temp / temp_try;
        return GPA;
    }
    double get_rating() {
        rating = GPA * attendance;
        return rating;
    }
public:
    void registration() {
        std::string temp;
        std::cout << "Login: " << std::endl;
        std::cin >> temp;
        set_login(temp);
        std::cout << "Password: " << std::endl;
        std::cin >> temp;
        set_password(temp);
        set_user();
    }
    void open() {
        std::string temp_login;
        std::string temp_password;
        std::cout << "Write login: " << std::endl;
        std::cin >> temp_login;
        std::cout << "Write password: " << std::endl;
        std::cin >> temp_password;
        for (auto &pair:user) {
            if (pair.first == temp_login) {
                for (auto& pair : user) {
                    if (pair.second == temp_password)
                    {

                    }
                }
            }
            else {
                std::cout << "Incorrect login or password!"<<std::endl;
            }
        }
    }

    void start() {
        int choise;
        std::cout<<"Hello, new? \n1 - registration\n2 - entrance"<<std::endl;
        std::cin >> choise;
        switch (choise)
        {
            case 1:
                registration();
                break;
            case 2:
                open();
                break;
            default:
                break;
        }
    }

    void show_main() {

    }
};

int main()
{
    std::cout << "Hello World!\n";
}
