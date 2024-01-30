#ifndef H_IFFT_HPP
#define H_IFFT_HPP

#include <complex>
#include <vector>


using Complex = std::complex<double>;

class IFFT
{
public:
    virtual ~IFFT() = default;

    virtual void
    Compute(std::vector<Complex>& signal)
        = 0;
};

#endif  // H_IFFT_HPP