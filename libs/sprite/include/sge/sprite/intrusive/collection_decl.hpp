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
#include <fcppt/noncopyable.hpp>


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
	FCPPT_NONCOPYABLE(
		collection
	);
public:
	typedef sge::sprite::object<
		Choices
	> object;

	typedef
	sge::sprite::intrusive::connection_ref<
		Choices
	>
	connection_ref;

	collection();

	~collection();

	connection_ref
	connection();

	typedef sge::sprite::intrusive::range<
		Choices,
		false
	> range_type;

	typedef sge::sprite::intrusive::range<
		Choices,
		true
	> const_range_type;

	range_type
	range();

	const_range_type
	range() const;
private:
	typedef
	sge::sprite::intrusive::detail::list<
		Choices
	>
	list;

	list sprites_;

	sge::sprite::count count_;

	typedef sge::sprite::intrusive::detail::connection<
		Choices
	> connection_impl;

	connection_impl connection_;
};

}
}
}

#endif
