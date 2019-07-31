//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_RENDER_PARAMETERS_DECL_HPP_INCLUDED
#define SGE_SPRITE_RENDER_PARAMETERS_DECL_HPP_INCLUDED

#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/sprite/render/parameters_fwd.hpp>
#include <sge/sprite/state/render_context.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace sprite
{
namespace render
{

template<
	typename StateOptions
>
class parameters
{
public:
	typedef
	sge::sprite::state::render_context<
		StateOptions
	>
	render_context_type;

	parameters(
		render_context_type &,
		sge::renderer::vertex::declaration const &
	);

	render_context_type &
	render_context() const;

	sge::renderer::vertex::declaration const &
	vertex_declaration() const;
private:
	fcppt::reference<
		render_context_type
	> render_context_;

	fcppt::reference<
		sge::renderer::vertex::declaration const
	> vertex_declaration_;
};

}
}
}

#endif
