#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Main {
private:
  struct User {
    std::string password;
    double attendance;
    std::vector<int> assessments;
    std::string review;
  };

  std::map<std::string, User> users;

  void set_user(std::string login, std::string password, double attendance, std::vector<int> assessments, std::string review) {
    users[login] = {password, attendance, assessments, review};
  }

  double get_GPA(std::vector<int> assessments) {
    double total = 0;
    for (int assessment : assessments) {
      total += assessment;
    }
    if (assessments.empty()) {
      return 0;
    }
    return total / assessments.size();
  }

  double get_rating(std::string login) {
    const auto &user_data = users[login];
    double GPA = get_GPA(user_data.assessments);
    return GPA * user_data.attendance;
  }

  void save_data() {
    std::ofstream out_file("data.txt", std::ios::trunc);
    if (out_file.is_open()) {
      for (const auto &user : users) {
        out_file << user.first << " "
                 << user.second.password << " "
                 << user.second.attendance << " ";
        for (int assessment : user.second.assessments) {
          out_file << assessment << " ";
        }
        out_file << user.second.review << std::endl;
      }
      out_file.close();
    } else {
      std::cout << "Unable to open file for writing!" << std::endl;
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
        std::string review;
        in_file.ignore();
        std::getline(in_file, review);
        set_user(temp_login, temp_password, temp_attendance, assessments, review);
      }

      in_file.close();
    } else {
      std::cout << "Unable to open file for reading!" << std::endl;
    }
  }

public:
  void registration() {
    std::string temp_login, temp_password;
    double temp_attendance;
    std::vector<int> assessments;
    std::string review;

    std::cout << "Login: " << std::endl;
    std::cin >> temp_login;

    if (users.find(temp_login) != users.end()) {
      std::cout << "User already exists!" << std::endl;
      return;
    }

    std::cout << "Password: " << std::endl;
    std::cin >> temp_password;

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

    std::cout << "Add a review: " << std::endl;
    std::cin.ignore();
    std::getline(std::cin, review);

    set_user(temp_login, temp_password, temp_attendance, assessments, review);
    save_data();
  }

  void open() {
    std::string temp_login, temp_password;

    std::cout << "Write login: " << std::endl;
    std::cin >> temp_login;

    std::cout << "Write password: " << std::endl;
    std::cin >> temp_password;

    if (users.find(temp_login) != users.end() &&
        users[temp_login].password == temp_password) {
      std::cout << "Login successful!" << std::endl;
      show_main(temp_login);
    } else {
      std::cout << "Incorrect login or password!" << std::endl;
    }
  }

  void show_main(std::string login) {
    int choice;
    do {
      std::cout << "User: " << login << std::endl;
      std::cout << "1 - View Review\n2 - View All Data\n3 - Help\n4 - Logout" << std::endl;
      std::cin >> choice;

      switch (choice) {
      case 1:
        std::cout << "Review: " << users[login].review << std::endl;
        break;
      case 2:
        std::cout << "Login: " << login << "\nPassword: " << users[login].password << "\nAttendance: " << users[login].attendance << "\nAssessments: ";
        for (int assessment : users[login].assessments) {
          std::cout << assessment << " ";
        }
        std::cout << "\nReview: " << users[login].review << std::endl;
        break;
      case 3:
        std::cout << "RECEIVING PART"<<std::endl;
        std::cout << "phone\n380678288586"<<std::endl;
        std::cout << "phone\n380504478895"<<std::endl;
        std::cout << "phone\n380737978800"<<std::endl;
        std::cout << "EDUCATIONAL PART"<<std::endl;
        std::cout << "phone\n380737978814"<<std::endl;
        std::cout << "ECONOMISTS"<<std::endl;
        std::cout << "phone\n380737978813"<<std::endl;
        std::cout << "Education Department Managers"<<std::endl;
        std::cout << "Olga Tretyakova"<<std::endl;
        std::cout << "Yulia Mazur"<<std::endl;
        break;
      case 4:
        std::cout << "Logging out..." << std::endl;
        break;
      default:
        std::cout << "Invalid choice!" << std::endl;
        break;
      }
    } while (choice != 4);
  }

  void start() {
    load_data();
    int choice;

    do {
      std::cout << "Hello, new? \n1 - registration\n2 - entrance\n3 - exit" << std::endl;
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
};

int main() {
  Main app;
  app.start();
  return 0;
}
