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


#ifndef SGE_SRC_RENDERER_VF_DYNAMIC_DETAIL_ELEMENT_CONVERTER_HPP_INCLUDED
#define SGE_SRC_RENDERER_VF_DYNAMIC_DETAIL_ELEMENT_CONVERTER_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <sge/src/renderer/vf/dynamic/detail/element_converter_fwd.hpp>
#include <sge/src/renderer/vf/dynamic/detail/lock_interval.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{
namespace detail
{

class element_converter
{
public:
	element_converter(
		sge::image::color::format original_color,
		sge::image::color::format backend_color,
		sge::renderer::vf::dynamic::stride,
		sge::renderer::vf::dynamic::offset
	);

	void
	convert(
		sge::renderer::vf::dynamic::detail::lock_interval const &,
		sge::renderer::raw_pointer data,
		sge::renderer::vertex::first,
		bool unlock
	);
private:
	sge::image::color::format
		original_color_,
		backend_color_;

	sge::renderer::vf::dynamic::stride stride_;

	sge::renderer::vf::dynamic::offset offset_;
};

}
}
}
}
}

#endif
