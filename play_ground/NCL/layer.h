#ifndef LAYER_H
#define LAYER_H
template <class INTYPE, class OUTTYPE, class F>
class layer
{
public:
    INTYPE input;
    OUTTYPE output;
    layer(/* args */);
    ~layer();
    virtual OUTTYPE forward(INTYPE &) = 0; //
    // virtual INTYPE backward() = 0;          // OUTTYPE &x, F &lr
};

template <class INTYPE, class OUTTYPE, class F>
layer<INTYPE, OUTTYPE, F>::layer(/* args */)
{
}

template <class INTYPE, class OUTTYPE, class F>
layer<INTYPE, OUTTYPE, F>::~layer()
{
}

#endif
