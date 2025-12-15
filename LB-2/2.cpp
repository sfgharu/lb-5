#include <iostream>
#include <string>
using namespace std;

// Базовый класс Sales
class Sales {
protected:
    float sales[3]; // продажи за последние три месяца
public:
    void getSales() {
        cout << "Введите продажи за последние три месяца:\n";
        for (int i = 0; i < 3; ++i) {
            cout << "Месяц " << i + 1 << ": ";
            cin >> sales[i];
        }
        cin.ignore();
    }

    float getSalesSum() const {
        float sum = 0;
        for (int i = 0; i < 3; ++i) {
            sum += sales[i];
        }
        return sum;
    }
};

// Базовый класс Publication 
class Publication {
protected:
    string title;
    float price;
public:
    void getdata() {
        cout << "Введите название: ";
        getline(cin, title);
        cout << "Введите цену: ";
        cin >> price;
        cin.ignore();
    }
    void putdata() const {
        cout << "Название: " << title << endl;
        cout << "Цена: " << price << endl;
    }
};

// Класс Book, наследующий Publication и Sales
class Book : public Publication, public Sales {
private:
    int pages;
public:
    void getdata() {
        Publication::getdata();
        getSales();
        cout << "Введите количество страниц: ";
        cin >> pages;
        cin.ignore();
    }
    void putdata() const {
        Publication::putdata();
        cout << "Общий объем продаж за последние 3 месяца: " << getSalesSum() << endl;
        cout << "Количество страниц: " << pages << endl;
    }
};

// Класс Type (аудиозаписи), наследующий Publication и Sales
class Type : public Publication, public Sales {
private:
    int duration; // время записи в минутах
public:
    void getdata() {
        Publication::getdata();
        getSales();
        cout << "Введите время записи (минуты): ";
        cin >> duration;
        cin.ignore();
    }
    void putdata() const {
        Publication::putdata();
        cout << "Общий объем продаж за последние 3 месяца: " << getSalesSum() << endl;
        cout << "Время записи (минуты): " << duration << endl;
    }
};

int main() {
    Book myBook;
    Type myAudio;

    // Ввод данных о книге
    cout << "Ввод данных о книге:\n";
    myBook.getdata();

    // Ввод данных об аудиозаписи
    cout << "\nВвод данных об аудиозаписи:\n";
    myAudio.getdata();

    // Вывод данных
    cout << "\nИнформация о книге:\n";
    myBook.putdata();

    cout << "\nИнформация об аудиозаписи:\n";
    myAudio.putdata();

    return 0;
}
