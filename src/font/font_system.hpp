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


#ifndef SGE_FONT_SYSTEM_HPP_INCLUDED
#define SGE_FONT_SYSTEM_HPP_INCLUDED

#include "../string.hpp"
#include "../path.hpp"
#include "../shared_ptr.hpp"
#include "../plugin_traits.hpp"
#include "../export.hpp"
#include "font_types.hpp"
#include "font_metrics.hpp"

namespace sge
{

class font_system {
public:
	virtual ~font_system(){}
	virtual const font_metrics_ptr create_font(const path& font_path,
	                                           unsigned font_height) = 0;
};

typedef shared_ptr<font_system> font_system_ptr;

namespace detail
{

template<> struct plugin_traits<font_system> {
	SGE_SYMBOL static address_name plugin_loader_name();
	SGE_SYMBOL static plugin_type::type get_plugin_type();
	typedef font_system* (*loader_fun)();
};

}

}

#endif

