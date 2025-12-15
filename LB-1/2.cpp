#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum BookType {
    HUD,    // Худ
    TEC   // Тех
};
class Book {
private:
    string author;
    string title;
    BookType type;
public:
    Book(const string& auth, const string& titl, BookType typ) {
        if (auth.empty() || titl.empty()) {
            throw invalid_argument("ошибка");
        }
        author = auth;
        title = titl;
        type = typ;
    }
    //методы класса для доступа к приватным полям
    string getAuthor() const { return author; }
    string getTitle() const { return title; }
    BookType getType() const { return type; }

    // Деструктор
    ~Book() {}
};
class Library {
private:
    vector<Book*> books;
    
public:
    // Добавление книги
    void addBook(Book* book) {
        books.push_back(book);
    }

    //  с switch
    void countBooksWithSwitch() const {
        int fictionCount = 0;
        int technicalCount = 0;

        for (const auto& book : books) {
            switch (book->getType()) {
                case HUD:
                    fictionCount++;
                    break;
                case TEC:
                    technicalCount++;
                    break;
            }
        }

        cout << "Количество худ литературы: " << fictionCount << endl;
        cout << "Количество тех литературы: " << technicalCount << endl;
    }

    //без switch
    void countBooksWithoutSwitch() const {
        int fictionCount = 0;
        int technicalCount = 0;

        for (const auto& book : books) {
            if (book->getType() == HUD) {
                fictionCount++;
            } else if (book->getType() == TEC) {
                technicalCount++;
            }
        }

        cout << "Количество худ литературы: " << fictionCount << endl;
        cout << "Количество тех литературы: " << technicalCount << endl;
    }

    // Вывод всей худ
    void displayFictionBooks() const {
        cout << "Художественная литература:" << endl;
        
        bool found = false;
        for (const auto& book : books) {
            if (book->getType() == HUD) {
                cout << "Автор: " << book->getAuthor() << endl;
                cout << "Название: " << book->getTitle() << endl;
                found = true;
            }
        }
        
        if (!found) {
            cout << "Художественная литература не найдена" << endl;
        }
    }
     // Вывод всей тех
    void displayTechnicalBooks() const {
        cout << "---------------------------------" << endl;
        cout << "Научная (техническая) литература:" << endl;
       
        
        bool found = false;
        for (const auto& book : books) {
            if (book->getType() == TEC) {
                cout << "Автор: " << book->getAuthor() << endl;
                cout << "Название: " << book->getTitle() << endl;
                
                found = true;
            }
        }
        
        if (!found) {
            cout << "Научная литература не найдена" << endl;
        }
    }

    //освобождения памяти
    ~Library() {
        for (auto& book : books) {
            delete book;
        }
        books.clear();
    }
};

int main() {
    Library library;
    try {
        library.addBook(new Book("Тарас Чирков", "Эксплуатация ЦОД.", TEC));
        library.addBook(new Book("Стивен Кинг", "Зеленая Миля", HUD));
        library.addBook(new Book("Достоевский", "Преступление и наказание", HUD));
        library.addBook(new Book("Лев Толстой", "Война и мир", HUD));       
        
        // Вывод с switch
        cout << "с switch:" << endl;
        library.countBooksWithSwitch();
        cout << endl;
        
        // Вывод без switch
        cout << "без switch:" << endl;
        library.countBooksWithoutSwitch();
        cout << endl;
        
        // Вывод всех
        library.displayFictionBooks();
        library.displayTechnicalBooks();
        

    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}
