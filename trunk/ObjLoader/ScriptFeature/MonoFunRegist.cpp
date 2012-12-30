#include "MonoFunRegist.h"
#include "PreCompiledHeaders.h"

void OutPutToScreen()
{
	printf("Script Entry Success");
}

void RegistInternalCalls()
{
	mono_add_internal_call("ScriptRuntimeLibrary.Util::OutPutToScreen()",&OutPutToScreen);
}