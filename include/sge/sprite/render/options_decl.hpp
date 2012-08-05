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


#ifndef SGE_SPRITE_RENDER_OPTIONS_DECL_HPP_INCLUDED
#define SGE_SPRITE_RENDER_OPTIONS_DECL_HPP_INCLUDED

#include <sge/sprite/render/matrix_options.hpp>
#include <sge/sprite/render/options_fwd.hpp>
#include <sge/sprite/render/state_options.hpp>
#include <sge/sprite/render/vertex_options.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace sprite
{
namespace render
{

class options
{
	FCPPT_NONASSIGNABLE(
		options
	);
public:
	options(
		sge::sprite::render::matrix_options::type,
		sge::sprite::render::state_options::type,
		sge::sprite::render::vertex_options::type
	);

	sge::sprite::render::matrix_options::type
	matrix_options() const;

	sge::sprite::render::state_options::type
	state_options() const;

	sge::sprite::render::vertex_options::type
	vertex_options() const;
private:
	sge::sprite::render::matrix_options::type const matrix_options_;

	sge::sprite::render::state_options::type const state_options_;

	sge::sprite::render::vertex_options::type const vertex_options_;
};

}
}
}

#endif
