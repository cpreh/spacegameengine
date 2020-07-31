//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_INTRUSIVE_COLLECTION_DECL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_COLLECTION_DECL_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/intrusive/collection_fwd.hpp>
#include <sge/sprite/intrusive/connection_ref_fwd.hpp>
#include <sge/sprite/intrusive/range_fwd.hpp>
#include <sge/sprite/intrusive/detail/connection_decl.hpp>
#include <sge/sprite/intrusive/detail/list.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace sprite
{
namespace intrusive
{

template<
	typename Choices
>
class collection
{
	FCPPT_NONMOVABLE(
		collection
	);
public:
	using
	object
	=
	sge::sprite::object<
		Choices
	>;

	using
	connection_ref
	=
	sge::sprite::intrusive::connection_ref<
		Choices
	>;

	collection();

	~collection();

	[[nodiscard]]
	connection_ref
	connection();

	using
	range_type
	=
	sge::sprite::intrusive::range<
		Choices,
		false
	>;

	using
	const_range_type
	=
	sge::sprite::intrusive::range<
		Choices,
		true
	>;

	[[nodiscard]]
	range_type
	range();

	[[nodiscard]]
	const_range_type
	range() const;
private:
	using
	list
	=
	sge::sprite::intrusive::detail::list<
		Choices
	>;

	list sprites_;

	sge::sprite::count count_;

	using
	connection_impl
	=
	sge::sprite::intrusive::detail::connection<
		Choices
	>;

	connection_impl connection_;
};

}
}
}

#endif
