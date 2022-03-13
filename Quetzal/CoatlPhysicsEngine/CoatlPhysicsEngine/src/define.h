#pragma once

#ifdef COATLPHYSICSENGINE_EXPORTS
#define COATL_API __declspec(dllexport)
#else
#define COATL_API __declspec(dllimport)
#endif
#include <string.h>
#include <string>
#include <vector>
#include <memory>
template <typename T>
using U_P = std::unique_ptr<T>;
template <typename T>
using S_P = std::shared_ptr<T>;
template <typename T>
using Vec_SH = std::vector<S_P<T>>;
template <typename T>
using Vec_UP = std::vector<U_P<T>>;