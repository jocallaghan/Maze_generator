#pragma once

namespace josh
{
    template<typename T, typename Y>
    bool is_in_container(T container, Y object)
    {
        typename T::const_iterator found_in_container = container.find(object);
        if(found_in_container == container.end())
            return false;
        else
            return true;
    }
}

