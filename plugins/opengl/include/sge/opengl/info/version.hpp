//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_INFO_VERSION_HPP_INCLUDED
#define SGE_OPENGL_INFO_VERSION_HPP_INCLUDED

#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_fwd.hpp>

#undef major
#undef minor

namespace sge::opengl::info
{

class version
{
public:
	version(
		sge::opengl::info::major_version,
		sge::opengl::info::minor_version
	);

	[[nodiscard]]
	sge::opengl::info::major_version
	major() const;

	[[nodiscard]]
	sge::opengl::info::minor_version
	minor() const;
private:
	sge::opengl::info::major_version major_;

	sge::opengl::info::minor_version minor_;
};

}

#endif
