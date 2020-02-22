#include "pch.h"
#include "CanvasBrush.h"
#include <random>
#include <math.h>

Rendering::CanvasBrush::CanvasBrush()
	: width(20.0f),
	height(20.0f),
	penTip(PenTip::Pencil),
	penTipShape(PenTipShape::Circle),
	radius(width / 2),
	color(winrt::Windows::UI::Colors::Black())
{
}

void Rendering::CanvasBrush::Draw(Rendering::CanvasPoint const& point, winrt::Microsoft::Graphics::Canvas::CanvasDrawingSession const& ds)
{
	//float density = 30;
	//float densityGap = radius * 2 * density / 100;


	//
	//ds.DrawGradientMesh()

	////if (penTipShape == PenTipShape::Circle) {
	//	auto maxX = point.X() + radius;
	//	auto minX = point.X() - radius;
	//	auto maxY = point.Y() + radius;
	//	auto minY = point.Y() - radius;

	//	auto i = minX;
	//	auto j = minY;	

	//	// TODO Reasearch math function which defines
	//	// makes a gradient over a surface but similar with a pencil
	//	while (i < maxX && j < maxY)
	//	{
	//		auto distanceToPoint = std::sqrt(std::pow((i - point.X()), 2) + std::pow((j - point.Y()), 2));
	//		if (distanceToPoint < radius) {
	//			ds.FillCircle(i, j, 1, color);
	//		}
	//		i += densityGap;
	//		if (i > maxX) {
	//			j += densityGap;
	//			i = minX;
	//		}
	//	}
	//}
}
