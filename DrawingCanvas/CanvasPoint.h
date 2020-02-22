#pragma once
namespace Rendering {
	class CanvasPoint
	{
	public:
		CanvasPoint();
		CanvasPoint(winrt::Windows::UI::Input::PointerPoint const & newPoint);
		float X()const;
		float Y()const;
		float XTilt()const;
		float YTilt()const;
		float Presure()const;
	private:
		float x;
		float y;
		float xTilt;
		float yTilt;
		float presure;
	};
}

