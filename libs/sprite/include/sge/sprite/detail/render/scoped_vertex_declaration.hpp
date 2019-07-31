//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
