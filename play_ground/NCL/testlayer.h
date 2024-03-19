#ifndef TESTLAYER_H
#define TESTLAYER_H
class testlayer
{
public:
    double input;
    double output;
    testlayer(/* args */);
    ~testlayer();
    virtual double forward(double &input) = 0;
    // virtual double backward() = 0;          // double &x, F &lr
};

testlayer::testlayer(/* args */)
{
}

testlayer::~testlayer()
{
}

#endif
