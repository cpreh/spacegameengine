//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_COLLECTION_HPP_INCLUDED
#define SGE_PLUGIN_COLLECTION_HPP_INCLUDED

#include <sge/plugin/category_array.hpp>
#include <sge/plugin/collection_fwd.hpp>
#include <sge/plugin/context_fwd.hpp>
#include <sge/plugin/iterator_fwd.hpp>
#include <sge/plugin/detail/instantiate/symbol.hpp>
#include <fcppt/reference_decl.hpp>


namespace sge
{
namespace plugin
{

template<
	typename Type
>
class collection
{
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
	iterator
	const_iterator;

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
		sge::plugin::category_array const &
	);

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	collection(
		collection const &
	);

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	collection &
	operator=(
		collection const &
	);

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	~collection();

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	iterator
	begin() const;

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	iterator
	end() const;

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	size_type
	size() const;
private:
	fcppt::reference<
		sge::plugin::category_array const
	> plugins_;
};

}
}

#endif
