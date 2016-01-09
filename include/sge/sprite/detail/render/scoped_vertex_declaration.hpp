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


#ifndef SGE_SPRITE_DETAIL_RENDER_SCOPED_VERTEX_DECLARATION_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_SCOPED_VERTEX_DECLARATION_HPP_INCLUDED

#include <sge/renderer/context/core.hpp>
#include <sge/renderer/vertex/const_optional_declaration_ref.hpp>
#include <sge/sprite/render/parameters.hpp>
#include <sge/sprite/state/vertex_options.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace render
{

class scoped_vertex_declaration
{
	FCPPT_NONCOPYABLE(
		scoped_vertex_declaration
	);
public:
	template<
		typename StateChoices
	>
	scoped_vertex_declaration(
		sge::sprite::render::parameters<
			StateChoices
		> const &_parameters,
		sge::sprite::state::vertex_options const &_options
	)
	:
		render_context_(
			_parameters.render_context()
		),
		set_declaration_(
			_options
			==
			sge::sprite::state::vertex_options::declaration
			||
			_options
			==
			sge::sprite::state::vertex_options::declaration_and_buffer
		)
	{
		if(
			set_declaration_
		)
			render_context_.vertex_declaration(
				sge::renderer::vertex::const_optional_declaration_ref(
					fcppt::make_cref(
						_parameters.vertex_declaration()
					)
				)
			);
	}

	~scoped_vertex_declaration()
	{
		if(
			set_declaration_
		)
			render_context_.vertex_declaration(
				sge::renderer::vertex::const_optional_declaration_ref()
			);
	}
private:
	sge::renderer::context::core &render_context_;

	bool const set_declaration_;
};

}
}
}
}

#endif
