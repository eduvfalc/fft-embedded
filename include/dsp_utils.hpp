#ifndef H_DSP_UTILS_HPP
#define H_DSP_UTILS_HPP

#include <chrono>
#include <complex>
#include <vector>
#include "fft_types.hpp"

class DSPUtils
{
public:
    DSPUtils() = default;

    explicit DSPUtils(double max_frequency_delta_pct)
      : m_max_frequency_delta_pct(max_frequency_delta_pct){};

    void
    bit_reversal(std::vector<Complex>& signal);

    void
    zero_padding(std::vector<Complex>& signal);

    std::vector<std::pair<double, double>>
    find_peaks(std::vector<Complex>& signal, std::chrono::nanoseconds sampling_period, int max_peaks);

    double
    normalize(std::vector<Complex>& signal);

    void
    apply_hann_window(std::vector<Complex>& signal) const;

private:
    double m_max_frequency_delta_pct = 0.05;
};

#endif  // H_DSP_UTILS_HPP