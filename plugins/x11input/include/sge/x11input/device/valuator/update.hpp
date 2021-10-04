//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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


namespace sge::x11input::device::valuator
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

#endif
