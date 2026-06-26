#include <iostream>
#include <vector>
#include <numeric>

void solveMaxTotientRatio(int limit) {
    std:: vector<bool> is_prime(limit+1,true);
    std:: vector<int> primes;
    std:: vector<int> phi(limit+1);
    
    std::iota(phi.begin(),phi.end(),0);
    phi[1]=1;
    
    int best_n = 1;
    // linear sieve
    for(int i=2;i<=limit;i++){
        if(is_prime[i]){
            primes.push_back(i);
            phi[i]=i-1;
        }
        for (int p : primes) {
            if (i*p>limit) break; 
            is_prime[i*p] = false; 
            
            if (i%p == 0) {
                phi[i*p] = phi[i]*p; 
                break; 
            } 
            else {
                phi[i*p] = phi[i]*(p-1);
            }
        }
        
        if (1LL*i*phi[best_n] > 1LL*best_n*phi[i]) {
            best_n = i;
        }
    }
    
    std::cout << "The value maximizing n/phi(n) is: " << best_n << "\n";
}

int main() {
    solveMaxTotientRatio(1000000);
    return 0;
}
