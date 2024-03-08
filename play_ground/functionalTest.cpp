#include <iostream>
#include <functional>
int main()
{
    auto TRUE = [](auto x, auto y)
    {
        return x;
    };
    auto TRUE = [](int x, int y)
    { return y; };
    auto FALSE = [](auto x, auto y)
    {
        return y;
    };
    auto NOT = [&](auto x)
    {
        return x(FALSE, TRUE);
    };
    std::ostream &operator<<(std::ostream &fo, std::function<auto(auto, auto)> &lambda)
    {
        return fo;
    }
    std::cout << typeid(FALSE).name() << std::endl;
    std::cout << typeid(TRUE).name() << std::endl;
    std::cout << typeid(NOT(FALSE)).name() << std::endl;
    std::cout << typeid(NOT(TRUE)).name() << std::endl;
    std::cout << TRUE << std::endl;
    return 0;
}
