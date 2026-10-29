#include <bits/stdc++.h>
 
class FFTMultiplier {
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
    std::string multiply(std::string a_str, std::string b_str) {
        if (a_str == "0" || b_str == "0") return "0";
 
        std::vector<Complex> fa(a_str.begin(), a_str.end()), fb(b_str.begin(), b_str.end());
        
        // Convert ASCII characters to digits (reverse order for polynomials)
        for (auto& x : fa) x = static_cast<double>(x.real() - '0');
        for (auto& x : fb) x = static_cast<double>(x.real() - '0');
        std::reverse(fa.begin(), fa.end());
        std::reverse(fb.begin(), fb.end());
 
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
 
        // Extract integer coefficients and handle carries
        std::vector<long long> result(n);
        long long carry = 0;
        for (int i = 0; i < n; i++) {
            long long val = static_cast<long long>(std::round(fa[i].real())) + carry;
            result[i] = val % 10;
            carry = val / 10;
        }
 
        while (carry > 0) {
            result.push_back(carry % 10);
            carry /= 10;
        }
 
        // Remove leading zeros
        while (result.size() > 1 && result.back() == 0) {
            result.pop_back();
        }
 
        // Convert back to string
        std::string product = "";
        for (int i = static_cast<int>(result.size()) - 1; i >= 0; i--) {
            product += std::to_string(result[i]);
        }
 
        return product;
    }
};
 
