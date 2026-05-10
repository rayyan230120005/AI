#include <iostream>
using namespace std;

// Recursive function to calculate a^b
long long power(long long a, long long b) {
    // Base case
    if (b == 0)
        return 1;

    // Recursive case: divide the exponent by 2
    long long half = power(a, b / 2);

    // If exponent is even
    if (b % 2 == 0)
        return half * half;
    // If exponent is odd
    else
        return a * half * half;
}

int main() {
    long long a, b;
    cout << "Enter base (a): ";
    cin >> a;
    cout << "Enter exponent (b): ";
    cin >> b;

    cout << a << "^" << b << " = " << power(a, b) << endl;
    return 0;
}
