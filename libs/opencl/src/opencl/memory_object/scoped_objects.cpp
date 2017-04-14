/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/impl/handle_error.hpp>
#include <sge/opencl/memory_object/base.hpp>
#include <sge/opencl/memory_object/scoped_objects.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


sge::opencl::memory_object::scoped_objects::scoped_objects(
	sge::opencl::command_queue::object &_queue,
	sge::opencl::memory_object::base_ref_sequence const &_objects)
:
	queue_(
		_queue
	),
	objects_(
		_objects
	)
{
	FCPPT_ASSERT_PRE(
		!_objects.empty());

	glFinish();

	typedef
	std::vector<
		cl_mem
	>
	mem_vector;

	mem_vector const impls(
		fcppt::algorithm::map<
			mem_vector
		>(
			_objects,
			[](
				fcppt::reference<
					sge::opencl::memory_object::base
				> const _ref
			)
			{
				return
					_ref.get().impl();
			}
		)
	);

	cl_int const error_code{
		clEnqueueAcquireGLObjects(
			_queue.impl(),
			fcppt::cast::size<
				cl_uint
			>(
				impls.size()
			),
			impls.data(),
			0,
			nullptr,
			nullptr
		)
	};

	sge::opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clEnqueueAcquireGLObjects")
	);
}

sge::opencl::memory_object::scoped_objects::~scoped_objects()
{
	typedef
	std::vector<
		cl_mem
	>
	mem_vector;

	mem_vector const impls(
		fcppt::algorithm::map<
			mem_vector
		>(
			objects_,
			[](
				fcppt::reference<
					sge::opencl::memory_object::base
				> const _ref
			)
			{
				return
					_ref.get().impl();
			}
		)
	);

	cl_int error_code =
		clEnqueueReleaseGLObjects(
			queue_.impl(),
			fcppt::cast::size<
				cl_uint
			>(
				impls.size()
			),
			impls.data(),
			0,
			nullptr,
			nullptr
		);

	sge::opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clReleaseAcquireGLObjects")
	);

	error_code =
		clFinish(
			queue_.impl()
		);

	sge::opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clFinish")
	);
}
