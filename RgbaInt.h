#pragma once


#include "pch.h"

namespace Common {
	class RgbaInt
	{
	public:
		RgbaInt(const Windows::UI::Color& color);
		void mixColor(const Windows::UI::Color& color);
		Windows::UI::Color toColor();
	private:
		int R;
		int G;
		int B;
		int A;
	};
};

