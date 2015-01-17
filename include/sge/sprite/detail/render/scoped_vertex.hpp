/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_DETAIL_RENDER_SCOPED_VERTEX_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_SCOPED_VERTEX_HPP_INCLUDED

#include <sge/renderer/context/core.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/sprite/detail/render/scoped_vertex_declaration.hpp>
#include <sge/sprite/render/parameters.hpp>
#include <sge/sprite/state/vertex_options.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace render
{

class scoped_vertex
{
	FCPPT_NONCOPYABLE(
		scoped_vertex
	);
public:
	template<
		typename StateChoices
	>
	scoped_vertex(
		sge::sprite::render::parameters<
			StateChoices
		> const &_parameters,
		sge::renderer::vertex::buffer const &_vertex_buffer,
		sge::sprite::state::vertex_options const &_options
	)
	:
		scoped_vertex_declaration_(
			_parameters,
			_options
		),
		render_context_(
			_parameters.render_context()
		),
		vertex_buffer_(
			_vertex_buffer
		),
		set_buffer_(
			_options
			==
			sge::sprite::state::vertex_options::buffer
			||
			_options
			==
			sge::sprite::state::vertex_options::declaration_and_buffer
		)
	{
		if(
			set_buffer_
		)
			render_context_.activate_vertex_buffer(
				vertex_buffer_
			);
	}

	~scoped_vertex()
	{
		if(
			set_buffer_
		)
			render_context_.deactivate_vertex_buffer(
				vertex_buffer_
			);
	}
private:
	sge::sprite::detail::render::scoped_vertex_declaration const scoped_vertex_declaration_;

	sge::renderer::context::core &render_context_;

	sge::renderer::vertex::buffer const &vertex_buffer_;

	bool const set_buffer_;
};

}
}
}
}

#endif
