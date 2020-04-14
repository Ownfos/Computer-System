#ifndef COLOR_H
#define COLOR_H

namespace waffle
{
	class Color
	{
	public:
		Color() = default;

		// Initialize with normalized value (0 ~ 1).
		Color(float red, float green, float blue, float alpha);

		// Initialize with 8 bit value (0 ~ 255).
		Color(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha);

		// Initialize with 8 digit hexadecimal value (0x00000000 ~ 0xffffffff).
		Color(unsigned int hexCode);

		float Red();
		float Green();
		float Blue();
		float Alpha();

		// -Returns linear interpolation of colors.
		static Color Interpolate(Color left, Color right, float ratio);

	private:
		float red = 0.0f;
		float green = 0.0f;
		float blue = 0.0f;
		float alpha = 1.0f;
	};
}

#endif