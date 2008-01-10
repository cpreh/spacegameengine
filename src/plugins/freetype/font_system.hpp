/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_FT_FONT_SYSTEM_HPP_INCLUDED
#define SGE_FT_FONT_SYSTEM_HPP_INCLUDED

#include <map>
#include <utility>

#include <boost/weak_ptr.hpp>

#include "../../font/font_system.hpp"
#include "../../font/font_metrics.hpp"
#include "library.hpp"

namespace sge
{
namespace ft
{

class font_system : public sge::font_system {
public:
	const font_metrics_ptr create_font(const path& font_name,
	                                   unsigned font_size);
private:
	library _library;
	typedef std::map<std::pair<unsigned, path>, boost::weak_ptr<font_metrics> > loaded_fonts_list;
	loaded_fonts_list loaded_fonts;
};

}
}

#endif

