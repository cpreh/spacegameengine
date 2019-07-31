//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_RENDER_RANGE_WITH_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_RENDER_RANGE_WITH_OPTIONS_HPP_INCLUDED

#include <sge/sprite/buffers/roles/vertex_buffer.hpp>
#include <sge/sprite/detail/render/range.hpp>
#include <sge/sprite/detail/render/range_object.hpp>
#include <sge/sprite/detail/render/scoped_vertex.hpp>
#include <sge/sprite/render/parameters.hpp>
#include <sge/sprite/render/range_impl.hpp>
#include <sge/sprite/state/object_fwd.hpp>
#include <sge/sprite/state/options_fwd.hpp>
#include <sge/sprite/state/scoped_impl.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/record/get.hpp>


namespace sge
{
namespace sprite
{
namespace render
{

template<
	typename Choices,
	typename StateChoices
>
void
range_with_options(
	sge::sprite::render::parameters<
		StateChoices
	> const &_parameters,
	sge::sprite::render::range<
		Choices
	> const &_range,
	sge::sprite::state::object<
		StateChoices
	> &_states,
	sge::sprite::state::options<
		StateChoices
	> const &_options
)
{
	fcppt::optional::maybe_void(
		_range.object(),
		[
			&_parameters,
			&_range,
			&_states,
			&_options
		](
			fcppt::reference<
				sge::sprite::detail::render::range_object<
					Choices
				> const
			> const _range_object
		)
		{
			sge::sprite::state::scoped<
				StateChoices
			> const states(
				_states.renderer(),
				_parameters.render_context(),
				_options,
				_states
			);

			sge::sprite::detail::render::scoped_vertex const scoped_vertex(
				_parameters,
				*fcppt::record::get<
					sge::sprite::buffers::roles::vertex_buffer
				>(
					_range_object.get()
				),
				_options.vertex_options()
			);

			sge::sprite::detail::render::range(
				_parameters.render_context(),
				_range_object.get(),
				_range.parts()
			);
		}
	);
}

}
}
}

#endif
