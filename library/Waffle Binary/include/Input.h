#ifndef INPUT_H
#define INPUT_H

#include <Windows.h>

namespace waffle
{
	// Virtual key codes
	enum class KeyCode
	{
		// 0 ~ 255 : keyboard (identical with the virtual-key codes)
		Ctrl = VK_CONTROL,
		Enter = VK_RETURN,
		Esc = VK_ESCAPE,
		Space = VK_SPACE,
		BackSpace = VK_BACK,
		Tab = VK_TAB,
		Left = VK_LEFT,
		Up = VK_UP,
		Right = VK_RIGHT,
		Down = VK_DOWN,
		Number0 = 0x30,
		Number1,
		Number2,
		Number3,
		Number4,
		Number5,
		Number6,
		Number7,
		Number8,
		Number9,
		A = 0x41,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,

		// 256 ~ 258 : mouse
		MouseLeft = 256,
		MouseRight,
		MouseMiddle
	};

	// Frame dependent input information.
	enum class InputState
	{
		// released before and now
		Released,
		// released now but not before
		ReleasingNow,
		// pressed before and now
		Pressing,
		// pressed now but not before
		PressedNow
	};

	class Window;

	// Manages input message from a window and provide
	// raw states (pressed or not) and frame state
	// (see InputState for more detail) for keyboard and mouse
	class Input
	{
    public:
		Input(Window& window);

		// Should be called at the beginning of a new frame
		// if you wish to use FrameState
		void UpdateFrameState();

		// True if pressed, false if not pressed
		bool RawState(KeyCode keyCode) const;

		// See InputState for description
		InputState FrameState(KeyCode keyCode) const;

		// Mouse coordinates in pixel where (0, 0) is top-left corner of window's client area
		int MouseX() const;
		int MouseY() const;

    private:
		void HandleMessage(MSG message);

        int mouseX = 0;
        int mouseY = 0;

        bool rawState[256 + 3] = {};
		InputState frameState[256 + 3] = {};
    };
}

#endif
