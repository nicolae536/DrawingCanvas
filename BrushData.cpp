#include "pch.h"
#include "BrushData.h"
#include "StringUtils.h"
#include <windows.h>

using namespace DrawingCanvas;

BrushData::BrushData()
	:
	_Id(L""),
	_Name(L""),
	_Size(ref new BrushSize(5, 5)),
	_PenTipShape(WinInk::PenTipShape::Circle),
	_PenTipTransform()
{
	UUID uuid;
	UuidCreate(&uuid);
	UuidToStringW(&uuid, (RPC_WSTR*)&_Id);
}

BrushData::BrushData(
	Platform::String^ id,
	Platform::String^ name,
	BrushSize^ size, 
	const Windows::UI::Input::Inking::PenTipShape penTipShape, 
	const Windows::Foundation::Numerics::float3x2 penTipTransform)
	:
	_Id(StringUtils::PlatformStringToWString(id)),
	_Name(StringUtils::PlatformStringToWString(name)),
	_Size(size),
	_PenTipShape(penTipShape),
	_PenTipTransform(penTipTransform)
{
}
