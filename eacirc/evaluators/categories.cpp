#include "categories.h"
#include "../CommonFnc.h"
#include <cmath>

double Categories::compute_result() const {
    // using two-smaple Chi^2 test
    // (http://www.itl.nist.gov/div898/software/dataplot/refman1/auxillar/chi2samp.htm)
    double k1 = 1;
    double k2 = 1;
    double chi_square_value = 0;
    int dof = 0;

    for (unsigned i = 0; i != _precision; ++i) {
        auto sum = _histogram_A[i] + _histogram_B[i];
        if (sum > 5) {
            dof++;
            chi_square_value += std::pow(k1 * _histogram_A[i] - k2 * _histogram_B[i], 2) / sum;
        }
    }
    dof--; // last category is fully determined by others

    ///////////// STATISTICS START
    _histogram_history_a.emplace_back(_histogram_A);
    _histogram_history_b.emplace_back(_histogram_B);
    ///////////// STATISTICS END

    return (1.0 - CommonFnc::chisqr(dof, chi_square_value));
}

#include <fstream>

Categories::~Categories() {
    {
        std::ofstream histogram_history_file_a("histograms_a.csv");
        for (const auto& histogram : _histogram_history_a) {
            for (unsigned i = 0; i != _precision - 1; ++i)
                histogram_history_file_a << histogram[i] << ", ";
            histogram_history_file_a << histogram.back() << std::endl;
        }
    }
    {
        std::ofstream histogram_history_file_b("histograms_b.csv");
        for (const auto& histogram : _histogram_history_b) {
            for (unsigned i = 0; i != _precision - 1; ++i)
                histogram_history_file_b << histogram[i] << ", ";
            histogram_history_file_b << histogram.back() << std::endl;
        }
    }
}
