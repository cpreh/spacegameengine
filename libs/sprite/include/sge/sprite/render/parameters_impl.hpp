//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_RENDER_PARAMETERS_IMPL_HPP_INCLUDED
#define SGE_SPRITE_RENDER_PARAMETERS_IMPL_HPP_INCLUDED

#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/sprite/render/parameters_decl.hpp>


template<
	typename StateOptions
>
sge::sprite::render::parameters<
	StateOptions
>::parameters(
	render_context_type &_render_context,
	sge::renderer::vertex::declaration const &_vertex_declaration
)
:
	render_context_(
		_render_context
	),
	vertex_declaration_(
		_vertex_declaration
	)
{
}

template<
	typename StateOptions
>
typename
sge::sprite::render::parameters<
	StateOptions
>::render_context_type &
sge::sprite::render::parameters<
	StateOptions
>::render_context() const
{
	return
		render_context_.get();
}

template<
	typename StateOptions
>
sge::renderer::vertex::declaration const &
sge::sprite::render::parameters<
	StateOptions
>::vertex_declaration() const
{
	return
		vertex_declaration_.get();
}

#endif
