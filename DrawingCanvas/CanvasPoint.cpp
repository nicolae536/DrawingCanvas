#include "pch.h"
#include "CanvasPoint.h"

Rendering::CanvasPoint::CanvasPoint()
	:x(0),
	y(0),
	xTilt(0),
	yTilt(0),
	presure(0)
{
}

Rendering::CanvasPoint::CanvasPoint(winrt::Windows::UI::Input::PointerPoint const& newPoint)
	: x(newPoint.Position().X),
	y(newPoint.Position().Y),
	xTilt(newPoint.Properties().XTilt()),
	yTilt(newPoint.Properties().YTilt()),
	presure(newPoint.Properties().Pressure())
{
}

float Rendering::CanvasPoint::X() const
{
	return x;
}

float Rendering::CanvasPoint::Y() const
{
	return y;
}

float Rendering::CanvasPoint::XTilt() const
{
	return xTilt;
}

float Rendering::CanvasPoint::YTilt() const
{
	return yTilt;
}

float Rendering::CanvasPoint::Presure() const
{
	return presure;
}
