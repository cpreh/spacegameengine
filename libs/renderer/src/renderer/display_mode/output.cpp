//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/display_mode/dimensions.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/output.hpp>
#include <sge/renderer/display_mode/refresh_rate.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/optional/maybe_void.hpp>


fcppt::io::ostream &
sge::renderer::display_mode::operator<<(
	fcppt::io::ostream &_stream,
	sge::renderer::display_mode::object const &_mode
)
{
	_stream
		<< FCPPT_TEXT('(')
		<< _mode.pixel_size().get()
		<< FCPPT_TEXT("),(");

	fcppt::optional::maybe_void(
		_mode.dimensions(),
		[
			&_stream
		](
			sge::renderer::display_mode::dimensions const _dim
		)
		{
			_stream
				<< _dim;
		}
	);

	_stream
		<< FCPPT_TEXT(")@");

	fcppt::optional::maybe_void(
		_mode.refresh_rate(),
		[
			&_stream
		](
			sge::renderer::display_mode::refresh_rate const _rate
		)
		{
			_stream
				<< _rate;
		}
	);

	_stream
		<< FCPPT_TEXT(')');

	return
		_stream;
}
