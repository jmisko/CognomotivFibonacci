#include <iostream>

#define CACHE_SZ 512

// Fibonacci numbers:
// F(n) is sum of F(n-1), F(n-2)
// F(0) = 0, F(1) = 1
// all functions take an int(32bit) and return double(64bit) float
// to avoid overflow

double fib_recursive(int n)
{
    // Recursive Fibonacci is simple to ounderstand but has the drawback of
    // exponential growth since it requires 2 more function calls per iteration,
    // Each call will have its own stack frame and will quickly cause stack
    // overflow on system with constrained memory.
    // Recursion in this case also creates alot of repeated work,
    // even at n=4 we can start to see the repetition
    // F(4)->{F(3)-{F(2) {(F(1), F(0)}, F(1)}, F(2)->{F(1), F(0)}}

    // Handle F(0), F(1) cases
    if (n < 2) {
        return n;
    }
    return fib_recursive(n-1) + fib_recursive(n-2);
}

double fib_cache[CACHE_SZ] = {0}; // zero initialize

double fib_recursive_cache(int n)
{
    // This builds on fib_recursive by checking if a value for a specific n
    // has already been calculated. This will remove exponential memory
    // growth issue of plain recursion but is limited to fixed cache size.
    // Not ideal but will allow n > 100 easily and repeated calls will be fast

    // Handle F(0), F(1) cases
    if (n < 2) {
        return n;
    } else if (n > CACHE_SZ) {
        std::cout << "n greater than " << CACHE_SZ << std::endl;
        return -1;
    }

    if (fib_cache[n]) {
        return fib_cache[n];
    }

    fib_cache[n] =  fib_recursive_cache(n-1) + fib_recursive_cache(n-2);
    return fib_cache[n];
}


double fib_iter(int n)
{
    // Iteratve Fibonacci function is slightly longer but is still easy to
    // understand. Instead of repeadedly adding new function call frames to the
    // stack, this function only has a few local variables and a for loop so
    // there isnt any risk of stack overflow. Time complexity is also simply
    // O(n). This is my preferred approach for embedded because of simplicity,
    // low memory use, and safety

    double n1, n2, sum;

    // Handle F(0), F(1) cases
    if (n < 2) {
        return n;
    }

    n2 = 0; // n minus 2
    n1 = 1; // n minus 1

    for (int i = 2; i <= n; i++) {
        sum = n1 + n2;
        n2 = n1;
        n1 = sum;
    }
    return sum;
}

int main(int argc, char * argv[])
{
    double iter, recursive, cache;
    int n1, n2, i;

    // n1 = 50; recursive fibonacci starts to overflow after ~40
    n1 = 20; // smaller n1 still shows all 3 methods work
    n2 = 100;

    std::cout << "Print fibonacci numbers from 0-100" << std::endl;
    std::cout << "recursive, cached, and Iteratve methods" << std::endl;

    for (i = 0; i < n1; i++) {
        recursive = fib_recursive(i);
        cache = fib_recursive_cache(i);
        iter = fib_iter(i);
        std::cout << "n: " << i << " recursive: " << recursive;
        std::cout << " cache: " << cache << " iter: " << iter << std::endl;
    }

    std::cout << "Pure recursion is showing growth problem..." << std::endl;
    std::cout << "Lets just continue with cache and iterative" << std::endl;

    for (i = n1; i <= n2; i++) {
        cache = fib_recursive_cache(i);
        iter = fib_iter(i);
        std::cout << "n: " << i << " cache: " << cache;
        std::cout << " iter: " << iter << std::endl;
    }
    return 0;
}
