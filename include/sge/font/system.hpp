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

#include <sge/font/system_fwd.hpp>
#include <sge/font/metrics_ptr.hpp>
#include <sge/font/size_type.hpp>
#include <sge/image/multi_loader_fwd.hpp>
#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace font
{

class SGE_CLASS_SYMBOL system
{
	FCPPT_NONCOPYABLE(system)
protected:
	SGE_SYMBOL system();
public:
	SGE_SYMBOL virtual ~system();

	virtual metrics_ptr const
	create_font(
		fcppt::filesystem::path const &,
		size_type font_height,
		sge::image::multi_loader const * = 0
	) = 0;
};

}
}

#endif
