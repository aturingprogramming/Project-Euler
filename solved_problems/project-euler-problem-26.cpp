#include <iostream>
#include <vector>
#include <algorithm>

// Fast modular exponentiation 
long long power_mod(long long base, long long exp, long long mod) {
    long long res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (__int128)res * base % mod; 
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return res;
}

// Find and sort divisors of phi 
std::vector<long long> get_divisors(long long n) {
    std::vector<long long> divisors;
    for (long long i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (i * i != n) {
                divisors.push_back(n / i);
            }
        }
    }
    std::sort(divisors.begin(), divisors.end());
    return divisors;
}

// Calculate Euler's Totient Function 
long long calculate_phi(long long d) {
    long long result = d;
    for (long long p = 2; p * p <= d; p++) {
        if (d % p == 0) {
            while (d % p == 0) {
                d /= p;
            }
            result -= result / p;
        }
    }
    if (d > 1) {
        result -= result / d;
    }
    return result;
}

long long repeated_length(long long d) {
    while (d % 2 == 0) d /= 2;
    while (d % 5 == 0) d /= 5;
    if (d == 1) return 0;
    long long phi = calculate_phi(d);
    std::vector<long long> divisors = get_divisors(phi);
    
    // Find the first (smallest) divisor that satisfies Lagrange
    for (long long k : divisors) {
        if (power_mod(10, k, d) == 1) {
            return k;
        }
    }
    return 0;
}

int main() {
    long long max_length = 0;
    long long best_d = 0;
    
    for (int i = 2; i < 1000; i++) {
        long long current_length = repeated_length(i);
        if (current_length > max_length) {
            max_length = current_length;
            best_d = i;
        }
    }
    
    std::cout << "The number d < 1000 with the longest recurring decimal is: " << best_d << "\n";
    std::cout << "The length of its repetend is: " << max_length << " digits.\n";
    
    return 0;
}
