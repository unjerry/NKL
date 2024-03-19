#ifndef DENSE_H
#define DENSE_H
#include "matrix_over_field.h"
#include "layer.h"
class dense : public layer<matrix_over_field<double>, matrix_over_field<double>, double>
{
public:
    matrix_over_field<double> W;
    matrix_over_field<double> dW;
    matrix_over_field<double> B;
    matrix_over_field<double> dB;
    dense(const size_t &, const size_t &);
    ~dense();
    matrix_over_field<double> forward(const matrix_over_field<double> &);
    matrix_over_field<double> backward(const matrix_over_field<double> &, const double &);
    void step();
    void zero_d();
};
dense::dense(const size_t &input_size, const size_t &output_size)
{
    // std::cout << "dense constructor p=" << this << std::endl;
    this->W = *new matrix_over_field<double>(output_size, input_size);
    this->B = *new matrix_over_field<double>(output_size, 1);
    this->dW = *new matrix_over_field<double>(output_size, input_size);
    this->dB = *new matrix_over_field<double>(output_size, 1);
    this->W = 1;
    this->B = 0;
    this->dW = 0;
    this->dB = 0;
    // std::cout << "dense constructor end p=" << this << std::endl;
}
dense::~dense()
{
    // std::cout << "dense destructor p=" << this << std::endl;
    // std::cout << "dense destructor end p=" << this << std::endl;
}
matrix_over_field<double> dense::forward(const matrix_over_field<double> &input)
{
    // std::cout << "dense forward p=" << this << std::endl;
    this->input = input;
    this->output = this->W * this->input + this->B;
    // std::cout << "dense forward end p=" << this << std::endl;
    return this->output;
}
matrix_over_field<double> dense::backward(const matrix_over_field<double> &x, const double &lr)
{
    // std::cout << "dense backward p=" << this << std::endl;
    this->dW = this->dW + lr * x * this->input.T();
    this->dB = this->dB + lr * x;
    // std::cout << "dense backward end p=" << this << std::endl;
    return this->W.T() * x;
}
void dense::step()
{
    // std::cout << "dense step p=" << this << std::endl;
    this->W = this->W - this->dW;
    this->B = this->B - this->dB;
    // std::cout << "dense step end p=" << this << std::endl;
}
void dense::zero_d()
{
    // std::cout << "dense zero_d p=" << this << std::endl;
    this->dW = 0;
    this->dB = 0;
    // std::cout << "dense zero_d end p=" << this << std::endl;
}
#endif
