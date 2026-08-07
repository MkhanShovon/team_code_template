/**
 * Author: Lukas Polacek
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Operators for modular arithmetic. You need to set {\tt mod} to
 * some number first and then you can use the structure.
 */
#pragma once

#include "euclid.h"

const ll mod = 17; // change to something else
struct Mod {
	ll x;
	Mod(ll xx = 0) : x(xx) {}
	Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
	Mod operator-(Mod b) { return Mod((x - b.x + mod) % mod); }
	Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
	Mod operator/(Mod b) { return *this * invert(b); }
	Mod invert(Mod a) {
		ll x, y, g = euclid(a.x, mod, x, y);
		assert(g == 1); return Mod((x + mod) % mod);
	}
	Mod operator^(ll e) {
		if (!e) return Mod(1);
		Mod r = *this ^ (e / 2); r = r * r;
		return e&1 ? *this * r : r;
	}
};

int main() {
    // 1. Initialize Mod objects (mod is currently set to 17 in your struct)
    Mod a(10);
    Mod b(12);

    // 2. Perform modular arithmetic operations
    Mod add = a + b;  // (10 + 12) % 17 = 5
    Mod sub = a - b;  // (10 - 12 + 17) % 17 = 15
    Mod mul = a * b;  // (10 * 12) % 17 = 1
    Mod exp = a ^ 2;  // (10^2) % 17 = 15
    
    // Division uses the modular inverse (euclid function required)
    Mod div = a / b;  // 10 * invert(12) % 17

    // 3. Access the '.x' property to print or use the final integer values
    std::cout << "a + b = " << add.x << "\n";
    std::cout << "a - b = " << sub.x << "\n";
    std::cout << "a * b = " << mul.x << "\n";
    std::cout << "a ^ 2 = " << exp.x << "\n";
    std::cout << "a / b = " << div.x << "\n";

    return 0;
}
