#include <chrono>


namespace maze
{
    class Time
    {
    private:
        std::chrono::steady_clock::time_point current_time_stamp;

    public:
        Time();

        double milliseconds_since();
    };
}