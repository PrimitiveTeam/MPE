#include <iostream>
#include <Test/Test.h>

int main()
{
    std::cout << "Hello, MPE!\n";

    MPE::Test test;
    std::cout << test.GetName() << std::endl;

    return 0;
}