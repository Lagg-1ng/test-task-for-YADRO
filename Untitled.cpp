#include <iostream>
#include <complex>
#include <vector>
#include <cmath>

class FastFourierTransform {
private:
    // Helper function for recursive FFT
    void fftRecursive(std::vector<std::complex<double>>& a, bool invert);

public:
    // Perform FFT
    void fft(std::vector<std::complex<double>>& a, bool invert);

    // Perform inverse FFT
    void ifft(std::vector<std::complex<double>>& a);
};

// Helper function for recursive FFT
void FastFourierTransform::fftRecursive(std::vector<std::complex<double>>& a, bool invert) {
    int n = a.size();
    if (n <= 1)
        return;

    std::vector<std::complex<double>> a0(n / 2), a1(n / 2);
    for (int i = 0, j = 0; i < n; i += 2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i + 1];
    }

    fftRecursive(a0, invert);
    fftRecursive(a1, invert);

    double angle = 2 * M_PI / n * (invert ? -1 : 1);
    std::complex<double> w(1), wn(cos(angle), sin(angle));

    for (int i = 0; i < n / 2; ++i) {
        std::complex<double> t = w * a1[i];
        std::complex<double> u = a0[i];
        a[i] = u + t;
        a[i + n / 2] = u - t;
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

// Perform FFT
void FastFourierTransform::fft(std::vector<std::complex<double>>& a, bool invert) {
    int n = a.size();
    fftRecursive(a, invert);

    if (invert) {
        for (int i = 0; i < n; ++i)
            a[i] /= n;
    }
}

// Perform inverse FFT
void FastFourierTransform::ifft(std::vector<std::complex<double>>& a) {
    fft(a, true);
}

int main() {
    // Generate random complex input data
    std::vector<std::complex<double>> input = { {1, 2}, {3, 4}, {5, 6}, {7, 8} };

    // Forward FFT
    FastFourierTransform fft;
    fft.fft(input, false);

    // Display the result of the forward FFT
    std::cout << "Forward FFT result:" << std::endl;
    for (const auto& complex_num : input) {
        std::cout << complex_num << " ";
    }
    std::cout << std::endl;

    // Inverse FFT
    fft.ifft(input);

    // Display the result of the inverse FFT
    std::cout << "Inverse FFT result:" << std::endl;
    for (const auto& complex_num : input) {
        std::cout << complex_num << " ";
    }
    std::cout << std::endl;

    return 0;
}
