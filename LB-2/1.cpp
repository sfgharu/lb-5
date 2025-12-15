#include <iostream>
#include <string>
using namespace std;

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

// Класс Book, наследующий Publication
class Book : public Publication {
private:
    int pages;
public:
    void getdata() {
        Publication::getdata();
        cout << "Введите количество страниц: ";
        cin >> pages;
        cin.ignore();
    }
    void putdata() const {
        Publication::putdata();
        cout << "Количество страниц: " << pages << endl;
    }
};

// Класс Type (аудиозаписи), наследующий Publication
class Type : public Publication {
private:
    int duration; // время записи в минутах
public:
    void getdata() {
        Publication::getdata();
        cout << "Введите время записи (минуты): ";
        cin >> duration;
        cin.ignore();
    }
    void putdata() const {
        Publication::putdata();
        cout << "Время записи (минуты): " << duration << endl;
    }
};

int main() {
    // Создаем объекты
    Book myBook;
    Type myAudio;

    // Ввод данных для книги
    cout << "Ввод данных о книге:" << endl;
    myBook.getdata();

    // Ввод данных для аудиозаписи
    cout << "\nВвод данных об аудиозаписи:" << endl;
    myAudio.getdata();

    // Вывод данных
    cout << "\nИнформация о книге:" << endl;
    myBook.putdata();

    cout << "\nИнформация об аудиозаписи:" << endl;
    myAudio.putdata();

    return 0;
}
