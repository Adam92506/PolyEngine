#pragma once

#include "Poly/Core/Base.h"
#include "Poly/Core/Application.h"

#ifdef PY_PLATFORM_WINDOWS

int main(int argc, char** argv)
{
	Poly::Log::Init();

	auto app = Poly::CreateApplication({ argc, argv });

	app->Run();

	delete app;
}

#endif