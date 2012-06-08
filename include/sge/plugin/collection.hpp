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


#ifndef SGE_PLUGIN_COLLECTION_HPP_INCLUDED
#define SGE_PLUGIN_COLLECTION_HPP_INCLUDED

#include <sge/plugin/collection_fwd.hpp>
#include <sge/plugin/context_fwd.hpp>
#include <sge/plugin/iterator_fwd.hpp>
#include <sge/plugin/detail/collection_base_fwd.hpp>
#include <sge/plugin/detail/instantiate/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>



namespace sge
{
namespace plugin
{

template<
	typename Type
>
class collection
:
	public sge::plugin::detail::collection_base
{
	FCPPT_NONCOPYABLE(
		collection
	);

	typedef typename sge::plugin::category_array<
		Type
	>::type plugin_array;
public:
	typedef std::size_t size_type;

	typedef typename plugin_array::iterator iterator;

	typedef sge::plugin::context<
		Type
	> context;

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	collection();

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	~collection();

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	iterator const
	begin();

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	iterator const
	end();

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	context const &
	get(
		size_type index
	);

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	size_type
	size() const;
private:
	plugin_array plugins_;
};

}
}

#endif
