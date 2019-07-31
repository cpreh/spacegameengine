//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/egl/version.hpp>
#include <sge/opengl/egl/version_output.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/ostream.hpp>


fcppt::io::ostream &
sge::opengl::egl::operator<<(
	fcppt::io::ostream &_stream,
	sge::opengl::egl::version const &_version
)
{
	return
		_stream
			<< _version.major()
			<< FCPPT_TEXT('.')
			<< _version.minor();
}
