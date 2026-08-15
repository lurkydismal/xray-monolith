#pragma once

#include <time.h>

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

using xr_time_t = std::time_t;

template < typename TP >
xr_time_t xr_chrono_to_time_t( TP tp ) {
    using namespace std::chrono;
    auto sctp = time_point_cast< system_clock::duration >(
        tp - TP::clock::now() + system_clock::now() );

    return system_clock::to_time_t( sctp );
}

xr_string getCurrentTimeStamp( const char* format = "%H:%M:%S" );

xr_string timeInDMYHMSMMM();
xr_string timeInHMSMMM();
