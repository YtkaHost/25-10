#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

class Main {
private:
    std::map<std::string, double> GPA;
    std::map<std::string, double> attendance;
    std::map<std::string, double> rating;
    std::map<std::string, std::string> user;
    std::map<std::string, std::string> name;
    std::map<std::string, std::string> login;
    std::map<std::string, std::string> password;
    std::vector<int> assessments;

    void set_login(const std::string& new_login) {
        login["user"] = new_login;
    }
    void set_password(const std::string& new_password) {
        password["user"] = new_password;
    }
    void set_user() {
        user[login["user"]] = password["user"];
        set_all();
    }
    void set_name(const std::string& new_name) {
        name["user"] = new_name;
    }
    void set_assessments(int new_assessment) {
        assessments.push_back(new_assessment);
    }
    void set_attendance(double new_attendance) {
        attendance["user"] = new_attendance;
    }
    void set_all() {
        std::string set_string;
        double set_double;
        int set_user;

        std::cout << "Name: " << std::endl;
        std::cin >> set_string;
        set_name(set_string);

        std::cout << "Attendance: " << std::endl;
        std::cin >> set_double;
        set_attendance(set_double);

        do {
            std::cout << "Assessments: " << std::endl;
            std::cin >> set_double;
            set_assessments(static_cast<int>(set_double));
            std::cout << "It's all? \n1 = yes\n2 = no" << std::endl;
            std::cin >> set_user;
        } while (set_user != 1);
    }

    double get_GPA() {
        double total = 0.0;
        for (int assessment : assessments) {
            total += assessment;
        }
        if (assessments.empty()) {
            GPA["user"] = 0;
        } else {
            GPA["user"] = total / assessments.size();
        }
        return GPA["user"];
    }

    double get_rating() {
        rating["user"] = get_GPA() * attendance["user"];
        return rating["user"];
    }

    void save_data() {
        std::ofstream out_file("data.txt");
        if (out_file.is_open()) {
            out_file << login["user"] << " " << password["user"] << " " << name["user"] << " " << attendance["user"] << " ";
            for (int assessment : assessments) {
                out_file << assessment << " ";
            }
            out_file << std::endl;
            out_file.close();
        } else {
            std::cerr << "Unable to open file for writing!" << std::endl;
        }
    }

    void load_data() {
        std::ifstream in_file("data.txt");
        if (in_file.is_open()) {
            std::string temp_login, temp_password, temp_name;
            double temp_attendance;
            int temp_assessment;

            in_file >> temp_login >> temp_password >> temp_name >> temp_attendance;

            login["user"] = temp_login;
            password["user"] = temp_password;
            name["user"] = temp_name;
            attendance["user"] = temp_attendance;

            while (in_file >> temp_assessment) {
                assessments.push_back(temp_assessment);
            }

            in_file.close();
        } else {
            std::cerr << "Unable to open file for reading!" << std::endl;
        }
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
        save_data();
    }

    void open() {
        std::string temp_login;
        std::string temp_password;

        std::cout << "Write login: " << std::endl;
        std::cin >> temp_login;

        std::cout << "Write password: " << std::endl;
        std::cin >> temp_password;

        load_data();
        if (user[temp_login] == temp_password) {
            std::cout << "Login successful!" << std::endl;
        } else {
            std::cout << "Incorrect login or password!" << std::endl;
        }
    }

    void start() {
        int choice;

        std::cout << "Hello, new? \n1 - registration\n2 - entrance" << std::endl;
        std::cin >> choice;

        switch (choice) {
        case 1:
            registration();
            break;
        case 2:
            open();
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
            break;
        }

        int choise = 0;
        do {
            choise = 0;
            std::cout << "Continue? \n1 - registration new\n2 - entrance" << std::endl;
            std::cin >> choice;
        } while (choise != 1);
    }

    void show_main() {
        std::cout << "User: " << name["user"] << "\nGPA: " << get_GPA() << "\nRating: " << get_rating() << std::endl;
    }
};

int main() {
    Main app;
    app.start();
    return 0;
}
