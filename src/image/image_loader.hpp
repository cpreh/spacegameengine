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


#ifndef SGE_IMAGE_LOADER_HPP_INCLUDED
#define SGE_IMAGE_LOADER_HPP_INCLUDED

#include "../string.hpp"
#include "../shared_ptr.hpp"
#include "../plugin_traits.hpp"
#include "../path.hpp"
#include "image.hpp"
#include "image_format.hpp"

namespace sge
{

class image_loader {
public:
	virtual image_ptr load_image(const path&) = 0;
	virtual image_ptr load_image(image_format::type type, image::const_pointer format_data, image::size_type size) = 0;
	virtual image_ptr create_image(image::const_pointer data, const image::dim_type&) = 0;
	virtual ~image_loader(){}
};

typedef shared_ptr<image_loader> image_loader_ptr;

namespace detail
{

template<> struct plugin_traits<image_loader> {
	static address_name plugin_loader_name();
	static plugin_type::type get_plugin_type();
	typedef image_loader* (*loader_fun)();
};

}

}

#endif
