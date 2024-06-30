#pragma once
#include "Transform.h"

namespace Component
{
	struct RectTransform : public Transform
	{
		RectTransform();

	private:

		void CalculateMatrices() override;
	};
}