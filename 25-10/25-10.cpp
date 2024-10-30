#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Main {
private:
  std::map<std::string,
           std::pair<std::string, std::pair<double, std::vector<int>>>>
      users;

  void set_user(std::string login, std::string password, std::string name, double attendance,  std::vector<int> assessments) {
    users[login] = {password, {attendance, assessments}};
  }

  double get_GPA(std::vector<int> assessments) {
    double total = 0.0;
    for (int assessment : assessments) {
      total += assessment;
    }
    return assessments.empty() ? 0 : total / assessments.size();
  }

  double get_rating(std::string login) {
    const auto &user_data = users[login];
    double GPA = get_GPA(user_data.second.second);
    return GPA * user_data.second.first;
  }

  void save_data() {
    std::ofstream out_file("data.txt",
                           std::ios::app);
    if (out_file.is_open()) {
      for (auto user : users) {
        out_file << user.first << " "                
                 << user.second.first << " "      
                 << user.second.second.first << " ";
        for (int assessment : user.second.second.second) {
          out_file << assessment << " ";
        }
        out_file << std::endl;
      }
      out_file.close();
    } else {
      std::cerr << "Unable to open file for writing!" << std::endl;
    }
  }

  void load_data() {
    std::ifstream in_file("data.txt");
    if (in_file.is_open()) {
      std::string temp_login, temp_password;
      double temp_attendance;
      int temp_assessment;

      while (in_file >> temp_login >> temp_password >> temp_attendance) {
        std::vector<int> assessments;
        while (in_file.peek() != '\n' && in_file >> temp_assessment) {
          assessments.push_back(temp_assessment);
        }
        set_user(temp_login, temp_password, "", temp_attendance, assessments);
      }

      in_file.close();
    } else {
      std::cerr << "Unable to open file for reading!" << std::endl;
    }
  }

public:
  void registration() {
    std::string temp_login, temp_password, temp_name;
    double temp_attendance;
    std::vector<int> assessments;

    std::cout << "Login: " << std::endl;
    std::cin >> temp_login;

    if (users.find(temp_login) != users.end()) {
      std::cout << "User already exists!" << std::endl;
      return;
    }

    std::cout << "Password: " << std::endl;
    std::cin >> temp_password;

    std::cout << "Name: " << std::endl;
    std::cin >> temp_name;

    std::cout << "Attendance: " << std::endl;
    std::cin >> temp_attendance;

    int choice;
    do {
      int assessment;
      std::cout << "Assessments: " << std::endl;
      std::cin >> assessment;
      assessments.push_back(assessment);
      std::cout << "Add more assessments? \n1 = yes\n2 = no" << std::endl;
      std::cin >> choice;
    } while (choice == 1);

    set_user(temp_login, temp_password, temp_name, temp_attendance,
             assessments);
    save_data();
  }

  void open() {
    std::string temp_login, temp_password;

    std::cout << "Write login: " << std::endl;
    std::cin >> temp_login;

    std::cout << "Write password: " << std::endl;
    std::cin >> temp_password;

    if (users.find(temp_login) != users.end() &&
        users[temp_login].first == temp_password) {
      std::cout << "Login successful!" << std::endl;
      show_main(temp_login);
    } else {
      std::cout << "Incorrect login or password!" << std::endl;
    }
  }

  void start() {
    load_data();
    int choice;

    do {
      std::cout << "Hello, new? \n1 - registration\n2 - entrance\n3 - exit"<< std::endl;
      std::cin >> choice;
      switch (choice) {
      case 1:
        registration();
        break;
      case 2:
        open();
        break;
      case 3:
        break;
      default:
        std::cout << "Invalid choice!" << std::endl;
        break;
      }
    } while (choice != 3);
  }

  void show_main(const std::string &login) {
    const auto &user_data = users[login];
    std::cout << "User: " << login << "\nGPA: " << get_GPA(user_data.second.second) << "\nRating: " << get_rating(login) << std::endl;
  }
};

int main() {
  Main app;
  app.start();
  return 0;
}
