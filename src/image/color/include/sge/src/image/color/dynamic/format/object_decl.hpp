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


#ifndef SGE_SRC_IMAGE_COLOR_DYNAMIC_FORMAT_OBJECT_DECL_HPP_INCLUDED
#define SGE_SRC_IMAGE_COLOR_DYNAMIC_FORMAT_OBJECT_DECL_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/src/image/color/dynamic/format/object_base_decl.hpp>
#include <sge/src/image/color/dynamic/format/object_fwd.hpp>
#include <mizuiro/size_type.hpp>
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
namespace format
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Space,
	typename BaseType,
	mizuiro::size_type NumChannels
>
class object final
:
	public
	sge::image::color::dynamic::format::object_base<
		Space,
		BaseType,
		NumChannels
	>
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	typedef
	sge::image::color::dynamic::format::object_base<
		Space,
		BaseType,
		NumChannels
	>
	base;

	typedef
	sge::image::color::format
	color_format_type;

	template<
		typename Layout
	>
	object(
		Layout const &,
		color_format_type
	);

	~object();

	color_format_type const color_format;
};

FCPPT_PP_POP_WARNING

}
}
}
}
}

#endif
