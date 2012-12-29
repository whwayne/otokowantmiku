#include <stdio.h>
#include <Windows.h>

#ifdef ESCAPE_EXPORTS
#define ESCAPE_API __declspec(dllexport)
#else
#define ESCAPE_API __declspec(dllimport)
#endif