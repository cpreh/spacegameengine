/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENCL_MEMORY_OBJECT_IMAGE_PLANAR_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_IMAGE_PLANAR_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/dim2.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/memory_object/base.hpp>
#include <sge/opencl/memory_object/flags_field.hpp>
#include <sge/opencl/memory_object/image/planar_pitch.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/dim/object_impl.hpp>


namespace sge
{
namespace opencl
{
namespace memory_object
{
namespace image
{
class SGE_CORE_DETAIL_CLASS_SYMBOL planar
:
	public memory_object::base
{
FCPPT_NONCOPYABLE(
	planar);
public:
	SGE_OPENCL_DETAIL_SYMBOL
	planar(
		sge::opencl::context::object &,
		sge::opencl::memory_object::flags_field const &,
		cl_image_format const &,
		sge::opencl::dim2 const &size,
		sge::opencl::memory_object::image::planar_pitch const &);

	SGE_OPENCL_DETAIL_SYMBOL
	planar(
		sge::opencl::context::object &,
		sge::opencl::memory_object::flags_field const &,
		sge::renderer::texture::planar &);

	SGE_OPENCL_DETAIL_SYMBOL cl_mem
	impl()
	override;

	SGE_OPENCL_DETAIL_SYMBOL cl_image_format const &
	image_format() const;

	SGE_OPENCL_DETAIL_SYMBOL sge::opencl::dim2 const &
	size() const;

	SGE_OPENCL_DETAIL_SYMBOL ~planar()
	override;
private:
	cl_mem impl_;
	cl_image_format image_format_;
	sge::opencl::dim2 size_;
};
}
}
}
}

#endif
