#include "tdc.h"

TDC::TDC()
{
    tdc_to_strip_ = 
    {
        // 7, 15, 23, 31,  6, 14, 22, 30,
        // 5, 13, 21, 29,  4, 12, 20, 28,
        // 3, 11, 19, 27,  2, 10, 18, 26,
        // 1,  9, 17, 25,  0,  8, 16, 24,

    //     28, 24, 20, 16, 12, 8, 4, 0,
    //     29, 25, 21, 17, 13, 9, 5, 1,
    //     30, 26, 22, 18, 14, 10, 6, 2,
    //     31, 27, 23, 19, 15, 11, 7, 3

        0, 4, 8, 12, 16, 20, 24, 28,
        1, 5, 9, 13, 17, 21, 25, 29,
        2, 6,10, 14, 18, 22, 26, 30,
        3, 7,11, 15, 19, 23, 27, 31
    };
    // strip_to_tdc_ = 
    // {
    //     24, 20, 16, 12,  8,  4,  0, 28,
    //     25, 21, 17, 13,  9,  5,  1, 29,
    //     26, 22, 18, 14, 10,  6,  2, 30,
    //     27, 23, 19, 15, 11,  7,  3, 31
    // };
    strip_to_tdc_ = 
    {
        28, 24, 20, 16, 12,  8,  4,  0,
        29, 25, 21, 17, 13,  9,  5,  1,
        30, 26, 22, 18, 14, 10,  6,  2,
        31, 27, 23, 19, 15, 11,  7,  3
    };

    bcid_resolution_ns = 25;
    fine_time_resolution_ns = 0.1953125; // 25ns / 2^7 precision of TDC
    width_time_resolution_ns = 0.4;
}

TDC::~TDC()
{
}

// ############### Singleton methods ##############

TDC TDC::instance_;

TDC & TDC::get()
{
    return instance_;
}

// ############### Implementations ################

int TDC::channel_to_strip_imp(int channel) const
{
    return tdc_to_strip_[channel];
}

int TDC::strip_to_channel_imp(int strip) const
{
    return strip_to_tdc_[strip];
}

double TDC::combined_time_ns_imp(int bcid, int fine_time) const
{
    return bcid_resolution_ns * bcid + fine_time_resolution_ns * fine_time;
}

double TDC::width_time_ns_imp(int width) const
{
    return width_time_resolution_ns * width;
}

// ############### Static functions ################

int TDC::channel_to_strip(int channel)
{
    return TDC::get().channel_to_strip_imp(channel);
}

int TDC::strip_to_channel(int strip)
{
    return TDC::get().strip_to_channel_imp(strip);
}

double TDC::combined_time_ns(int bcid, int fine_time)
{
    return TDC::get().combined_time_ns_imp(bcid, fine_time);
}

double TDC::width_time_ns(int width)
{
    return TDC::get().width_time_ns_imp(width);
}