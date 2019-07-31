//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/xrandr/version.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

#undef major
#undef minor


sge::opengl::xrandr::version::version(
	int const _major,
	int const _minor
)
:
	major_(
		_major
	),
	minor_(
		_minor
	)
{
}

int
sge::opengl::xrandr::version::major() const
{
	return
		major_;
}

int
sge::opengl::xrandr::version::minor() const
{
	return
		minor_;
}

bool
sge::opengl::xrandr::operator<(
	sge::opengl::xrandr::version const &_left,
	sge::opengl::xrandr::version const &_right
)
{
	auto const to_pair(
		[](
			sge::opengl::xrandr::version const &_version
		)
		{
			return
				std::make_pair(
					_version.major(),
					_version.minor()
				);
		}
	);

	return
		to_pair(
			_left
		)
		<
		to_pair(
			_right
		);
}

fcppt::io::ostream &
sge::opengl::xrandr::operator<<(
	fcppt::io::ostream &_stream,
	sge::opengl::xrandr::version const &_version
)
{
	return
		_stream
		<<
		_version.major()
		<<
		FCPPT_TEXT('.')
		<<
		_version.minor();
}
