#include <iostream>
#include <math.h>
// -D__USE_MINGW_ANSI_STDIO

template <class ITYPE, class OTYPE>
class layer
{
public:
    const ITYPE *input;
    OTYPE *output;
    layer *next;
    virtual OTYPE forward(const ITYPE &) = 0;
    virtual ITYPE backward() = 0;
    OTYPE operator()(const ITYPE &);
    layer();
    ~layer();
};
template <class ITYPE, class OTYPE>
layer<ITYPE, OTYPE>::layer()
{
    // std::cout << "layer constructor p=" << this << std::endl;
    next = nullptr;
    output = new long double;
    // std::cout << "layer constructor end p=" << this << std::endl;
}
template <class ITYPE, class OTYPE>
layer<ITYPE, OTYPE>::~layer()
{
    // std::cout << "layer destructor p=" << this << std::endl;
    delete output;
    // std::cout << "layer destructor end p=" << this << std::endl;
}
template <class ITYPE, class OTYPE>
OTYPE layer<ITYPE, OTYPE>::operator()(const ITYPE &x)
{
    // std::cout << "layer operator() p=" << this << std::endl;
    // std::cout << "layer operator() end p=" << this << std::endl;
    return forward(x);
}

template <class ITYPE, class OTYPE>
class activi : public layer<ITYPE, OTYPE>
{
public:
    ITYPE *dinput;
    activi();
    ~activi();
};
template <class ITYPE, class OTYPE>
activi<ITYPE, OTYPE>::activi()
{
    // std::cout << "activi constructor p=" << this << std::endl;
    dinput = new ITYPE;
    // std::cout << "activi constructor end p=" << this << std::endl;
}
template <class ITYPE, class OTYPE>
activi<ITYPE, OTYPE>::~activi()
{
    // std::cout << "activi destructor p=" << this << std::endl;
    delete dinput;
    // std::cout << "activi destructor end p=" << this << std::endl;
}

template <class ITYPE, class OTYPE>
class trainabli : public activi<ITYPE, OTYPE>
{
public:
    virtual void zero_d() = 0;
    virtual void step() = 0;
    trainabli();
    ~trainabli();
};
template <class ITYPE, class OTYPE>
trainabli<ITYPE, OTYPE>::trainabli()
{
}
template <class ITYPE, class OTYPE>
trainabli<ITYPE, OTYPE>::~trainabli()
{
}

class Tanh : public activi<long double, long double>
{
public:
    long double forward(const long double &);
    long double backward();
    Tanh();
    ~Tanh();
};
long double Tanh::forward(const long double &x)
{
    // std::cout << "Tanh forward p=" << this << std::endl;
    input = &x;
    *output = tanh(*input);
    // std::cout << "Tanh forward end p=" << this << std::endl;
    if (next != nullptr)
    {
        return (*next)(*output);
    }
    return *output;
}
long double Tanh::backward()
{
    // std::cout << "Tanh backward p=" << this << std::endl;
    long double t = tanh(*input);
    *dinput = 1 - t * t;
    // std::cout << "Tanh backward end p=" << this << std::endl;
    if (next != nullptr)
    {
        return (*next).backward() * *dinput;
    }
    return *dinput;
}
Tanh::Tanh()
{
    std::cout << "Tanh constructor p=" << this << std::endl;
    std::cout << "Tanh constructor end p=" << this << std::endl;
}
Tanh::~Tanh()
{
    std::cout << "Tanh destructor p=" << this << std::endl;
    std::cout << "Tanh destructor end p=" << this << std::endl;
}

class lirg : public trainabli<long double, long double>
{
public:
    long double a;
    long double b;
    long double da;
    long double db;
    long double forward(const long double &);
    long double backward();
    void zero_d(){};
    void step(){};
    lirg();
    ~lirg();
};
long double lirg::forward(const long double &x)
{
    // std::cout << "lirg forward p=" << this << std::endl;
    input = &x;
    *output = a * *input + b;
    // std::cout << "lirg forward end p=" << this << std::endl;
    if (next != nullptr)
    {
        return (*next)(*output);
    }
    return *output;
}
long double lirg::backward()
{
    // std::cout << "lirg backward p=" << this << std::endl;
    *dinput = a;
    da = *input;
    db = 1;
    // std::cout << "lirg backward end p=" << this << std::endl;
    if (next != nullptr)
    {
        long double dy = (*next).backward();
        da *= dy;
        db *= dy;
        return dy * *dinput;
    }
    return *dinput;
}
lirg::lirg()
{
    a = 1L;
    b = 0L;
}
lirg::~lirg()
{
}

// class SQ : public layer<double, double>
// {
// public:
//     double a;
//     double b;
//     double da;
//     double db;
//     double forward(const double &);
//     double backward();
//     double operator()(const double &);
//     SQ();
//     ~SQ();
// };
// double SQ::forward(const double &x)
// {
// std::cout << "SQ forward p=" << this << std::endl;
//     output = a * x * x + b;
// std::cout << "SQ forward end p=" << this << std::endl;
//     if (next == NULL)
//     {
//         return output;
//     }
//     return (*next)(output);
// }
// double SQ::backward()
// {
// std::cout << "SQ backward p=" << this << std::endl;
// std::cout << "SQ backward end p=" << this << std::endl;
//     return 0;
// }
// double SQ::operator()(const double &x)
// {
// std::cout << "SQ operator() p=" << this << std::endl;
// std::cout << "SQ operator() end p=" << this << std::endl;
//     return forward(x);
// }
// SQ::SQ()
// {
// std::cout << "SQ constructor p=" << this << std::endl;
//     a = 1;
//     b = 1;
//     next = NULL;
//     prev = NULL;
// std::cout << "SQ constructor end p=" << this << std::endl;
// }
// SQ::~SQ()
// {
// std::cout << "SQ destructor p=" << this << std::endl;
// std::cout << "SQ destructor end p=" << this << std::endl;
// }

template <class ITYPE, class OTYPE>
void show_activi(const activi<ITYPE, OTYPE> &A)
{
    std::cout << *A.input << std::endl
              << *A.output << std::endl
              << A.next << std::endl
              << *A.dinput << std::endl;
}

int main()
{
    // SQ f[2];
    // f[0].next = &f[1];
    // f[1].prev = &f[0];
    // std::cout << "------" << f[0](1) << "------\n";
    // Tanh f[2];
    // f[0].next = &f[1];
    // std::cout << f[0](1) << std::endl;
    // std::cout << f[0].backward() << std::endl;
    // // std::cout << f[1](1) << std::endl;
    // // std::cout << f[1].backward() << std::endl;
    // show_activi(f[0]);
    // std::cout << std::endl;
    // show_activi(f[1]);
    // std::cout << sizeof(Tanh) << " " << sizeof(long double *) << std::endl;
    // std::cout << *f[0].input << std::endl;
    // std::cout << &(f[0].input) << std::endl;
    // std::cout << &(f[0].output) << std::endl;
    // std::cout << &(f[0].next) << std::endl;
    // std::cout << &(f[0].dinput) << std::endl;

    lirg f;
    Tanh g;
    f.next = &g;
    std::cout << f(1) << std::endl;
    f.backward();
    show_activi(f);
    show_activi(g);
    // f[0].a = (long double)f[0].a;
    // f[0].b = (long double)f[0].b;
    // printf("%Lf\n", f[0].a);
    // printf("%Lf\n", f[0].b);
    // // printf("%Lf\n", __LDBL_MAX__);
    // printf("%Lf", f[0].a * f[0].b);
    return 0;
}
