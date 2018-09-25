//  Author  :   Gu-hwan Bae
//  Date    :   21 September 2018
//  Summary :   std::bind vs lambda expression

#include <iostream>
#include <functional>
#include <vector>
#include <exception>

#include "wireless_signal.h"

// Using C++11 lambda expression
WirelessSignal high_pass_filterL(const WirelessSignal& input) {
    // Filter's physical properties
    constexpr double cutoff_freq {300000000}; // 300 MHz 
    constexpr double threshold {0.9}; 

    // It's much more simple than using std::bind.
    auto is_valid_signal = [cutoff_freq, threshold] (const WirelessSignal& signal)
        {
            return (signal.get_power() > threshold)
                       && (signal.get_carrier_freq() > cutoff_freq);
        };

    if(!is_valid_signal(input)) {
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
            filtered.emplace_back(high_pass_filterL(sig));
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
