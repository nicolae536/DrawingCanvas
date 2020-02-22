#include "pch.h"
#include "DrawingQueue.h"

Rendering::DrawingQueue::DrawingQueue()
	:pointsQueue(std::make_shared<std::vector<Rendering::CanvasPoint>>()),
	isPointerActive(false)
{
}

void Rendering::DrawingQueue::Add(Rendering::CanvasPoint point)
{
	if (isPointerActive) {
		pointsQueue->push_back(point);
	}
}

void Rendering::DrawingQueue::ActivatePointer()
{
	isPointerActive = true;
}

void Rendering::DrawingQueue::DeactivatePointer()
{
	isPointerActive = false;
}

std::shared_ptr<std::vector<Rendering::CanvasPoint>> Rendering::DrawingQueue::GetPoints()
{
	return pointsQueue;
}
