#include "time.h"

maze::Time::Time()
{
    current_time_stamp = std::chrono::steady_clock::now();
}

/* Return the number of milliseconds since last call */
double maze::Time::milliseconds_since()
{

    /* Adapted from snippet http://en.cppreference.com/w/cpp/chrono/time_point
       (accessed 16/9/14) */

    std::chrono::steady_clock::time_point finish = std::chrono::steady_clock::now();

    double milliseconds_since_last_call = 
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - current_time_stamp).count();

    current_time_stamp = finish;

    return milliseconds_since_last_call;

}