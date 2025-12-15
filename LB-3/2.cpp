#include <iostream>
#include <vector>
#include <memory>
#include <random>

// Базовый класс
class Base {
protected:
    Base(const std::string& name) : name(name) {}

public:
    virtual ~Base() = default;
    virtual void show() const {
        std::cout << "Base: " << name << std::endl;
    }
    std::string getName() const { return name; }

    // создание объектов
    static std::unique_ptr<Base> create(const std::string& name) {
        return std::unique_ptr<Base>(new Base(name));
    }

    // добавление в хранилище
    template<typename Container>
    friend void add(Container& container, std::unique_ptr<Base> obj);

protected:
    std::string name;
};

// Производный класс
class Derived : public Base {
protected:
    Derived(const std::string& name, int value) : Base(name), specialValue(value) {}

public:
    void show() const override {
        std::cout << "Derived: " << name << " (специальное значение: " << specialValue << ")" << std::endl;
    }

    // создание объектов
    static std::unique_ptr<Base> create(const std::string& name, int value) {
        return std::unique_ptr<Base>(new Derived(name, value));
    }

private:
    int specialValue;
};

// добавления в хранилище
template<typename Container>
void add(Container& container, std::unique_ptr<Base> obj) {
    container.push_back(std::move(obj));
}

int main() {
    std::vector<std::unique_ptr<Base>> storage;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);

    // Создание объектов в цикле случайным образом
    for (int i = 0; i < 5; ++i) {
        int randomValue = dis(gen);
        
        if (randomValue % 2 == 0) {
            // Четное Base
            auto obj = Base::create("BaseObject_" + std::to_string(i));
            add(storage, std::move(obj));
            std::cout << "Создан Base (случайное число: " << randomValue << ")" << std::endl;
        } else {
            // Нечетное Derived
            auto obj = Derived::create("DerivedObject_" + std::to_string(i), randomValue * 10);
            add(storage, std::move(obj));
            std::cout << "Создан Derived (случайное число: " << randomValue << ")" << std::endl;
        }
    }

    std::cout << "\n ПОЛИМОРФИЗМ" << std::endl;
    
    // разница объектов
    for (size_t i = 0; i < storage.size(); ++i) {
        std::cout << i + 1 << ". ";
        storage[i]->show(); // Полиморфный вызов
    }
    return 0; }
