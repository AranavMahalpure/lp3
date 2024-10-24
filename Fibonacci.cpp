#include <iostream>
using namespace std;

int fibonacciNonRecursive(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    int prev1 = 0, prev2 = 1;
    int fib = 0;

    for (int i = 2; i <= n; i++) {
        fib = prev1 + prev2;
        prev1 = prev2;
        prev2 = fib;
    }
    return fib;
}

int main() {
    int n;
    cout << "Enter the value of n: ";
    cin >> n;
    cout << "Fibonacci(" << n << ") = " << fibonacciNonRecursive(n) << endl;
    return 0;
}


#include <iostream>
using namespace std;

int fibonacciRecursive(int n) {
    if (n <= 1) return n;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

int main() {
    int n;
    cout << "Enter the value of n: ";
    cin >> n;
    cout << "Fibonacci(" << n << ") = " << fibonacciRecursive(n) << endl;
    return 0;
}


// Non-Recursive	TO(n)	SO(1)
// Recursive	TO(2^n)	SO(n)