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


#ifndef SGE_OPENCL_COMMAND_QUEUE_SCOPED_PLANAR_MAPPING_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_SCOPED_PLANAR_MAPPING_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/symbol.hpp>
#include <sge/opencl/command_queue/object_fwd.hpp>
#include <sge/opencl/memory_object/rect.hpp>
#include <sge/opencl/memory_object/image/planar_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opencl
{
namespace command_queue
{
class scoped_planar_mapping
{
FCPPT_NONCOPYABLE(
	scoped_planar_mapping);
public:
	SGE_OPENCL_SYMBOL explicit
	scoped_planar_mapping(
		command_queue::object &,
		opencl::memory_object::image::planar &,
		cl_map_flags,
		opencl::memory_object::rect const &);

	SGE_OPENCL_SYMBOL void*
	ptr() const;

	SGE_OPENCL_SYMBOL std::size_t
	pitch() const;

	SGE_OPENCL_SYMBOL sge::image2d::view::object const
	view();

	SGE_OPENCL_SYMBOL ~scoped_planar_mapping();
private:
	command_queue::object &queue_;
	opencl::memory_object::rect rect_;
	sge::image::color::format::type sge_image_format_;
	cl_mem image_;
	void *ptr_;
	std::size_t pitch_;
};
}
}
}

#endif
