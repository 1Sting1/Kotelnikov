#ifndef RATIONAL_VECTOR_H
#define RATIONAL_VECTOR_H

#include <iostream>
#include <algorithm>
#include <stdexcept>

template<typename T>
class Vector {
private:
    T* array; // Указатель на первый элемент массива
    size_t capacity; // Размер выделенной памяти
    size_t size; // Текущий размер вектора

    T sum; // Сумма элементов вектора
    double average; // Среднее значение элементов вектора
    bool isSumAverageValid; // Флаг, указывающий, что сумма и среднее значение корректны

public:
    // Конструктор по умолчанию
    Vector() : array(nullptr), capacity(0), size(0), sum(0), average(0), isSumAverageValid(false) {}

    // Конструктор с заданным начальным размером
    Vector (size_t initial_size) : array(new T[initial_size]), capacity(initial_size), size(initial_size), sum(0), average(0), isSumAverageValid(false) {}

    // Деструктор
    ~Vector() {
        delete[] array;
    }

    // Метод добавления элемента в конец вектора
    void push_back(const T& value) {

        if (size >= capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        array[size++] = value;
        updateSumAverage(value);
    }

    // Метод удаления элемента из указанной позиции
    void erase(size_t index) {
        if (index >= size) {
            throw std::out_of_range("out of range");
        }
        // Обновляем сумму и среднее значение перед удалением элемента
        updateSumAverage(array[index], true);

        // Сдвигаем элементы влево начиная с индекса до конца массива
        for (size_t i = index; i < size - 1; ++i) {
            array[i] = array[i + 1];
        }
        --size;
    }

    // Метод добавления элемента в указанную позицию
    void insert(size_t index, const T& value) {
        if (index > size) {
            throw std::out_of_range("out of range");
        }

        if (size >= capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }


        for (size_t i = size; i > index; --i) {
            array[i] = array[i - 1];
        }
        array[index] = value;
        ++size;
        updateSumAverage(value);
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("out of range");
        }

        return array[index];
    }

    // Метод получения размера вектора
    size_t getSize() const {
        return size;
    }

    // Метод выделения памяти для вектора
    void reserve(size_t new_capacity) {
        if (new_capacity <= capacity) {
            return;
        }
        T* new_array = new T[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_array[i] = std::move(array[i]);
        }
        delete[] array;
        array = new_array;
        capacity = new_capacity;
    }

    // Оператор вывода для класса Vector
    friend std::ostream& operator<<(std::ostream& out, const Vector<T>& vec) {
        out << "[";
        for (size_t i = 0; i < vec.size; ++i) {
            out << vec.array[i];
            if (i != vec.size - 1) {
                out << ", ";
            }
        }
        out << "]";
        return out;
    }

    // Метод обновления суммы и среднего значения
    void updateSumAverage(const T& value, bool subtract = false) {
        if (subtract && isSumAverageValid) {
            sum -= value;
            average = static_cast<double>(sum) / size;
        }
        else {
            sum += value;
            average = static_cast<double>(sum) / size;
            isSumAverageValid = true;
        }
    }

    // Метод получения суммы
    T getSum() const {
        if (!isSumAverageValid) {
            throw std::logic_error("error");
        }
        return sum;
    }

    // Метод получения среднего значения элементов вектора
    double getAverage() const {
        if (!isSumAverageValid) {
            throw std::logic_error("error");
        }
        return average;
    }

    // Метод вычисления медианы вектора
    double getMedian() const {
        if (size == 0) {
            throw std::logic_error("error");
        }

        Vector<T> temp(*this);
        std::sort(temp.array, temp.array + temp.size);

        if (size % 2 == 0) {
            return static_cast<double>((temp.array[size / 2 - 1] + temp.array[size / 2])) / 2;
        }

        else {
            return temp.array[size / 2];
        }
    }
};

#endif
