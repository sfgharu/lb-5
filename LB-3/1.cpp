#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Базовый класс 
class Component {
protected:
    Component(const std::string& name) : name(name) {}

public:
    virtual ~Component() = default;
    virtual void print() const = 0;
    std::string getName() const { return name; }

protected:
    std::string name;
};

// Класс Деталь
class Part : public Component {
protected:
    Part(const std::string& name, double weight) 
        : Component(name), weight(weight) {}

public:
    void print() const override {
        std::cout << "Деталь: " << name << " (вес: " << weight << " кг)" << std::endl;
    }

    double getWeight() const { return weight; }

    // Статические методы для создания объектов
    static std::unique_ptr<Part> createNut(double weight) {
        return std::unique_ptr<Part>(new Part("Гайка", weight));
    }

    static std::unique_ptr<Part> createScrew(double weight) {
        return std::unique_ptr<Part>(new Part("Винт", weight));
    }

    static std::unique_ptr<Part> createWasher(double weight) {
        return std::unique_ptr<Part>(new Part("Шайба", weight));
    }

    //  дружественная функция 
    template<typename Container>
    friend void addToStorage(Container& container, const std::string& partType, double weight);

private:
    double weight;
};

// Класс Сборка
class Assembly : public Component {
protected:
    Assembly(const std::string& name) : Component(name) {}

public:
    void addPart(std::unique_ptr<Part> part) {
        parts.push_back(std::move(part));
    }

    void print() const override {
        std::cout << "Сборка: " << name << " (содержит " << parts.size() << " деталей)" << std::endl;
        for (const auto& part : parts) {
            std::cout << "  - ";
            part->print();
        }
    }

    double getTotalWeight() const {
        double total = 0;
        for (const auto& part : parts) {
            total += part->getWeight();
        }
        return total;
    }

    // создание объектов
    static std::unique_ptr<Assembly> create(const std::string& name) {
        return std::unique_ptr<Assembly>(new Assembly(name));
    }

    // добавления в вектор
    template<typename Container>
    friend void addToStorage(Container& container, const std::string& name);

private:
    std::vector<std::unique_ptr<Part>> parts;
};

//добавления деталей в хранилище
template<typename Container>
void addToStorage(Container& container, const std::string& partType, double weight) {
    if (partType == "гайка") {
        container.push_back(Part::createNut(weight));
    } else if (partType == "винт") {
        container.push_back(Part::createScrew(weight));
    } else if (partType == "шайба") {
        container.push_back(Part::createWasher(weight));
    }
}

// Перегрузка 
template<typename Container>
void addToStorage(Container& container, const std::string& name) {
    container.push_back(Assembly::create(name));
}

int main() {
    std::vector<std::unique_ptr<Component>> storage;

    // Создаем детали 
    addToStorage(storage, "гайка", 0.005);
    addToStorage(storage, "винт", 0.01);
    addToStorage(storage, "шайба", 0.002);
    addToStorage(storage, "гайка", 0.008);
    addToStorage(storage, "винт", 0.015);

    // Создаем сборку  
    addToStorage(storage, "Моя сборка");

    // в сборку добавляем в нее детали
    auto assembly = dynamic_cast<Assembly*>(storage.back().get());
    if (assembly) {
        // Добавляем в сборку одну из каждой детали
        assembly->addPart(Part::createNut(0.005));
        assembly->addPart(Part::createScrew(0.01));
        assembly->addPart(Part::createWasher(0.002));
    }

    // Выводим информацию о всех компонентах
    std::cout << "СОДЕРЖИМОЕ ХРАНИЛИЩА" << std::endl;
    for (size_t i = 0; i < storage.size(); ++i) {
        std::cout << i + 1 << ". ";
        storage[i]->print();
    }

    //  полиморфизм
    std::cout << "\n ПОЛИМОРФИЗМ" << std::endl;
    for (const auto& component : storage) {
        std::cout << "Компонент: " << component->getName() << std::endl;
    }

    return 0;
}
