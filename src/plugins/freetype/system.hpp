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


#ifndef SGE_FT_SYSTEM_HPP_INCLUDED
#define SGE_FT_SYSTEM_HPP_INCLUDED

#include "library.hpp"
#include <sge/path.hpp>
#include <sge/font/system.hpp>
#include <sge/font/metrics.hpp>
#include <boost/weak_ptr.hpp>
#include <map>
#include <utility>

namespace sge
{
namespace ft
{

class system : public font::system {
public:
	const font::metrics_ptr
	create_font(
		const path& font_name,
		font::size_type font_size);
private:
	library library_;
	typedef std::map<
		std::pair<font::size_type, path>,
		boost::weak_ptr<font::metrics>
	> loaded_fonts_list;
	loaded_fonts_list loaded_fonts;
};

}
}

#endif

