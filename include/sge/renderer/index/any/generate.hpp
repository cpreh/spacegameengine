/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_INDEX_ANY_GENERATE_HPP_INCLUDED
#define SGE_RENDERER_INDEX_ANY_GENERATE_HPP_INCLUDED

#include <sge/renderer/index/iterator.hpp>
#include <sge/renderer/index/view.hpp>
#include <sge/renderer/index/any/view.hpp>
#include <fcppt/tag.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace index
{
namespace any
{

template<
	typename Gen
>
void
generate(
	sge::renderer::index::any::view const &_view,
	Gen const &_gen
)
{
	fcppt::variant::apply_unary(
		[
			&_view,
			&_gen
		](
			auto const &_inner_view
		)
		{
			for(
				auto item
				:
				_inner_view
			)
				item.set(
					_gen(
						fcppt::tag<
							typename
							std::decay<
								decltype(
									_inner_view
								)
							>::type::value_type
						>{}
					)
				);
		},
		_view
	);
}

}
}
}
}

#endif
