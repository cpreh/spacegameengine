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


#include <sge/image/mizuiro_color.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/impl/instantiate_format.hpp>
#include <sge/src/core/export_function_instantiation.hpp>


template<
	typename Element,
	typename
>
sge::image::color::any::object::object(
	Element const &_element
)
:
	variant_(
		_element
	)
{
}

sge::image::color::any::object::object(
	sge::image::color::any::object const &
)
=
default;

sge::image::color::any::object &
sge::image::color::any::object::operator=(
	sge::image::color::any::object const &
)
=
default;

sge::image::color::any::object::~object()
{
}

sge::image::color::any::object::variant const &
sge::image::color::any::object::get() const
{
	return
		variant_;
}

#define SGE_IMAGE_COLOR_ANY_OBJECT_INSTANTIATE_CTOR(\
	format_arg, \
	_\
)\
template \
SGE_CORE_EXPORT_FUNCTION_INSTANTIATION \
sge::image::color::any::object::object( \
	sge::image::mizuiro_color<\
		sge::image::color:: format_arg ## _format \
	> const & \
)

SGE_IMAGE_COLOR_IMPL_INSTANTIATE_FORMAT(
	SGE_IMAGE_COLOR_ANY_OBJECT_INSTANTIATE_CTOR,
	_
);

#undef SGE_IMAGE_COLOR_ANY_OBJECT_INSTANTIATE_CTOR
