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


#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vf/dynamic/color_format_vector.hpp>
#include <sge/renderer/vf/dynamic/extra.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <sge/renderer/vf/dynamic/detail/lock_interval_set.hpp>
#include <sge/src/renderer/vf/dynamic/detail/convert_if_color.hpp>
#include <sge/src/renderer/vf/dynamic/detail/converter_impl.hpp>
#include <sge/src/renderer/vf/dynamic/detail/element_converter_vector.hpp>
#include <sge/src/renderer/vf/dynamic/detail/lock_interval.hpp>
#include <fcppt/variant/holds_type.hpp>


sge::renderer::vf::dynamic::detail::converter_impl::converter_impl(
	sge::renderer::vf::dynamic::part const &_part,
	sge::renderer::vf::dynamic::color_format_vector const &_accepted_formats
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

		sge::renderer::vf::dynamic::detail::convert_if_color(
			element_converters_,
			element.info(),
			_accepted_formats,
			_part.stride(),
			elem_it->offset()
		);

		if(
			fcppt::variant::holds_type<
				sge::renderer::vf::dynamic::extra
			>(
				element.info()
			)
		)
			sge::renderer::vf::dynamic::detail::convert_if_color(
				element_converters_,
				element.info().get<
					sge::renderer::vf::dynamic::extra
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
	sge::renderer::raw_pointer const _data,
	sge::renderer::vertex::first const _pos,
	sge::renderer::vf::dynamic::detail::lock_interval_set const &_intervals,
	sge::renderer::vf::dynamic::detail::lock_interval const &_current_lock
)
{
	sge::renderer::vf::dynamic::detail::lock_interval_set const new_lock(
		_intervals & _current_lock
	);

	for(
		sge::renderer::vf::dynamic::detail::lock_interval_set::const_iterator interval_it(
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
	sge::renderer::raw_pointer const _data,
	sge::renderer::vertex::first const _pos,
	sge::renderer::vf::dynamic::detail::lock_interval const &_current_lock
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
	sge::renderer::raw_pointer const _data,
	sge::renderer::vertex::first const _pos,
	sge::renderer::vf::dynamic::detail::lock_interval const &_interval,
	bool const _unlock
)
{
	for(
		sge::renderer::vf::dynamic::detail::element_converter_vector::iterator it(
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
