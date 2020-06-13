//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_RENDER_SCOPED_VERTEX_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_SCOPED_VERTEX_HPP_INCLUDED

#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/vertex/const_buffer_ref.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/sprite/detail/symbol.hpp>
#include <sge/sprite/detail/render/scoped_vertex_declaration.hpp>
#include <sge/sprite/state/vertex_options.hpp>
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
	SGE_SPRITE_DETAIL_SYMBOL
	scoped_vertex(
		sge::renderer::context::core_ref,
		sge::renderer::vertex::const_declaration_ref,
		sge::renderer::vertex::const_buffer_ref,
		sge::sprite::state::vertex_options const &
	);

	SGE_SPRITE_DETAIL_SYMBOL
	~scoped_vertex();
private:
	sge::sprite::detail::render::scoped_vertex_declaration const scoped_vertex_declaration_;

	sge::renderer::context::core_ref const render_context_;

	sge::renderer::vertex::const_buffer_ref const vertex_buffer_;

	bool const set_buffer_;
};

}
}
}
}

#endif
