#pragma once

#include "Input/InputAction.h"


class IInputSource
{
public:
	virtual ~IInputSource() = default;

	virtual bool isActionHeld(InputAction action) const = 0;
	virtual bool isActionPressed(InputAction action) const = 0;
};
