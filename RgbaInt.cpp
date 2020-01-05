#include "pch.h"
#include "RgbaInt.h"

Common::RgbaInt::RgbaInt(const Windows::UI::Color& color)
	: R(color.R),
	G(color.G),
	B(color.B),
	A(color.A)
{
}

void Common::RgbaInt::mixColor(const Windows::UI::Color& color) {
	int r = color.R;
	int g = color.G;
	int b = color.B;
	int a = color.A;

	R = (R + r) / 2;
	G = (G + g) / 2;
	B = (B + b) / 2;
	A = (A + a) / 2;
}

Windows::UI::Color Common::RgbaInt::toColor() {
	return Windows::UI::ColorHelper::FromArgb(A, R, G, B);
}