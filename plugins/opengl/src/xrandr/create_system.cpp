//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/xrandr/create_system.hpp>
#include <sge/opengl/xrandr/extension.hpp>
#include <sge/opengl/xrandr/get_extension.hpp>
#include <sge/opengl/xrandr/get_version.hpp>
#include <sge/opengl/xrandr/optional_system_unique_ptr.hpp>
#include <sge/opengl/xrandr/system.hpp>
#include <sge/opengl/xrandr/version.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/maybe.hpp>


sge::opengl::xrandr::optional_system_unique_ptr
sge::opengl::xrandr::create_system(
	fcppt::log::object &_log,
	awl::backends::x11::display &_display
)
{
	return
		fcppt::optional::maybe(
			sge::opengl::xrandr::get_extension(
				_display
			),
			[
				&_log
			]{
				FCPPT_LOG_WARNING(
					_log,
					fcppt::log::out
						<< FCPPT_TEXT("xrandr extension not found")
				)

				return
					sge::opengl::xrandr::optional_system_unique_ptr();
			},
			[
				&_log,
				&_display
			](
				sge::opengl::xrandr::extension const _extension
			)
			{
				sge::opengl::xrandr::version const version(
					sge::opengl::xrandr::get_version(
						_extension,
						_display
					)
				);

				if(
					version
					<
					sge::opengl::xrandr::version(
						1,
						3
					)
				)
				{
					FCPPT_LOG_WARNING(
						_log,
						fcppt::log::out
							<< FCPPT_TEXT("xrandr version ")
							<< version
							<< FCPPT_TEXT(" too old")
					)

					return
						sge::opengl::xrandr::optional_system_unique_ptr();
				}

				return
					sge::opengl::xrandr::optional_system_unique_ptr(
						fcppt::make_unique_ptr<
							sge::opengl::xrandr::system
						>(
							_extension
						)
					);
			}
		);
}
