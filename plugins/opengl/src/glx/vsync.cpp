//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/glx/current_drawable.hpp>
#include <sge/opengl/glx/swap_functions.hpp>
#include <sge/opengl/glx/vsync.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/const.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/maybe.hpp>


void
sge::opengl::glx::vsync(
	fcppt::log::object &_log,
	sge::opengl::glx::swap_functions const &_swap_functions,
	awl::backends::x11::display &_display
)
{
	// prefer swap_interval_ext
	if(
		fcppt::optional::maybe(
			_swap_functions.swap_interval_ext(),
			fcppt::const_(
				false
			),
			[
				&_log,
				&_display
			](
				sge::opengl::glx::swap_functions::glx_swap_interval_ext_ref const _swap
			)
			{
				FCPPT_LOG_INFO(
					_log,
					fcppt::log::out
						<< FCPPT_TEXT("Using glXSwapIntervalExt")
				)

				_swap.get()(
					_display.get(),
					sge::opengl::glx::current_drawable(),
					1
				);

				return
					true;
			}
		)
	)
		return;

	if(
		fcppt::optional::maybe(
			_swap_functions.swap_interval_sgi(),
			fcppt::const_(
				false
			),
			[
				&_log
			](
				sge::opengl::glx::swap_functions::glx_swap_interval_sgi_ref const _swap
			)
			{
				FCPPT_LOG_INFO(
					_log,
					fcppt::log::out
						<< FCPPT_TEXT("Using glXSwapIntervalSGI")
				)

				if(
					_swap.get()(
						1
					)
					!= 0
				)
					throw
						sge::renderer::exception{
							FCPPT_TEXT("Setting the swap interval via SGI returned an error!")
						};

				return
					true;
			}
		)
	)
		return;

	FCPPT_LOG_ERROR(
		_log,
		fcppt::log::out
			<< FCPPT_TEXT("Setting vsync is not supported.")
	)
}
