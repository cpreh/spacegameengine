/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "handle_error.hpp"
#include <sge/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/string.hpp>

namespace
{
fcppt::string const
error_code_to_string(
	cl_int const code)
{
	switch (code)
	{
		case CL_SUCCESS: return FCPPT_TEXT("CL_SUCCESS: Success!");
		case CL_DEVICE_NOT_FOUND: return FCPPT_TEXT("CL_DEVICE_NOT_FOUND: Device not found.");
		case CL_DEVICE_NOT_AVAILABLE: return FCPPT_TEXT("CL_DEVICE_NOT_AVAILABLE: Device not available");
		case CL_COMPILER_NOT_AVAILABLE: return FCPPT_TEXT("CL_COMPILER_NOT_AVAILABLE: Compiler not available");
		case CL_MEM_OBJECT_ALLOCATION_FAILURE: return FCPPT_TEXT("CL_MEM_OBJECT_ALLOCATION_FAILURE: Memory object allocation failure");
		case CL_OUT_OF_RESOURCES: return FCPPT_TEXT("CL_OUT_OF_RESOURCES: Out of resources");
		case CL_OUT_OF_HOST_MEMORY: return FCPPT_TEXT("CL_OUT_OF_HOST_MEMORY: Out of host memory");
		case CL_PROFILING_INFO_NOT_AVAILABLE: return FCPPT_TEXT("CL_PROFILING_INFO_NOT_AVAILABLE: Profiling information not available");
		case CL_MEM_COPY_OVERLAP: return FCPPT_TEXT("CL_MEM_COPY_OVERLAP: Memory copy overlap");
		case CL_IMAGE_FORMAT_MISMATCH: return FCPPT_TEXT("CL_IMAGE_FORMAT_MISMATCH: Image format mismatch");
		case CL_IMAGE_FORMAT_NOT_SUPPORTED: return FCPPT_TEXT("CL_IMAGE_FORMAT_NOT_SUPPORTED: Image format not supported");
		case CL_BUILD_PROGRAM_FAILURE: return FCPPT_TEXT("CL_BUILD_PROGRAM_FAILURE: Program build failure");
		case CL_MAP_FAILURE: return FCPPT_TEXT("CL_MAP_FAILURE: Map failure");
		case CL_INVALID_VALUE: return FCPPT_TEXT("CL_INVALID_VALUE: Invalid value");
		case CL_INVALID_DEVICE_TYPE: return FCPPT_TEXT("CL_INVALID_DEVICE_TYPE: Invalid device type");
		case CL_INVALID_PLATFORM: return FCPPT_TEXT("CL_INVALID_PLATFORM: Invalid platform");
		case CL_INVALID_DEVICE: return FCPPT_TEXT("CL_INVALID_DEVICE: Invalid device");
		case CL_INVALID_CONTEXT: return FCPPT_TEXT("CL_INVALID_CONTEXT: Invalid context");
		case CL_INVALID_QUEUE_PROPERTIES: return FCPPT_TEXT("CL_INVALID_QUEUE_PROPERTIES: Invalid queue properties");
		case CL_INVALID_COMMAND_QUEUE: return FCPPT_TEXT("CL_INVALID_COMMAND_QUEUE: Invalid command queue");
		case CL_INVALID_HOST_PTR: return FCPPT_TEXT("CL_INVALID_HOST_PTR: Invalid host pointer");
		case CL_INVALID_MEM_OBJECT: return FCPPT_TEXT("CL_INVALID_MEM_OBJECT: Invalid memory object");
		case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR: return FCPPT_TEXT("CL_INVALID_IMAGE_FORMAT_DESCRIPTOR: Invalid image format descriptor");
		case CL_INVALID_IMAGE_SIZE: return FCPPT_TEXT("CL_INVALID_IMAGE_SIZE: Invalid image size");
		case CL_INVALID_SAMPLER: return FCPPT_TEXT("CL_INVALID_SAMPLER: Invalid sampler");
		case CL_INVALID_BINARY: return FCPPT_TEXT("CL_INVALID_BINARY: Invalid binary");
		case CL_INVALID_BUILD_OPTIONS: return FCPPT_TEXT("CL_INVALID_BUILD_OPTIONS: Invalid build options");
		case CL_INVALID_PROGRAM: return FCPPT_TEXT("CL_INVALID_PROGRAM: Invalid program");
		case CL_INVALID_PROGRAM_EXECUTABLE: return FCPPT_TEXT("CL_INVALID_PROGRAM_EXECUTABLE: Invalid program executable");
		case CL_INVALID_KERNEL_NAME: return FCPPT_TEXT("CL_INVALID_KERNEL_NAME: Invalid kernel name");
		case CL_INVALID_KERNEL_DEFINITION: return FCPPT_TEXT("CL_INVALID_KERNEL_DEFINITION: Invalid kernel definition");
		case CL_INVALID_KERNEL: return FCPPT_TEXT("CL_INVALID_KERNEL: Invalid kernel");
		case CL_INVALID_ARG_INDEX: return FCPPT_TEXT("CL_INVALID_ARG_INDEX: Invalid argument index");
		case CL_INVALID_ARG_VALUE: return FCPPT_TEXT("CL_INVALID_ARG_VALUE: Invalid argument value");
		case CL_INVALID_ARG_SIZE: return FCPPT_TEXT("CL_INVALID_ARG_SIZE: Invalid argument size");
		case CL_INVALID_KERNEL_ARGS: return FCPPT_TEXT("CL_INVALID_KERNEL_ARGS: Invalid kernel arguments");
		case CL_INVALID_WORK_DIMENSION: return FCPPT_TEXT("CL_INVALID_WORK_DIMENSION: Invalid work dimension");
		case CL_INVALID_WORK_GROUP_SIZE: return FCPPT_TEXT("CL_INVALID_WORK_GROUP_SIZE: Invalid work group size");
		case CL_INVALID_WORK_ITEM_SIZE: return FCPPT_TEXT("CL_INVALID_WORK_ITEM_SIZE: Invalid work item size");
		case CL_INVALID_GLOBAL_OFFSET: return FCPPT_TEXT("CL_INVALID_GLOBAL_OFFSET: Invalid global offset");
		case CL_INVALID_EVENT_WAIT_LIST: return FCPPT_TEXT("CL_INVALID_EVENT_WAIT_LIST: Invalid event wait list");
		case CL_INVALID_EVENT: return FCPPT_TEXT("CL_INVALID_EVENT: Invalid event");
		case CL_INVALID_OPERATION: return FCPPT_TEXT("CL_INVALID_OPERATION: Invalid operation");
		case CL_INVALID_GL_OBJECT: return FCPPT_TEXT("CL_INVALID_GL_OBJECT: Invalid OpenGL object");
		case CL_INVALID_BUFFER_SIZE: return FCPPT_TEXT("CL_INVALID_BUFFER_SIZE: Invalid buffer size");
		case CL_INVALID_MIP_LEVEL: return FCPPT_TEXT("CL_INVALID_MIP_LEVEL: Invalid mip-map level");
		default: return FCPPT_TEXT("Unknown");
	}
}
}

void
sge::opencl::handle_error(
	cl_int const error_code,
	fcppt::string const &function_name)
{
	if(error_code != CL_SUCCESS)
	{
		throw
			sge::exception(
				FCPPT_TEXT("Function ")+
				function_name+
				FCPPT_TEXT(": ")+
				error_code_to_string(
					error_code));
	}
}
