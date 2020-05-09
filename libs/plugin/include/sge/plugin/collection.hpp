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
	using
	size_type
	=
	sge::plugin::category_array::size_type;

	using
	iterator
	=
	sge::plugin::iterator<
		Type
	>;

	using
	const_iterator
	=
	iterator;

	using
	context
	=
	sge::plugin::context<
		Type
	>;

	using
	value_type
	=
	context;

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
	collection(
		collection &&
	)
	noexcept;

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	collection &
	operator=(
		collection const &
	);

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	collection &
	operator=(
		collection &&
	)
	noexcept;

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	~collection(); // NOLINT(performance-trivially-destructible)

	[[nodiscard]]
	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	iterator
	begin() const;

	[[nodiscard]]
	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	iterator
	end() const;

	[[nodiscard]]
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
