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


#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/memory_object/base.hpp>
#include <sge/opencl/memory_object/scoped_objects.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/src/opencl/handle_error.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>


sge::opencl::memory_object::scoped_objects::scoped_objects(
	command_queue::object &_queue,
	memory_object::base_ref_sequence const &_objects)
:
	queue_(
		_queue),
	objects_(
		_objects)
{
	FCPPT_ASSERT_PRE(
		!_objects.empty());

	glFinish();

	typedef
	fcppt::container::raw_vector<cl_mem>
	mem_vector;

	mem_vector impls;
	impls.reserve(
		static_cast<mem_vector::size_type>(
			_objects.size()));
	for(
		memory_object::base_ref_sequence::const_iterator it =
			_objects.begin();
		it != _objects.end();
		++it)
		impls.push_back(
			(*it)->impl());

	cl_int const error_code =
		clEnqueueAcquireGLObjects(
			_queue.impl(),
			static_cast<cl_uint>(
				impls.size()),
			impls.data(),
			0,
			0,
			0);
	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clEnqueueAcquireGLObjects"));
}

sge::opencl::memory_object::scoped_objects::~scoped_objects()
{
	typedef
	fcppt::container::raw_vector<cl_mem>
	mem_vector;

	mem_vector impls;
	impls.reserve(
		static_cast<mem_vector::size_type>(
			objects_.size()));
	for(
		memory_object::base_ref_sequence::const_iterator it =
			objects_.begin();
		it != objects_.end();
		++it)
		impls.push_back(
			(*it)->impl());

	cl_int error_code =
		clEnqueueReleaseGLObjects(
			queue_.impl(),
			static_cast<cl_uint>(
				impls.size()),
			impls.data(),
			0,
			0,
			0);
	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clReleaseAcquireGLObjects"));

	error_code =
		clFinish(
			queue_.impl());
	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clFinish"));
}
