/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_IMAGE_COLOR_DYNAMIC_FORMAT_OBJECT_DECL_HPP_INCLUDED
#define SGE_SRC_IMAGE_COLOR_DYNAMIC_FORMAT_OBJECT_DECL_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/src/image/color/dynamic/available_layouts.hpp>
#include <sge/src/image/color/dynamic/format_object_base.hpp>
#include <sge/src/image/color/dynamic/format_object_fwd.hpp>
#include <mizuiro/color/homogenous_dynamic_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace dynamic
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename BaseType,
	unsigned NumChannels
>
class format_object
:
	public
	sge::image::color::dynamic::format_object_base<
		BaseType,
		NumChannels
	>::type
{
	FCPPT_NONCOPYABLE(
		format_object
	);
public:
	typedef typename sge::image::color::dynamic::format_object_base<
		BaseType,
		NumChannels
	>::type base;

	typedef typename base::channel_array channel_array;

	typedef sge::image::color::dynamic::available_layouts::type layout_enum;

	typedef sge::image::color::format color_format_type;

	format_object(
		channel_array const &,
		layout_enum,
		color_format_type
	);

	~format_object();

	layout_enum const layout_type;

	color_format_type const color_format;
};

FCPPT_PP_POP_WARNING

}
}
}
}

#endif
