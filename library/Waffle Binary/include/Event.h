#ifndef EVENT_H
#define EVENT_H

#include <boost/signals2.hpp>
#include <functional>

namespace waffle
{
    // Wrapper class for boost::signals2::signal
    template<typename Handler>
    class Event
    {
    public:
        using SignalType = boost::signals2::signal<Handler>;

        auto AddHandler(std::function<Handler> handler)
        {
            return signal.connect(handler);
        }

        template<typename T>
        auto AddHandler(std::function<Handler> handler, std::shared_ptr<T> track)
        {
            return signal.connect(SignalType::slot_type(handler).track_foreign(track));
        }

        template<typename... Args>
        auto Signal(Args&&... args)
        {
            signal(std::forward<Args>(args)...);
        }

    private:
        SignalType signal;
    };
}

#endif