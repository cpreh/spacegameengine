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


#ifndef SGE_X11INPUT_DEVICE_VALUATOR_UPDATE_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_VALUATOR_UPDATE_HPP_INCLUDED

#include <sge/x11input/device/valuator/absolute.hpp>
#include <sge/x11input/device/valuator/accu.hpp>
#include <sge/x11input/device/valuator/any.hpp>
#include <sge/x11input/device/valuator/relative.hpp>
#include <sge/x11input/device/valuator/update_accu.hpp>
#include <sge/x11input/device/valuator/value.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace device
{
namespace valuator
{

template<
	typename Result
>
std::pair<
	Result,
	sge::x11input::device::valuator::any
>
update(
	sge::x11input::device::valuator::any const &_any,
	sge::x11input::device::valuator::value const _value
)
{
	return
		fcppt::variant::match(
			_any,
			[
				_value
			](
				sge::x11input::device::valuator::absolute const _absolute
			)
			{

				std::pair<
					Result,
					sge::x11input::device::valuator::accu
				> const result{
					sge::x11input::device::valuator::update_accu<
						Result
					>(
						sge::x11input::device::valuator::accu{
							0.
						},
						_value
						-
						_absolute.previous()
					)
				};

				return
					std::make_pair(
						result.first,
						sge::x11input::device::valuator::any{
							sge::x11input::device::valuator::absolute{
								result.first
								!=
								0
								?
									_value
								:
									_absolute.previous()
							}
						}
					);
			},
			[
				_value
			](
				sge::x11input::device::valuator::relative const _relative
			)
			{
				std::pair<
					Result,
					sge::x11input::device::valuator::accu
				> const result{
					sge::x11input::device::valuator::update_accu<
						Result
					>(
						_relative.accu(),
						_value
					)
				};

				return
					std::make_pair(
						result.first,
						sge::x11input::device::valuator::any{
							sge::x11input::device::valuator::relative{
								result.second
							}
						}
					);
			}
		);
}

}
}
}
}

#endif
