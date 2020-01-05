#include "pch.h"
#include "BrushData.h"

using namespace Models;

Models::BrushData::BrushData()
	:
	_Name(),
	Size(ref new BrushSize(5, 5)),
	PenTipTransform()
{
	PenTipShape = WinInk::PenTipShape::Circle;
}

Models::BrushData::BrushData(const BrushSize size, const Windows::UI::Input::Inking::PenTipShape penTipShape, const Windows::Foundation::Numerics::float3x2 penTipTransform)
	:
	_Name(),
	Size(ref new BrushSize(size.Width, size.Height)),
	PenTipShape(penTipShape),
	PenTipTransform(penTipTransform)
{
}

void Models::BrushData::UpdateSize(BrushSize size)
{
	Size->Height = size.Height;
	Size->Width = size.Width;
}

void Models::BrushData::UpdatePenTipShape(Windows::UI::Input::Inking::PenTipShape penTipShape)
{
	PenTipShape = penTipShape;
}

void Models::BrushData::UpdatePenTipTransform(Windows::Foundation::Numerics::float3x2 penTipTransform)
{
	PenTipTransform = PenTipTransform;
}

Windows::Foundation::Size Models::BrushData::GetInkSize()
{
	return Windows::Foundation::Size(Size->Width, Size->Height);
}
