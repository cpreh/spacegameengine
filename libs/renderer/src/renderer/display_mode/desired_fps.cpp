//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/display_mode/desired_fps.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/refresh_rate_value.hpp>
#include <fcppt/const.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/maybe.hpp>


sge::renderer::display_mode::refresh_rate_value
sge::renderer::display_mode::desired_fps(
	sge::renderer::display_mode::optional_object const &_opt_display_mode
)
{
	// TODO(philipp): Remove this
	constexpr sge::renderer::display_mode::refresh_rate_value const default_value{
		60
	};

	return
		fcppt::optional::maybe(
			fcppt::optional::bind(
				_opt_display_mode,
				[](
					sge::renderer::display_mode::object const &_display_mode
				)
				{
					return
						_display_mode.refresh_rate();
				}
			),
			fcppt::const_(
				default_value
			),
			[](
				sge::renderer::display_mode::refresh_rate const _rate
			)
			{
				return
					_rate.get();
			}
		);
}
