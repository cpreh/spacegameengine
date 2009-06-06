/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#ifndef SGE_FONT_SYSTEM_HPP_INCLUDED
#define SGE_FONT_SYSTEM_HPP_INCLUDED

#include <sge/font/metrics_fwd.hpp>
#include <sge/font/size_type.hpp>
#include <sge/image/loader_fwd.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace font
{

class SGE_CLASS_SYMBOL system {
	SGE_NONCOPYABLE(system)
protected:
	SGE_SYMBOL system();
public:
	SGE_SYMBOL virtual ~system();

	virtual metrics_ptr const
	create_font(
		filesystem::path const &,
		size_type font_height,
		sge::image::loader_ptr
			= sge::image::loader_ptr()) = 0;
};

}
}

#endif
