#pragma once
#include <vector>
#include <memory>
#include "CanvasPoint.h"

namespace Rendering {
	class DrawingQueue
	{
	private:
		std::shared_ptr<std::vector<Rendering::CanvasPoint>> pointsQueue;
		bool isPointerActive;
	public:
		DrawingQueue();
		void Add(Rendering::CanvasPoint point);
		void ActivatePointer();
		void DeactivatePointer();
		std::shared_ptr<std::vector<Rendering::CanvasPoint>> GetPoints();		
	};
}

