#pragma once
#include "CanvasPoint.h"

namespace Rendering {
	enum PenTip {
		Pencil = 0,
		Brush = 1,
	};

	enum PenTipShape {
		Circle = 0,
		Rectangle = 1,
	};

	class CanvasBrush
	{
	public:
		CanvasBrush();

		void Draw(Rendering::CanvasPoint const& point, winrt::Microsoft::Graphics::Canvas::CanvasDrawingSession const& ds);
	private:
		float width;
		float height;
		float radius;
		winrt::Windows::UI::Color color;

		PenTip penTip;
		PenTipShape penTipShape;
	};
}

