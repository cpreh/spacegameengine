//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_VERSION_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_VERSION_HPP_INCLUDED

#include <sge/opengl/xrandr/version_fwd.hpp>
#include <fcppt/io/ostream_fwd.hpp>

#undef major
#undef minor

namespace sge
{
namespace opengl
{
namespace xrandr
{

class version
{
public:
	version(
		int major,
		int minor
	);

	[[nodiscard]]
	int
	major() const;

	[[nodiscard]]
	int
	minor() const;
private:
	int major_;

	int minor_;
};

bool
operator<(
	sge::opengl::xrandr::version const &,
	sge::opengl::xrandr::version const &
);

fcppt::io::ostream &
operator<<(
	fcppt::io::ostream &,
	sge::opengl::xrandr::version const &
);

}
}
}

#endif
