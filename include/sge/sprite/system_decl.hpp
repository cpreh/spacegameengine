/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_SYSTEM_DECL_HPP_INCLUDED
#define SGE_SPRITE_SYSTEM_DECL_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <sge/sprite/buffers_decl.hpp>
#include <sge/sprite/buffers_option.hpp>
#include <sge/sprite/system_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace sprite
{

template<
	typename Choices
>
class system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	system(
		sge::renderer::device &,
		sge::sprite::buffers_option::type
	);

	~system();

	typedef sge::sprite::buffers<
		Choices
	> buffers_type;

	buffers_type &
	buffers();

	buffers_type const &
	buffers() const;
private:
	sge::renderer::vertex_declaration_ptr const vertex_declaration_;

	buffers_type buffers_;
};

}
}

#endif
