//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version.hpp>

#undef major
#undef minor

sge::opengl::info::version::version(
	sge::opengl::info::major_version const _major,
	sge::opengl::info::minor_version const _minor
)
:
	major_{
		_major
	},
	minor_{
		_minor
	}
{
}

sge::opengl::info::major_version
sge::opengl::info::version::major() const
{
	return
		major_;
}

sge::opengl::info::minor_version
sge::opengl::info::version::minor() const
{
	return
		minor_;
}
