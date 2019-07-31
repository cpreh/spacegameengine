//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_INTRUSIVE_PROCESS_ORDERED_WITH_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_PROCESS_ORDERED_WITH_OPTIONS_HPP_INCLUDED

#include <sge/sprite/buffers/parameters.hpp>
#include <sge/sprite/detail/render/scoped_vertex_declaration.hpp>
#include <sge/sprite/intrusive/detail/render_one.hpp>
#include <sge/sprite/intrusive/ordered/collection_impl.hpp>
#include <sge/sprite/process/is_options.hpp>
#include <sge/sprite/render/parameters_impl.hpp>
#include <sge/sprite/state/object_fwd.hpp>
#include <sge/sprite/state/options_impl.hpp>
#include <sge/sprite/state/render_context.hpp>
#include <sge/sprite/state/scoped_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace intrusive
{
namespace process
{

template<
	typename Options,
	typename RenderContext,
	typename Choices,
	typename Order,
	typename Buffers,
	typename StateChoices,
	typename Compare
>
void
ordered_with_options(
	RenderContext &_render_context,
	sge::sprite::intrusive::ordered::collection<
		Choices,
		Order
	> &_collection,
	Buffers &_buffers,
	sge::sprite::state::object<
		StateChoices
	> &_states,
	Compare const &_compare,
	sge::sprite::state::options<
		StateChoices
	> const &_options
)
{
	static_assert(
		sge::sprite::process::is_options<
			Options
		>::value,
		"Options must be a sprite::process::options"
	);

	typedef typename sge::sprite::intrusive::ordered::collection<
		Choices,
		Order
	>::collection_base collection;

	sge::sprite::state::scoped<
		StateChoices
	> const scoped_states(
		_states.renderer(),
		_render_context,
		_options,
		_states
	);

	sge::sprite::detail::render::scoped_vertex_declaration const scoped_vertex_declaration(
		sge::sprite::render::parameters<
			StateChoices
		>(
			_render_context,
			_buffers.parameters().vertex_declaration()
		),
		_options.vertex_options()
	);

	_collection.for_each(
		std::bind(
			sge::sprite::intrusive::detail::render_one<
				Options,
				sge::sprite::state::render_context<
					StateChoices
				>,
				Buffers,
				Compare,
				typename collection::range_type
			>,
			std::ref(
				_render_context
			),
			std::ref(
				_buffers
			),
			std::cref(
				_compare
			),
			std::placeholders::_1
		)
	);
}

}
}
}
}

#endif
