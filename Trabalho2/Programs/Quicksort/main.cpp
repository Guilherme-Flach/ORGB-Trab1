#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>

int partition(std::vector<int>& numbers, const long int low, const long int high) {
    const int pivot = numbers[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (numbers[j] < pivot) {
            i++;
            std::swap(numbers[i], numbers[j]);
        }
    }
    std::swap(numbers[i + 1], numbers[high]);
    return i + 1;
}

void quicksort(std::vector<int>& numbers, const long int low, const long int high) {
    if (low >= high)
        return;
    const int pivot = partition(numbers, low, high);
    quicksort(numbers, low, pivot - 1);
    quicksort(numbers, pivot + 1, high);
}

void quicksort(std::vector<int>& numbers) {
    quicksort(numbers, 0, static_cast<long>(numbers.size()) - 1);
}

int main() {
    std::cout << "Greetings! This program will sort a specific amount of numbers using quicksort.\n" << std::endl;
    std::cout << "Please enter the amount of numbers to sort: ";
    long count;
    std::cin >> count;
    std::cout << "Preparing the number collection..." << std::endl;
    std::vector<int> numbers(count);
    for (int i = 0; i < count; i++)
        numbers[i] = static_cast<long int>(tan(i));
    std::cout << "Sorting the numbers..." << std::endl;
    const auto start = std::chrono::high_resolution_clock::now();
    quicksort(numbers);
    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Done!" << std::endl;

    const std::chrono::duration<double> diff = end - start;
    std::cout << "Time taken: " << diff.count() << " seconds\n";
    return 0;
}