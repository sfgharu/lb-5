#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <memory>

using namespace std;

// Иерархия классов ошибок
class ProgramError {
public:
    virtual ~ProgramError() = default;
    virtual string getMessage() const = 0;
    virtual void print() const {
        cout << "Ошибка программы: " << getMessage() << endl;
    }
};

class InsufficientMemoryError : public ProgramError {
public:
    string getMessage() const override {
        return "Недостаточно памяти";
    }
};

class InputOutputError : public ProgramError {
public:
    string getMessage() const override {
        return "Ошибка ввода/вывода";
    }
};

class FileReadError : public InputOutputError {
public:
    string getMessage() const override {
        return "Ошибка чтения файла";
    }
};

class FileWriteError : public InputOutputError {
public:
    string getMessage() const override {
        return "Ошибка записи файла";
    }
};

// Шаблонный класс для хранения массива указателей
template <typename T>
class PointerArray {
private:
    vector<T*> pointers;
    size_t maxSize;
    static const size_t MAX_ALLOWED_SIZE = 50;

public:
    // Конструктор
    PointerArray(size_t initialSize = 10) : maxSize(initialSize) {
        if (initialSize > MAX_ALLOWED_SIZE) {
            throw range_error("Запрошенный размер " + to_string(initialSize) + 
                            " превышает максимально допустимый размер " + to_string(MAX_ALLOWED_SIZE));
        }
        pointers.resize(initialSize, nullptr);
    }

    // Деструктор
    ~PointerArray() {
        for (size_t i = 0; i < pointers.size(); ++i) {
            delete pointers[i];
        }
    }

    // Перегрузка оператора [] для неконстантного объекта
    T*& operator[](size_t index) {
        if (index >= pointers.size()) {
            throw out_of_range("Индекс " + to_string(index) + 
                             " вне диапазона. Размер массива: " + to_string(pointers.size()));
        }
        return pointers[index];
    }

    // Перегрузка оператора [] для константного объекта
    const T* operator[](size_t index) const {
        if (index >= pointers.size()) {
            throw out_of_range("Индекс " + to_string(index) + 
                             " вне диапазона. Размер массива: " + to_string(pointers.size()));
        }
        return pointers[index];
    }

    // Добавление элемента
    void addElement(size_t index, T* element) {
        if (index >= pointers.size()) {
            throw out_of_range("Индекс вне диапазона");
        }
        if (pointers[index] != nullptr) {
            delete pointers[index];
        }
        pointers[index] = element;
    }

    // Получение размера
    size_t getSize() const {
        return pointers.size();
    }

    // Получение максимального допустимого размера
    static size_t getMaxAllowedSize() {
        return MAX_ALLOWED_SIZE;
    }

    // Вывод всех элементов
    void printAll() const {
        cout << "Содержимое массива (" << pointers.size() << " элементов):" << endl;
        for (size_t i = 0; i < pointers.size(); ++i) {
            cout << "[" << i << "]: ";
            if (pointers[i] != nullptr) {
                pointers[i]->print();
            } else {
                cout << "nullptr" << endl;
            }
        }
    }
};

// Демонстрационный класс для тестирования
class DemoClass {
private:
    string name;
    int value;

public:
    DemoClass(const string& n = "", int v = 0) : name(n), value(v) {}
    
    void print() const {
        cout << "Демо-класс: " << name << " (значение: " << value << ")" << endl;
    }
    
    string getName() const { return name; }
    int getValue() const { return value; }
};

// Функция для возведения в степень с проверкой range_error
double safePower(double base, int exponent) {
    if (exponent < 0) {
        throw invalid_argument("Отрицательные степени не поддерживаются");
    }
    
    double result = 1.0;
    for (int i = 0; i < exponent; ++i) {
        // Проверка на переполнение во время вычислений
        if (result > 1e100) {
            throw range_error("Результат возведения в степень превысит максимально допустимое значение (1e100) во время вычислений");
        }
        result *= base;
    }
    
    // Проверка результата на допустимый диапазон
    if (result > 1e50) {
        throw range_error("Результат " + to_string(result) + 
                        " превышает максимально допустимый диапазон (0, 1e50)");
    }
    
    return result;
}

int main() {
    try {
        cout << "Демонстрация работы с иерархией ошибок" << endl;
        
        // Создание массива для ошибок
        PointerArray<ProgramError> errorArray(4);
        
        // Заполнение массива различными типами ошибок
        errorArray.addElement(0, new InsufficientMemoryError());
        errorArray.addElement(1, new InputOutputError());
        errorArray.addElement(2, new FileReadError());
        errorArray.addElement(3, new FileWriteError());
        
        // Демонстрация полиморфизма
        errorArray.printAll();
        
        cout << "\n Демонстрация работы с DemoClass" << endl;
        
        // Создание массива для DemoClass
        PointerArray<DemoClass> demoArray(3);
        
        demoArray.addElement(0, new DemoClass("Объект1", 100));
        demoArray.addElement(1, new DemoClass("Объект2", 200));
        demoArray.addElement(2, new DemoClass("Объект3", 300));
        
        demoArray.printAll();
        
        // Демонстрация работы оператора []
        cout << "\nДемонстрация оператора []" << endl;
        for (size_t i = 0; i < 3; ++i) {
            cout << "Элемент " << i << ": ";
            demoArray[i]->print();
        }
        
        cout << "\nТестирование обработки исключений" << endl;
        
        // Тестирование out_of_range
        try {
            cout << "Попытка доступа к несуществующему индексу" << endl;
            demoArray[10]->print();
        } catch (const out_of_range& e) {
            cout << "out_of_range: " << e.what() << endl;
        }
        
        cout << "\nДемонстрация range_error" << endl;
        
        // Демонстрация возведения в степень
        try {
            cout << "возведение в степень:" << endl;
            cout << "2^5 = " << safePower(2, 5) << " (успешно)" << endl;
            
            cout << "Попытка вычислить 10^20" << endl;
            cout << "10^20 = " << safePower(10, 20) << endl;
        } catch (const range_error& e) {
            cout << "range_error: " << e.what() << endl;
        } catch (const invalid_argument& e) {
            cout << "invalid_argument: " << e.what() << endl;
        }
        
        // Пример с отрицательной степенью
        try {
            cout << "\nПопытка вычислить с отрицательной степенью" << endl;
            cout << "2^-3 = " << safePower(2, -3) << endl;
        } catch (const invalid_argument& e) {
            cout << "invalid_argument: " << e.what() << endl;
        }
        
    } catch (const exception& e) {
        cerr << "Неожиданная ошибка в программе: " << e.what() << endl;
        return 1;
    }
    
        return 0;
}
