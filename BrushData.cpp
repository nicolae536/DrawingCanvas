#include "pch.h"
#include "BrushData.h"
#include "StringUtils.h"

using namespace DrawingCanvas;

BrushData::BrushData()
	:
	_Name(),
	Size(ref new BrushSize(5, 5)),
	PenTipTransform()
{
	PenTipShape = WinInk::PenTipShape::Circle;
}

BrushData::BrushData(
	Platform::String^ name,
	BrushSize^ size, 
	const Windows::UI::Input::Inking::PenTipShape penTipShape, 
	const Windows::Foundation::Numerics::float3x2 penTipTransform)
	:
	_Name(StringUtils::PlatformStringToWString(name)),
	Size(size),
	PenTipShape(penTipShape),
	PenTipTransform(penTipTransform)
{
}

BrushSize^ BrushData::GetBrushSize()
{
	return Size;
}

WinInk::PenTipShape BrushData::GetPenTipShape()
{
	return PenTipShape;
}

WinNumerics::float3x2 BrushData::GetPenTipTransform()
{
	return PenTipTransform;
}

void BrushData::UpdateSize(BrushSize^ size)
{
	Size = size;
}

void BrushData::UpdatePenTipShape(Windows::UI::Input::Inking::PenTipShape penTipShape)
{
	PenTipShape = penTipShape;
}

void BrushData::UpdatePenTipTransform(Windows::Foundation::Numerics::float3x2 penTipTransform)
{
	PenTipTransform = PenTipTransform;
}

Windows::Foundation::Size BrushData::GetInkSize()
{
	return Windows::Foundation::Size(Size->GetWidth(), Size->GetHeight());
}
