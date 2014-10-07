#pragma once


namespace extra
{

	/* is_in_container uses the find function and const_iterator of containers to determine
	if an object is contained in the container 
	T must be a container with the find function that returns an iterator and must allow access 
	to an end iterator.
	*/
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

