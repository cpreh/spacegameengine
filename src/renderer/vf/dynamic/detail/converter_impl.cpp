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


#include "converter_impl.hpp"
#include "element_converter.hpp"
#include <sge/image/color/format.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/renderer/vf/dynamic/color.hpp>
#include <sge/renderer/vf/dynamic/color_format_vector.hpp>
#include <sge/renderer/vf/dynamic/locked_part.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/algorithm/contains.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>

namespace
{

sge::image::color::format::type
matching_format(
	sge::image::color::format::type const _format,
	sge::renderer::vf::dynamic::color_format_vector const &_formats
)
{
	if(
		fcppt::algorithm::contains(
			_formats,
			_format
		)
	)
		return _format;

	for(
		sge::renderer::vf::dynamic::color_format_vector::const_iterator format_it(
			_formats.begin()
		);
		format_it != _formats.end();
		++format_it
	)
	{
		sge::renderer::vf::dynamic::color_format_vector::value_type const value(
			*format_it
		);

		if(
			sge::image::color::format_stride(
				_format
			)
			==
			sge::image::color::format_stride(
				value
			)
		)
			return value;
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid vertex color!") // TODO: error message!
	);
}

template<
	typename Vector,
	typename Type
>
void
convert_if_color(
	Vector &_converters,
	Type const &_type,
	sge::renderer::vf::dynamic::color_format_vector const &_formats,
	sge::renderer::size_type const _vertex_stride,
	sge::renderer::size_type const _offset
)
{
	if(
		!fcppt::variant::holds_type<
			sge::renderer::vf::dynamic::color
		>(
			_type
		)
	)
		return;

	sge::image::color::format::type const format(
		_type. template get<
			sge::renderer::vf::dynamic::color
		>().color_format()
	);
		
	fcppt::container::ptr::push_back_unique_ptr(
		_converters,
		fcppt::make_unique_ptr<
			sge::renderer::vf::dynamic::detail::element_converter
		>(
			format,
			matching_format(
				format,
				_formats
			),
			_vertex_stride,
			_offset
		)
	);
}

}

sge::renderer::vf::dynamic::detail::converter_impl::converter_impl(
	dynamic::part const &_part,
	dynamic::color_format_vector const &_accepted_formats
)
:
	element_converters_()
{
	
	renderer::vf::dynamic::ordered_element_list const &elements(
		_part.elements()
	);

	for(
		renderer::vf::dynamic::ordered_element_list::const_iterator elem_it(
			elements.begin()
		);
		elem_it != elements.end();
		++elem_it
	)
	{
		renderer::vf::dynamic::element const element(
			elem_it->element()
		);

		::convert_if_color(
			element_converters_,
			element.info(),
			_accepted_formats,
			_part.stride(),
			elem_it->offset()
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
				element.info().get<
					renderer::vf::dynamic::unspecified
				>().type(),
				_accepted_formats,
				_part.stride(),
				elem_it->offset()
			);
	}
}

sge::renderer::vf::dynamic::detail::converter_impl::~converter_impl()
{
}

void
sge::renderer::vf::dynamic::detail::converter_impl::convert_lock(
	renderer::raw_pointer const _data,
	renderer::size_type const _pos,
	detail::lock_interval_set const &_intervals,
	detail::lock_interval const &_current_lock
)
{
	detail::lock_interval_set const new_lock(
		_intervals & _current_lock
	);

	for(
		detail::lock_interval_set::const_iterator interval_it(
			new_lock.begin()
		);
		interval_it != new_lock.end();
		++interval_it
	)
		this->do_convert(
			_data,
			_pos,
			*interval_it,
			false
		);
}

void
sge::renderer::vf::dynamic::detail::converter_impl::convert_unlock(
	renderer::raw_pointer const _data,
	renderer::size_type const _pos,
	detail::lock_interval const &_current_lock
)
{
	this->do_convert(
		_data,
		_pos,
		_current_lock,
		true
	);
}

void
sge::renderer::vf::dynamic::detail::converter_impl::do_convert(
	renderer::raw_pointer const _data,
	renderer::size_type const _pos,
	detail::lock_interval const &_interval,
	bool const _unlock
)
{
	for(
		element_converter_vector::iterator it(
			element_converters_.begin()
		);
		it != element_converters_.end();
		++it
	)
		it->convert(
			_interval,
			_data,
			_pos,
			_unlock
		);
}
