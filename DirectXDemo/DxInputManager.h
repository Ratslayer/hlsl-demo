#pragma once
#include "main.h"
#include "DxRenderer.h"
//This is a class that contains the code for keyboard input processing
class DxInputManager
{
public:
	DxInputManager();
	~DxInputManager();

	static void ProcessKey(WPARAM key);
};

