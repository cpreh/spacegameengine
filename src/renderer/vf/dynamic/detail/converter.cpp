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


#include "converter.hpp"

namespace
{

template<
	typename Vector,
	typename Type
>
void
convert_if_color(
	Vector &_converters,
	Type const &_type,
	sge::renderer::size_type const _vertex_stride,
	sge::renderer::size_type const _offset
)
{
	if(
		fcppt::variant::holds_type<
			sge::renderer::vf::dynamic::color
		>(
			_type
		)
	)
		fcppt::container::ptr::push_back_unique_ptr(
			_converters,
			fcppt::make_unique_ptr<
				sge::renderer::vf::dynamic::detail::element_converter
			>(
				_type. template get<
					sge::renderer::vf::dynamic::color
				>(),
				_vertex_stride,
				_offset
			)
		);
}

}

sge::renderer::vf::dynamic::detail::converter::converter(
	dynamic::part const &_part,
	sge::image::algorithm::accepted_format_array const &_accepted_formats
)
:
	element_converters_()
{
	BOOST_FOREACH(
		renderer::vf::dynamic::ordered_element_list::const_reference elem,
		_part.elements()
	)
	{
		renderer::vf::dynamic::element const element(
			elem.element()
		);

		::convert_if_color(
			element_converters_,
			_accepted_formats,
			element.info(),
			_part.stride(),
			elem.offset()
		);

		if(
			fcppt::variant::holds_type<
				sge::renderer::vf::dynamic::unspecified
			>(
				element.info()
			)
		)
			::convert_if_color(
				element_converters_,
				_accepted_formats,
				element.info().get<
					renderer::vf::dynamic::unspecified
				>().type(),
				_part.stride(),
				elem.offset()
			);
	}
}

sge::renderer::vf::dynamic::detail::converter::~converter()
{
}

void
sge::renderer::vf::dynamic::detail::converter::convert(
	dynamic::locked_part const &_part,
	detail::lock_interval_set const &_intervals,
	bool const _unlock
)
{
	BOOST_FOREACH(
		detail::lock_interval_set::const_reference interval,
		_intervals
	)
		BOOST_FOREACH(
			element_vector::reference ref,
			elements_
		)
			ref->convert(
				interval,
				_part.data(),
				_unlock
			);
}
