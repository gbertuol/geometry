#pragma once

#include <boost/signals2.hpp>
#include <functional>

namespace geometry
{
    namespace utils
    {
        template <typename Signature>
        using Signal = boost::signals2::signal<Signature>;

        typedef boost::signals2::trackable SignalTrackable;
    }
}