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


#ifndef SGE_SPRITE_INTRUSIVE_DETAIL_RENDER_ONE_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_DETAIL_RENDER_ONE_HPP_INCLUDED

#include <sge/renderer/vertex/scoped_buffer.hpp>
#include <sge/sprite/buffers/roles/vertex_buffer.hpp>
#include <sge/sprite/detail/process/geometry.hpp>
#include <sge/sprite/detail/render/range.hpp>
#include <sge/sprite/detail/render/range_object.hpp>
#include <sge/sprite/render/range_impl.hpp>
#include <majutsu/get.hpp>
#include <fcppt/optional/maybe_void.hpp>


namespace sge
{
namespace sprite
{
namespace intrusive
{
namespace detail
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
	typedef
	typename
	Buffers::choices
	choices;

	typedef
	sge::sprite::render::range<
		choices
	>
	range_type;

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
			sge::sprite::detail::render::range_object<
				choices
			> const &_range_object
		)
		{
			sge::renderer::vertex::scoped_buffer const scoped_buffer(
				_render_context,
				*majutsu::get<
					sge::sprite::buffers::roles::vertex_buffer
				>(
					_range_object
				)
			);

			sge::sprite::detail::render::range(
				_render_context,
				_range_object,
				range.parts()
			);
		}
	);
}

}
}
}
}

#endif
