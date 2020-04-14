#ifndef WINDOW_H
#define WINDOW_H

#include "Event.h"
#include "Rectangle.h"
#include "Input.h"
#include <Windows.h>
#include <unordered_map>
#include <memory>
#include <string>
#include <optional>
#include <any>

namespace waffle
{
    enum class WindowType
    {
        Default = WS_OVERLAPPEDWINDOW,
        DisableResizing = WS_OVERLAPPED | WS_SYSMENU,
    };

    // Represents Windows API's window(the HWND thing...)
    class Window
    {
    public:
        Window() = default;
        Window(std::wstring title, Rectangle size, WindowType type = WindowType::Default);
        virtual ~Window();

        // Send resize message
        void Resize(Rectangle size);
        Rectangle Size() const;
        HWND Handle() const;

        // Return width/height
        // Used in creating projection matrix
        float AspectRatio() const;

        // Handle window message until message queue is empty
        // Window instances must be created on the same thread where this function is called!!!
        // This might block main loop in some cases(ex. window resizing & moving)
        // In this case, consider using separate thread for rendering
        static std::optional<int> ProcessMessage();

        // Send quit message
        static void Quit();

        // Helper function which simplifies main function
        template<typename T>
        static int MessageLoop(T loopBody)
        {
            while (true)
            {
                if (auto exit = Window::ProcessMessage(); exit.has_value())
                    return exit.value();

                loopBody();
            }
        }

        // Public event variables used to implement observer pattern
        Event<void(Rectangle)> resizeEvent;
        Event<void(MSG)> inputEvent;

        // Manages keyboard & mouse state
        Input input;

    protected:
        Rectangle size;
        WindowType type;
        HWND handle = NULL;

    private:
        // Returns the total window size including client area(specified size), frame, title, ....
        Rectangle AdjustedSize(Rectangle size, WindowType type);

        static LRESULT WINAPI WindowProcedure(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

        // Used in Window::WindowProcedure to map HWND(from message) to Window(this class) instance
        static std::unordered_map<HWND, Window*> windows;
    };
}

#endif
