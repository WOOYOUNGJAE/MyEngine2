#pragma once

#include <optix.h>
#include <optix_function_table_definition.h>
#include <optix_stack_size.h>
#include <optix_stubs.h>

class COptix : public IUnknown
{
	COM_BASE
public:
	COptix();
	~COptix();
};

