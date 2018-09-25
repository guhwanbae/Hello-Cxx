class WirelessSignal {
    public :
        explicit WirelessSignal(double cf, double pwr = 1.0) : 
            carrier_freq {cf}, power {pwr} {};

        WirelessSignal(const WirelessSignal&) = default;
        WirelessSignal& operator=(const WirelessSignal&) = default;

        WirelessSignal(WirelessSignal&&) = default;
        WirelessSignal& operator=(WirelessSignal&&) = default;

        double get_carrier_freq() const noexcept;
        double get_power() const noexcept;
    private :
        double carrier_freq;
        double power;
};

double WirelessSignal::get_carrier_freq() const noexcept {
    return carrier_freq;
}

double WirelessSignal::get_power() const noexcept {
    return power;
}
