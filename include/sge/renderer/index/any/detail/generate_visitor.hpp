/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_INDEX_ANY_DETAIL_GENERATE_VISITOR_HPP_INCLUDED
#define SGE_RENDERER_INDEX_ANY_DETAIL_GENERATE_VISITOR_HPP_INCLUDED

#include <sge/renderer/index/iterator.hpp>
#include <sge/renderer/index/proxy.hpp>
#include <fcppt/nonassignable.hpp>

namespace sge
{
namespace renderer
{
namespace index
{
namespace any
{
namespace detail
{

template<
	typename Gen
>
class generate_visitor
{
	FCPPT_NONASSIGNABLE(
		generate_visitor
	);
public:
	typedef void result_type;

	explicit generate_visitor(
		Gen const &_gen
	)
	:
		gen_(_gen)
	{}

	template<
		typename View
	>
	result_type
	operator()(
		View const &_view
	) const
	{
		for(
			typename View::iterator
				it(
					_view.begin()
				),
				end(
					_view.end()
				);
			it != end;
			++it
		)
			(*it).set(
				gen_.operator()<typename View::value_type>()
			);
	}
private:
	Gen const gen_;
};

}
}
}
}
}

#endif
