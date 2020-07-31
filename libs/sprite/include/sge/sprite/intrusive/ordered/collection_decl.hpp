//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_COLLECTION_DECL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_COLLECTION_DECL_HPP_INCLUDED

#include <sge/sprite/intrusive/collection_fwd.hpp>
#include <sge/sprite/intrusive/connection_ref_fwd.hpp>
#include <sge/sprite/intrusive/ordered/collection_fwd.hpp>
#include <sge/sprite/intrusive/ordered/range_fwd.hpp>
#include <sge/sprite/intrusive/ordered/detail/map.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace sprite
{
namespace intrusive
{
namespace ordered
{

template<
	typename Choices,
	typename Order
>
class collection
{
	FCPPT_NONMOVABLE(
		collection
	);
public:
	using
	order
	=
	Order;

	using
	collection_base
	=
	sge::sprite::intrusive::collection<
		Choices
	>;

	using
	choices
	=
	Choices;

	using
	connection_ref
	=
	sge::sprite::intrusive::connection_ref<
		Choices
	>;

	collection();

	~collection();

	[[nodiscard]]
	collection_base &
	get(
		order const &
	);

	[[nodiscard]]
	connection_ref
	connection(
		order const &
	);

	using
	range_type
	=
	sge::sprite::intrusive::ordered::range<
		Choices,
		order,
		false
	>;

	using
	const_range_type
	=
	sge::sprite::intrusive::ordered::range<
		Choices,
		order,
		true
	>;

	[[nodiscard]]
	range_type
	range();

	[[nodiscard]]
	const_range_type
	range() const;

	template<
		typename Function
	>
	void
	for_each(
		Function const &
	);
private:
	using
	order_map
	=
	sge::sprite::intrusive::ordered::detail::map<
		order,
		Choices
	>;

	order_map collections_;
};

}
}
}
}

#endif
