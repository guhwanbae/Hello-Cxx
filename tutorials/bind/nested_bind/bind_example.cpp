//  Author  :   Gu-hwan Bae
//  Date    :   21 September 2018
//  Summary :   Nested std::bind subexpression share the std::placeholders.

#include <iostream>
#include <functional>
#include <vector>
#include <exception>

using namespace std::placeholders;

#include "wireless_signal.h"

// Using C++11 std::bind
WirelessSignal high_pass_filterB(const WirelessSignal& input) {
    // Filter's physical properties
    constexpr double cutoff_freq {300000000}; // 300 MHz 
    constexpr double threshold {0.9}; 

    /*
    // Unfortunately, expressions can not be passed to the constructor of std::bind.
    auto is_valid_signal = std::bind(std::logical_and<bool>(),
            threshold < _1, cutoff_freq < _2);
    */

    // Therefore, we should use a nested std::bind.
    // Howerver, it is much more complex to read than using functor or lambda expr.
    // Nested std::bind subexpression share the std::placeholder.
    auto is_valid_signal = std::bind(std::logical_and<bool>(),
            std::bind(std::less<double>(), threshold, _1),
            std::bind(std::less<double>(), cutoff_freq, _2));

    if(!is_valid_signal(input.get_power(), input.get_carrier_freq())) {
        // If power of signal is under threshold or
        // carrier frequence under cut-off frequence,
        // the signal will be absorbed.
        throw std::runtime_error("Oops! Wireless signal has been absorbed.");
    }

    WirelessSignal output {input};
    return output;
}

void use_high_pass_filter() {
    WirelessSignal wifi {2400000000}; // Wifi, 802.11b standard, 2.4 GHz
    WirelessSignal tv_broadcast {850000000}; // digital tv broadcast, 850MHz
    WirelessSignal am_radio {25000000}; // AM Radio broadcast, 25 MHz

    std::vector<WirelessSignal> signals {wifi, tv_broadcast, am_radio};
    std::vector<WirelessSignal> filtered;

    for(const auto& sig : signals) {
        std::cout << "Original signal : power = " << sig.get_power()
            << ", carrier frequence : " << sig.get_carrier_freq() << " Hz" << std::endl;
        try {
            filtered.emplace_back(high_pass_filterB(sig));
        }
        catch(std::runtime_error msg) {
            std::cout << msg.what() << std::endl;
        }
    }

    for(const auto& sig : filtered) {
        std::cout << "Filtered signal : power = " << sig.get_power()
            << ", carrier frequence : " << sig.get_carrier_freq() << " Hz" << std::endl;
    }
}

int main() {
    use_high_pass_filter();
    return 0;
}
