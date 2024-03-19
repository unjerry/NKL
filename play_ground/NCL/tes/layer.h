#ifndef LAYER_H
#define LAYER_H
#include <iostream>
template <class INPUT, class OUTPUT, class F>
class layer
{
public:
    INPUT input;
    OUTPUT output;
    virtual OUTPUT forward(const INPUT &) = 0;
    virtual INPUT backward(const OUTPUT &, const F &) = 0;
    virtual void step() = 0;
    virtual void zero_d() = 0;
    layer();
    ~layer();
};
template <class INPUT, class OUTPUT, class F>
layer<INPUT, OUTPUT, F>::layer()
{
    std::cout << "layer constructor p=" << this << std::endl;
    std::cout << "layer constructor end p=" << this << std::endl;
}
template <class INPUT, class OUTPUT, class F>
layer<INPUT, OUTPUT, F>::~layer()
{
    std::cout << "layer destructor p=" << this << std::endl;
    std::cout << "layer destructor end p=" << this << std::endl;
}
#endif
