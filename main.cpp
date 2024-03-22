#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

class Date {
private:
    int day;
    int month1;
    int year;
    const int daysInMonth[12] = {31, 29 , 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const std::string month2[12] = {"January", "February", "March", "April", "May", "June","July", "August", "September", "October", "November", "December"};


public:
    Date(int d = 1, int m = 1, int y = 2000) : day(d), month1(m), year(y) {}

    //Метод для ввода даты
    void inputDate() {
        while (true) {
            std::cout << "Enter date:";
            char dot;
            std::cin >> day >> dot >> month1 >> dot >> year;

            // Проверка на правильность введенной даты
            if (std::cin.fail() || day < 1 || month1 < 1 || month1 > 12 || year < 0 || day > daysInMonth[month1 - 1] || (month1 == 2 && isLeapYear(year) && day >= 29))
            {
                std::cout << "Invalid date" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                break;
            }
        }
    }

    // Метод для определения високосного года
    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    void printFullDate() const {
        std::cout << day << " " << month2[month1 - 1] << " " << year <<std::endl;
    }

    // Перегрузка оператора <<
    friend std::ostream& operator<<(std::ostream& os, const Date& date) {
        os << std::setw(2) << std::setfill('0') << date.day << "."
           << std::setw(2) << std::setfill('0') << date.month1 << "."
           << std::setw(2) << std::setfill('0') << (date.year % 100);
        return os;
    }

    // Метод для вычисления разницы между датами в днях
    int daysDifference(const Date& other) const {
        int julian1 = getJulianDay();
        int julian2 = other.getJulianDay();
        return abs(julian2 - julian1);
    }

private:

    // Метод для расчета юлианского числа
    int getJulianDay() const {
        int a = (14 - month1) / 12;
        int y = year + 4800 - a;
        int m = month1 + 12 * a - 3;
        return day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    }
};

int main() {
    Date date1, date2;

    date1.inputDate();
    date2.inputDate();

    std::cout << "1 date: " << date1 << std::endl;
    std::cout << "2 date: " << date2 << std::endl;

    std::cout << "Difference: " << date1.daysDifference(date2) << std::endl;

    date1.printFullDate();
    date2.printFullDate();

    return 0;
}


