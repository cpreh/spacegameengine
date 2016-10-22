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


#ifndef SGE_RENDERER_IMPL_VF_DYNAMIC_ELEMENT_CONVERTER_HPP_INCLUDED
#define SGE_RENDERER_IMPL_VF_DYNAMIC_ELEMENT_CONVERTER_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/impl/vf/dynamic/element_converter_fwd.hpp>
#include <sge/renderer/impl/vf/dynamic/lock_interval.hpp>
#include <sge/renderer/impl/vf/dynamic/unlock.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace renderer
{
namespace impl
{
namespace vf
{
namespace dynamic
{

class element_converter
{
public:
	FCPPT_MAKE_STRONG_TYPEDEF(
		sge::image::color::format,
		original_format
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		sge::image::color::format,
		backend_format
	);

	element_converter(
		original_format,
		backend_format,
		sge::renderer::vf::dynamic::stride,
		sge::renderer::vf::dynamic::offset
	);

	void
	convert(
		sge::renderer::impl::vf::dynamic::lock_interval const &,
		sge::renderer::raw_pointer data,
		sge::renderer::vertex::first,
		sge::renderer::impl::vf::dynamic::unlock
	) const;
private:
	original_format original_format_;

	backend_format backend_format_;

	sge::renderer::vf::dynamic::stride stride_;

	sge::renderer::vf::dynamic::offset offset_;
};

}
}
}
}
}

#endif
