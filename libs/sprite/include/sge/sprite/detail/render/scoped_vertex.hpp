//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_RENDER_SCOPED_VERTEX_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_SCOPED_VERTEX_HPP_INCLUDED

#include <sge/renderer/context/core.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/sprite/detail/render/scoped_vertex_declaration.hpp>
#include <sge/sprite/render/parameters.hpp>
#include <sge/sprite/state/vertex_options.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/nonmovable.hpp>


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
	FCPPT_NONMOVABLE(
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
				fcppt::make_cref(
					vertex_buffer_
				)
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
