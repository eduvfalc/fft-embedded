#include <algorithm>
#include <chrono>
#include <complex>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include "../tests/utils/include/signal_generator.hpp"
#include "dsp_utils.hpp"
#include "etl/vector.h"
#include "fft.hpp"
#include "fft_types.hpp"

using namespace fftemb;

int
main()
{
    // sine parameters (amplitude, frequency)
    std::vector<std::pair<double, double>> parameters{{10, 60}};

    // signal generator parameters (mind the trade-off in between frequency/time resolution)
    std::chrono::nanoseconds sampling_period
        = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(0.001));
    std::chrono::milliseconds duration(
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<double>(1)));

    // create signal container
    etl::vector<Complex, 1024> signal(1024);

    // create signal generator
    std::shared_ptr<SignalGenerator> generator = std::make_shared<SignalGenerator>(duration, sampling_period);

    // generate sine function
    generator->generate_sine_wave(signal, parameters);

    // normalize
    std::shared_ptr<DSPUtils> dsp_utils     = std::make_shared<DSPUtils>();
    auto                      max_amplitude = dsp_utils->normalize(signal);

    // apply the Hann window
    dsp_utils->apply_hann_window(signal);

    // compute FFT
    std::shared_ptr<FFT<Complex>> fft = std::make_shared<FFT<Complex>>(dsp_utils);
    fft->compute(signal);

    // calculate peak
    auto peak_data = dsp_utils->find_peaks(signal, sampling_period, parameters.size());
    std::cout << "Peak: " << peak_data[0].first * max_amplitude << std::endl
              << "Peak freq: " << peak_data[0].second << std::endl;

    return 0;
}
