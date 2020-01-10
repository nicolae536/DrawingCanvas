#include "pch.h"
#include "BrushSize.h"

using namespace Models;


BrushSize::BrushSize(float width, float height)
	: Width(width),
	Height(height)
{
}

float Models::BrushSize::GetWidth()
{
	return Width;
}

float Models::BrushSize::GetHeight()
{
	return Height;
}

void Models::BrushSize::SetWidth(float width)
{
	Width = width;
}

void Models::BrushSize::SetHeight(float height)
{
	Height = height;
}
