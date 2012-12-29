#include "MonoFunRegist.h"
#include "PreCompiledHeaders.h"

void OutPutToScreen()
{
	printf("internal call success");
}

void RegistInternalCalls()
{
	mono_add_internal_call("OutPutToScreen()",&OutPutToScreen);
}