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


#ifndef SGE_SPRITE_DETAIL_RENDER_SCOPED_MATRICES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_SCOPED_MATRICES_HPP_INCLUDED

#include <sge/renderer/context/object_fwd.hpp>
#include <sge/sprite/set_matrices.hpp>
#include <sge/sprite/unset_matrices.hpp>
#include <sge/sprite/render/matrix_options.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace render
{

class scoped_matrices
{
	FCPPT_NONCOPYABLE(
		scoped_matrices
	);
public:
	scoped_matrices(
		sge::renderer::context::object &_render_context,
		sge::sprite::render::matrix_options::type const _options
	)
	:
		render_context_(
			_render_context
		),
		set_matrices_(
			_options
			==
			sge::sprite::render::matrix_options::set
		)
	{
		if(
			set_matrices_
		)
			sge::sprite::set_matrices(
				render_context_
			);
	}

	~scoped_matrices()
	{
		if(
			set_matrices_
		)
			sge::sprite::unset_matrices(
				render_context_
			);
	}
private:
	sge::renderer::context::object &render_context_;

	bool const set_matrices_;
};

}
}
}
}

#endif
