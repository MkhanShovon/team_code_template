#include <bits/stdc++.h>

class PolynomialMultiplier {
private:
    typedef std::complex<double> Complex;
    const double PI = std::acos(-1.0);

    void fft(std::vector<Complex>& a, bool invert) {
        int n = static_cast<int>(a.size());
        if (n == 1) return;

        // Bit-reversal permutation
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) std::swap(a[i], a[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * PI / len * (invert ? -1 : 1);
            Complex wlen(std::cos(ang), std::sin(ang));
            for (int i = 0; i < n; i += len) {
                Complex w(1);
                for (int j = 0; j < len / 2; j++) {
                    Complex u = a[i + j], v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }

        if (invert) {
            for (Complex& x : a) {
                x /= n;
            }
        }
    }

public:
    // Multiplies polynomial A and polynomial B
    // Coefficients are ordered from lowest degree to highest: a0 + a1*x + a2*x^2 + ...
    std::vector<long long> multiply(const std::vector<long long>& a, const std::vector<long long>& b) {
        std::vector<Complex> fa(a.begin(), a.end());
        std::vector<Complex> fb(b.begin(), b.end());

        // Find the next power of 2 for the FFT size
        int n = 1;
        int required_size = static_cast<int>(fa.size() + fb.size());
        while (n < required_size) {
            n <<= 1;
        }
        fa.resize(n);
        fb.resize(n);

        // Apply FFT
        fft(fa, false);
        fft(fb, false);

        // Point-wise multiplication
        for (int i = 0; i < n; i++) {
            fa[i] *= fb[i];
        }

        // Apply Inverse FFT
        fft(fa, true);

        // Extract integer coefficients
        std::vector<long long> result(n);
        for (int i = 0; i < n; i++) {
            result[i] = static_cast<long long>(std::round(fa[i].real()));
        }

        // Remove trailing zeros for higher-degree coefficients
        while (result.size() > 1 && result.back() == 0) {
            result.pop_back();
        }

        return result;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Polynomial A: 1 + 2x  -> coefficients [1, 2]
    std::vector<long long> poly_a = {1, 2};

    // Polynomial B: 3 + 4x  -> coefficients [3, 4]
    std::vector<long long> poly_b = {3, 4};

    PolynomialMultiplier poly_multiplier;
    std::vector<long long> result = poly_multiplier.multiply(poly_a, poly_b);

    // Print the product polynomial coefficients
    std::cout << "Result coefficients: ";
    for (size_t i = 0; i < result.size(); i++) {
        std::cout << result[i] << (i + 1 < result.size() ? ", " : "\n");
    }
    // Output will be: 3, 10, 8 (representing 3 + 10x + 8x^2)

    return 0;
}