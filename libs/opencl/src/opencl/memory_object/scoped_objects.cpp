//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
