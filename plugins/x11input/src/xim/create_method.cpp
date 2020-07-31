//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/exception.hpp>
#include <sge/x11input/xim/create_method.hpp>
#include <sge/x11input/xim/lc_ctype.hpp>
#include <sge/x11input/xim/method.hpp>
#include <sge/x11input/xim/method_unique_ptr.hpp>
#include <sge/x11input/xim/scoped_locale.hpp>
#include <awl/backends/x11/display_ref.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <string>
#include <fcppt/config/external_end.hpp>


sge::x11input::xim::method_unique_ptr
sge::x11input::xim::create_method(
	fcppt::log::object &_log,
	awl::backends::x11::display_ref const _display
)
{
	return
		fcppt::optional::maybe(
			sge::x11input::xim::lc_ctype(),
			[
				&_display,
				&_log
			]{
				FCPPT_LOG_WARNING(
					_log,
					fcppt::log::out
						<< FCPPT_TEXT("LC_CTYPE is not set.")
						<< FCPPT_TEXT(" Character conversion of X11 will not work properly!")
				)

				return
					fcppt::make_unique_ptr<
						sge::x11input::xim::method
					>(
						_display
					);
			},
			[
				&_display
			](
				std::string const &_locale_name
			)
			{
				sge::x11input::xim::scoped_locale const temp_locale(
					_locale_name
				);

				if(
					::XSupportsLocale()
					==
					False
				)
				{
					throw
						sge::input::exception{
							FCPPT_TEXT("X doesn't support the locale ")
							+
							fcppt::from_std_string(
								_locale_name
							)
						};
				}

				if(
					::XSetLocaleModifiers(
						"" // XMODIFIERS are appended automatically
					)
					==
					nullptr
				)
				{
					throw
						sge::input::exception{
							FCPPT_TEXT("XSetLocaleModifiers() failed!")
						};
				}

				return
					fcppt::make_unique_ptr<
						sge::x11input::xim::method
					>(
						_display
					);
			}
		);
}
