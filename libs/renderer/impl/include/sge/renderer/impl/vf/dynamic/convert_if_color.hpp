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


#ifndef SGE_RENDERER_IMPL_VF_DYNAMIC_CONVERT_IF_COLOR_HPP_INCLUDED
#define SGE_RENDERER_IMPL_VF_DYNAMIC_CONVERT_IF_COLOR_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/renderer/vf/dynamic/color.hpp>
#include <sge/renderer/vf/dynamic/color_format_vector.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <sge/renderer/impl/vf/dynamic/element_converter.hpp>
#include <sge/renderer/impl/vf/dynamic/element_converter_vector.hpp>
#include <sge/renderer/impl/vf/dynamic/matching_color_format.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/variant/to_optional.hpp>


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

template<
	typename Variant
>
void
convert_if_color(
	sge::renderer::impl::vf::dynamic::element_converter_vector &_converters,
	Variant const &_variant,
	sge::renderer::vf::dynamic::color_format_vector const &_formats,
	sge::renderer::vf::dynamic::stride const _stride,
	sge::renderer::vf::dynamic::offset const _offset
)
{
	fcppt::optional::maybe_void(
		fcppt::variant::to_optional<
			sge::renderer::vf::dynamic::color
		>(
			_variant
		),
		[
			&_converters,
			&_formats,
			_stride,
			_offset
		](
			sge::renderer::vf::dynamic::color const &_color
		)
		{
			sge::image::color::format const format(
				_color.color_format()
			);

			_converters.push_back(
				sge::renderer::impl::vf::dynamic::element_converter{
					format,
					sge::renderer::impl::vf::dynamic::matching_color_format(
						format,
						_formats
					),
					_stride,
					_offset
				}
			);
		}
	);
}

}
}
}
}
}

#endif
