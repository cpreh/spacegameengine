/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_INTRUSIVE_PROCESS_ORDERED_WITH_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_PROCESS_ORDERED_WITH_OPTIONS_HPP_INCLUDED

#include <sge/renderer/context/object_fwd.hpp>
#include <sge/sprite/buffers/parameters.hpp>
#include <sge/sprite/detail/render/scoped_matrices.hpp>
#include <sge/sprite/detail/render/scoped_states.hpp>
#include <sge/sprite/detail/render/scoped_vertex_declaration.hpp>
#include <sge/sprite/intrusive/detail/render_one.hpp>
#include <sge/sprite/intrusive/ordered/collection_impl.hpp>
#include <sge/sprite/process/is_options.hpp>
#include <sge/sprite/render/options.hpp>
#include <sge/sprite/render/parameters.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
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
	typename Choices,
	typename Order,
	typename Buffers,
	typename Compare
>
typename boost::enable_if<
	sge::sprite::process::is_options<
		Options
	>,
	void
>::type
ordered_with_options(
	sge::renderer::context::object &_render_context,
	sge::sprite::intrusive::ordered::collection<
		Choices,
		Order
	> &_collection,
	Buffers &_buffers,
	Compare const &_compare,
	sge::sprite::render::options const &_render_options
)
{
	typedef typename sge::sprite::intrusive::ordered::collection<
		Choices,
		Order
	>::collection_base collection;

	sge::sprite::detail::render::scoped_matrices const scoped_matrices(
		_render_context,
		_render_options.matrix_options()
	);

	sge::sprite::detail::render::scoped_states<
		Choices
	> const scoped_states(
		_render_context,
		_render_options.state_options()
	);

	sge::sprite::detail::render::scoped_vertex_declaration const scoped_vertex_declaration(
		sge::sprite::render::parameters(
			_render_context,
			_buffers.parameters().vertex_declaration()
		),
		_render_options.vertex_options()
	);

	_collection.for_each(
		std::tr1::bind(
			sge::sprite::intrusive::detail::render_one<
				Options,
				Buffers,
				Compare,
				typename collection::range_type
			>,
			fcppt::ref(
				_render_context
			),
			fcppt::ref(
				_buffers
			),
			fcppt::cref(
				_compare
			),
			std::tr1::placeholders::_1
		)
	);
}

}
}
}
}

#endif
