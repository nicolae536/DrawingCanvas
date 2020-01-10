#include "pch.h"
#include "BrushData.h"
#include "StringUtils.h"

using namespace Models;

Models::BrushData::BrushData()
	:
	_Name(),
	Size(ref new BrushSize(5, 5)),
	PenTipTransform()
{
	PenTipShape = WinInk::PenTipShape::Circle;
}

Models::BrushData::BrushData(BrushSize^ size, const Windows::UI::Input::Inking::PenTipShape penTipShape, const Windows::Foundation::Numerics::float3x2 penTipTransform)
	:
	_Name(),
	Size(size),
	PenTipShape(penTipShape),
	PenTipTransform(penTipTransform)
{
}

Platform::String^ Models::BrushData::GetName()
{
	return StringUtils::WStringToPlatformString(_Name);
}

BrushSize^ Models::BrushData::GetBrushSize()
{
	return Size;
}

WinInk::PenTipShape Models::BrushData::GetPenTipShape()
{
	return PenTipShape;
}

WinNumerics::float3x2 Models::BrushData::GetPenTipTransform()
{
	return PenTipTransform;
}

void Models::BrushData::UpdateSize(BrushSize^ size)
{
	Size = size;
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
	return Windows::Foundation::Size(Size->GetWidth(), Size->GetHeight());
}
