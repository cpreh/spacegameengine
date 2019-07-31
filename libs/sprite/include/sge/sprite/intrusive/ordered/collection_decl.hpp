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
#include <fcppt/noncopyable.hpp>


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
	FCPPT_NONCOPYABLE(
		collection
	);
public:
	typedef
	Order
	order;

	typedef
	sge::sprite::intrusive::collection<
		Choices
	>
	collection_base;

	typedef
	Choices
	choices;

	typedef
	sge::sprite::intrusive::connection_ref<
		Choices
	>
	connection_ref;

	collection();

	~collection();

	collection_base &
	get(
		order const &
	);

	connection_ref
	connection(
		order const &
	);

	typedef
	sge::sprite::intrusive::ordered::range<
		Choices,
		order,
		false
	>
	range_type;

	typedef
	sge::sprite::intrusive::ordered::range<
		Choices,
		order,
		true
	>
	const_range_type;

	range_type
	range();

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
	typedef
	sge::sprite::intrusive::ordered::detail::map<
		order,
		Choices
	>
	order_map;

	order_map collections_;
};

}
}
}
}

#endif
