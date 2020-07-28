//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EGL_VERSION_HPP_INCLUDED
#define SGE_OPENGL_EGL_VERSION_HPP_INCLUDED

#include <sge/opengl/egl/major_version.hpp>
#include <sge/opengl/egl/minor_version.hpp>
#include <sge/opengl/egl/version_fwd.hpp>

#undef major
#undef minor

namespace sge
{
namespace opengl
{
namespace egl
{

class version
{
public:
	version(
		sge::opengl::egl::major_version,
		sge::opengl::egl::minor_version
	);

	[[nodiscard]]
	sge::opengl::egl::major_version
	major() const;

	[[nodiscard]]
	sge::opengl::egl::minor_version
	minor() const;
private:
	sge::opengl::egl::major_version major_;

	sge::opengl::egl::minor_version minor_;
};

}
}
}

#endif
