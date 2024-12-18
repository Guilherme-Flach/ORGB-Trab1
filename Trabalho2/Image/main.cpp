#include <iostream>
#include <complex>
#include <vector>
#include <chrono>
#include <bits/stl_algo.h>

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "include/stb_image_write.h"

void fft(std::vector<std::complex<double> > &x) {
    const auto size = x.size();
    if (size <= 1)
        return;
    std::vector<std::complex<double> > even(size / 2), odd(size / 2);
    for (int i = 0; i < size / 2; i++) {
        even[i] = x[2 * i];
        odd[i] = x[2 * i + 1];
    }
    fft(even);
    fft(odd);
    for (int i = 0; i < size / 2; i++) {
        std::complex<double> t = std::exp(std::complex<double>(0, -2 * M_PI * i / static_cast<double>(size))) * odd[i];
        x[i] = even[i] + t;
        x[i + size / 2] = even[i] - t;
    }
}

void ifftRec(std::vector<std::complex<double> > &x) {
    const auto size = x.size();
    if (size <= 1)
        return;
    std::vector<std::complex<double> > even(size / 2), odd(size / 2);
    for (int i = 0; i < size / 2; i++) {
        even[i] = x[2 * i];
        odd[i] = x[2 * i + 1];
    }
    ifftRec(even);
    ifftRec(odd);
    for (int i = 0; i < size / 2; i++) {
        std::complex<double> t = std::exp(std::complex<double>(0, 2 * M_PI * i / static_cast<double>(size))) * odd[i];
        x[i] = even[i] + t;
        x[i + size / 2] = even[i] - t;
    }
}

void ifft(std::vector<std::complex<double> > &x) {
    ifftRec(x);
    for (int i = 0; i < x.size(); i++)
        x[i] /= static_cast<double>(x.size());
}

std::vector<std::complex<double> > convertToComplex(const unsigned char *data, const int width, const int height) {
    std::vector<std::complex<double> > result(width * height);
    const auto newSize = pow(2, ceil(log2(width * height)));
    for (int i = 0; i < width * height; i++)
        result[i] = std::complex<double>(data[i], 0);
    while (static_cast<double>(result.size()) < newSize)
        result.emplace_back(0, 0);
    return result;
}

unsigned char *convertToArray(const std::vector<std::complex<double> > &data) {
    auto *result = new unsigned char[data.size()];
    for (int i = 0; i < data.size(); i++) {
        const auto clamped = std::clamp(data[i].real(), 0.0, 255.0);
        result[i] = static_cast<unsigned char>(round(clamped));
    }
    return result;
}

void filter(std::vector<std::complex<double> > &image) {
    double max = -1.0 * INFINITY, average = 0;
    for (auto complex: image) {
        average = average + abs(complex);
        if (abs(complex) > max)
            max = abs(complex);
    }
    average /= static_cast<double>(image.size());
    auto threshold = average + (max - average) * 0.5;
    for (auto &i: image)
        if (abs(i) > threshold)
            i = 0;
}

int main() {
    int width, height, channels;
    constexpr auto desiredChannels = 1;
    const auto before = std::chrono::high_resolution_clock::now();
    std::cout << "Loading image..." << std::endl;
    unsigned char *data = stbi_load("./input.png", &width, &height, &channels, desiredChannels);
    if (data == nullptr) {
        std::cout <<
                "Error loading image. Make sure that your file is located at the root of the execution path and named 'input.png'."
                << std::endl;
        return 1;
    }
    std::cout << "Image loaded successfully! " << width << "x" << height << ", " << channels << " channels." <<
            std::endl;
    std::cout << "Converting image to complex coefficients..." << std::endl;
    auto complex = convertToComplex(data, width, height);
    stbi_image_free(data);
    std::cout << "Calculating DFT of image..." << std::endl;
    fft(complex);
    std::cout << "Applying filters..." << std::endl;
    filter(complex);
    std::cout << "Restoring image..." << std::endl;
    ifft(complex);
    const auto new_image = convertToArray(complex);
    std::cout << "Saving image..." << std::endl;
    stbi_write_png("./output.png", width, height, desiredChannels, new_image, width * desiredChannels);
    delete[] new_image;
    const auto after = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::seconds>(after - before).count() <<
            " second(s)" << std::endl;
    return 0;
}
