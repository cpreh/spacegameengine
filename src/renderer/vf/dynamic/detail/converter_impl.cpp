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
#include <sge/src/renderer/vf/dynamic/detail/element_converter.hpp>
#include <sge/src/renderer/vf/dynamic/detail/lock_interval.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/variant/to_optional.hpp>


sge::renderer::vf::dynamic::detail::converter_impl::converter_impl(
	sge::renderer::vf::dynamic::part const &_part,
	sge::renderer::vf::dynamic::color_format_vector const &_accepted_formats
)
:
	element_converters_()
{

	for(
		sge::renderer::vf::dynamic::ordered_element const &elem
		:
		_part.elements()
	)
	{
		sge::renderer::vf::dynamic::element const element(
			elem.element()
		);

		sge::renderer::vf::dynamic::detail::convert_if_color(
			element_converters_,
			element.info(),
			_accepted_formats,
			_part.stride(),
			elem.offset()
		);

		fcppt::optional::maybe_void(
			fcppt::variant::to_optional<
				sge::renderer::vf::dynamic::extra
			>(
				element.info()
			),
			[
				&_accepted_formats,
				&_part,
				&elem,
				this
			](
				sge::renderer::vf::dynamic::extra const &_extra
			)
			{
				sge::renderer::vf::dynamic::detail::convert_if_color(
					element_converters_,
					_extra.type(),
					_accepted_formats,
					_part.stride(),
					elem.offset()
				);
			}
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
	for(
		sge::renderer::vf::dynamic::detail::lock_interval const &interval
		:
		(_intervals & _current_lock)
	)
		this->do_convert(
			_data,
			_pos,
			interval,
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
		sge::renderer::vf::dynamic::detail::element_converter &conv
		:
		element_converters_
	)
		conv.convert(
			_interval,
			_data,
			_pos,
			_unlock
		);
}
