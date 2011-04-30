/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_CEGUI_TOOLBOX_SCOPED_LAYOUT_HPP_INCLUDED
#define SGE_CEGUI_TOOLBOX_SCOPED_LAYOUT_HPP_INCLUDED

#include <sge/charconv/system_fwd.hpp>
#include <sge/cegui/symbol.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/noncopyable.hpp>

namespace CEGUI
{
class Window;
}

namespace sge
{
namespace cegui
{
namespace toolbox
{
class scoped_layout
{
FCPPT_NONCOPYABLE(
	scoped_layout);
public:
	SGE_CEGUI_SYMBOL explicit
	scoped_layout(
		fcppt::filesystem::path const &,
		sge::charconv::system &);

	SGE_CEGUI_SYMBOL ~scoped_layout();

	SGE_CEGUI_SYMBOL
	CEGUI::Window &
	window() const;
private:
	CEGUI::Window *const window_;
};
}
}
}

#endif
