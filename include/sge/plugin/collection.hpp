/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/plugin/category_array.hpp>
#include <sge/plugin/collection_fwd.hpp>
#include <sge/plugin/context_fwd.hpp>
#include <sge/plugin/iterator_fwd.hpp>
#include <sge/plugin/detail/instantiate/symbol.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace plugin
{

template<
	typename Type
>
class collection
{
	FCPPT_NONASSIGNABLE(
		collection
	);
public:
	typedef
	sge::plugin::category_array::size_type
	size_type;

	typedef
	sge::plugin::iterator<
		Type
	>
	iterator;

	typedef
	sge::plugin::context<
		Type
	>
	context;

	typedef
	context
	value_type;

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	explicit
	collection(
		sge::plugin::category_array &
	);

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	collection(
		collection const &
	);

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	~collection();

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	iterator const
	begin() const;

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	iterator const
	end() const;

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	context const
	get(
		size_type index
	) const;

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	size_type
	size() const;
private:
	sge::plugin::category_array &plugins_;
};

}
}

#endif
