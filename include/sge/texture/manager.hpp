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


#ifndef FCPPT_TEXTURE_MANAGER_HPP_INCLUDED
#define FCPPT_TEXTURE_MANAGER_HPP_INCLUDED

#include <sge/texture/part_ptr.hpp>
#include <sge/texture/fragmented_fwd.hpp>
#include <sge/texture/fragmented_auto_ptr.hpp>
#include <sge/texture/detail/container_position.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/symbol.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace texture
{

class manager
{
	FCPPT_NONCOPYABLE(manager)
public:
	typedef sge::function::object<
		fragmented_auto_ptr ()
	> onalloc_function;

	SGE_SYMBOL manager(
		sge::renderer::device_ptr rend,
		onalloc_function const &
	);

	SGE_SYMBOL ~manager();

	SGE_SYMBOL part_ptr const
	add(
		image::view::const_object const &
	);

	SGE_SYMBOL sge::renderer::device_ptr const
	renderer() const;

	SGE_SYMBOL void
	onalloc(
		onalloc_function const &
	);

	SGE_SYMBOL void
	free_empty_textures();
private:
	friend class fragmented;

	void
	part_freed(
		detail::container_position const &,
		fragmented const &
	);

	sge::renderer::device_ptr const     rend;
	onalloc_function                    onalloc_;

	detail::fragmented_queue            free_textures;
	detail::fragmented_list             full_textures;
};

}
}

#endif
