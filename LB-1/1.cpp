#include <iostream>
int main() {
    setlocale(LC_ALL, "Russian");
    int n;

    // Ввод размера массива
    std::cout << "размер массива: ";
    std::cin >> n;

    // Проверка корректности ввода
    if (n <= 0) {
        std::cout << "размер должен быть положительным" << std::endl;
        return 1;
}
//Динамическое выделение памяти для массива 
int* arr = new int[n];

// Заполнение массива
std::cout << "элементы:" << std::endl;
for (int i = 0; i < n; ++i) {
    std::cout << "Элемент [" << i << "]: ";
    std::cin >> arr[i];
}
// Вывод содержимого массива
std::cout << "\nсодержимое массива:" << std::endl;
for (int i = 0; i < n; ++i) {
    std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
}
// Вывод адреса начала массива 
std::cout << "\nадрес начала массива: " << static_cast<void*>(arr) << std::endl;

// Вывод адресов элементов и расстояния от начала массива в байтах 
std::cout << "\nадреса элементов и pасстояние от начала:" << std::endl;
for (int i = 0; i < n; ++i) {
    // вычисление расстояния в байтах
    unsigned long distance_bytes = i * sizeof(int); //размер типа int в байтаx(4)

    std::cout << "Элемент [" << i << "]: адрес = " << static_cast<void*>(&arr[i]) 
                << ", расстояние = " << distance_bytes << " байт" << std::endl;
}
// Освобождение памяти (предотвращение утечки памяти)
delete[] arr;

return 0;
}