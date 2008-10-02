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


#ifndef SGE_TEXTURE_MANAGER_HPP_INCLUDED
#define SGE_TEXTURE_MANAGER_HPP_INCLUDED

#include "part_fwd.hpp"
#include "fragmented_auto_ptr.hpp"
#include "../export.hpp"
#include "../exception.hpp"
#include "../renderer/device_fwd.hpp"
#include "../renderer/texture_fwd.hpp"
#include "../renderer/image_view.hpp"
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <boost/ptr_container/ptr_list.hpp>

namespace sge
{
namespace texture
{

class fragmented;

class manager : boost::noncopyable {
public:
	typedef boost::function<fragmented_auto_ptr ()> onalloc_function;

	SGE_SYMBOL manager(
		renderer::device_ptr rend,
		onalloc_function const &);
	SGE_SYMBOL part_ptr const add(
		renderer::const_image_view const &src);
	SGE_SYMBOL renderer::device_ptr const get_renderer() const;
	SGE_SYMBOL void onalloc(onalloc_function const &);

	class SGE_CLASS_SYMBOL image_too_big : public exception {
	public:
		SGE_SYMBOL image_too_big();
	};
private:
	part_ptr const init_texture(
		fragmented &,
		renderer::const_image_view const &src) const;

	renderer::device_ptr const          rend;
	onalloc_function                    onalloc_;
	typedef boost::ptr_list<fragmented> fragmented_texture_list;
	fragmented_texture_list             fragmented_textures;
};

}
}

#endif
