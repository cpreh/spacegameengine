//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_INTRUSIVE_DETAIL_RENDER_ONE_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_DETAIL_RENDER_ONE_HPP_INCLUDED

#include <sge/renderer/vertex/scoped_buffer.hpp>
#include <sge/sprite/buffers/roles/vertex_buffer.hpp>
#include <sge/sprite/detail/process/geometry.hpp>
#include <sge/sprite/detail/render/range.hpp>
#include <sge/sprite/detail/render/range_object.hpp>
#include <sge/sprite/render/range_impl.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/record/get.hpp>


namespace sge::sprite::intrusive::detail
{

template<
	typename Options,
	typename RenderContext,
	typename Buffers,
	typename Compare,
	typename Range
>
void
render_one(
	RenderContext &_render_context,
	Buffers &_buffers,
	Compare const &_compare,
	Range const &_range
)
{
	using
	choices
	=
	typename
	Buffers::choices;

	using
	range_type
	=
	sge::sprite::render::range<
		choices
	>;

	range_type const range(
		sge::sprite::detail::process::geometry<
			Options::geometry_options::value,
			choices
		>(
			_range,
			_buffers,
			_compare
		)
	);

	fcppt::optional::maybe_void(
		range.object(),
		[
			&_render_context,
			&range
		](
			fcppt::reference<
				sge::sprite::detail::render::range_object<
					choices
				> const
			> const _range_object
		)
		{
			sge::renderer::vertex::scoped_buffer const scoped_buffer(
				_render_context,
				*fcppt::record::get<
					sge::sprite::buffers::roles::vertex_buffer
				>(
					_range_object.get()
				)
			);

			sge::sprite::detail::render::range(
				_render_context,
				_range_object.get(),
				range.parts()
			);
		}
	);
}

}

#endif
