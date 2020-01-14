#include "pch.h"
#include "BrushSize.h"

using namespace DrawingCanvas;


BrushSize::BrushSize(float width, float height)
	: Width(width),
	Height(height)
{
}

float BrushSize::GetWidth()
{
	return Width;
}

float BrushSize::GetHeight()
{
	return Height;
}

void BrushSize::SetWidth(float width)
{
	Width = width;
}

void BrushSize::SetHeight(float height)
{
	Height = height;
}
