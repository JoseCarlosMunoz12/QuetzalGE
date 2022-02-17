#pragma once

#ifdef COATLPHYSICSENGINE_EXPORTS
#define COATL_API __declspec(dllexport)
#else
#define COATL_API __declspec(dllimport)
#endif
#include <string.h>
#include <string>