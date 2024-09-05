#include <iostream>
#include <chrono>  // for std::chrono
#include <thread>  // for std::this_thread::sleep_for


void foo() {
    std::cout << "Inside foo()\n";
  //  std::this_thread::sleep_for(std::chrono::seconds(1));  // Sleep for 1 second
}

int bar(int a, int b) {
    std::cout << "Inside bar(), a = " << a << ", b = " << b << "\n";
  //  std::this_thread::sleep_for(std::chrono::seconds(2));  // Sleep for 2 seconds
    return a + b;
}

double baz(double x, double y) {
    std::cout << "Inside baz(), x = " << x << ", y = " << y << "\n";
   // std::this_thread::sleep_for(std::chrono::seconds(3));  // Sleep for 3 seconds
    return x * y;
}

void qux() {
    std::cout << "Inside qux()\n";
    
    //std::this_thread::sleep_for(std::chrono::seconds(1));  // Sleep for 1 second
}


int main() {
    foo();
    int result1 = bar(3, 4);
    double result2 = baz(2.5, 3.5);
    qux();
    std::cout << "Result of bar: " << result1 << "\n";
    std::cout << "Result of baz: " << result2 << "\n";
    printf("Hello world\n");
    return 0;
}