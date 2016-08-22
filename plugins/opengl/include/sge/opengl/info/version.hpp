/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OPENGL_INFO_VERSION_HPP_INCLUDED
#define SGE_OPENGL_INFO_VERSION_HPP_INCLUDED

#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_fwd.hpp>

#undef major
#undef minor

namespace sge
{
namespace opengl
{
namespace info
{

class version
{
public:
	version(
		sge::opengl::info::major_version,
		sge::opengl::info::minor_version
	);

	sge::opengl::info::major_version
	major() const;

	sge::opengl::info::minor_version
	minor() const;
private:
	sge::opengl::info::major_version major_;

	sge::opengl::info::minor_version minor_;
};

}
}
}

#endif
