//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_INTRUSIVE_DETAIL_CONNECTION_DECL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_DETAIL_CONNECTION_DECL_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/intrusive/connection_decl.hpp>
#include <sge/sprite/intrusive/detail/list.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_decl.hpp>


namespace sge
{
namespace sprite
{
namespace intrusive
{
namespace detail
{

template<
	typename Choices
>
class connection
:
	public sge::sprite::intrusive::connection<
		Choices
	>
{
	FCPPT_NONCOPYABLE(
		connection
	);
public:
	typedef
	sge::sprite::intrusive::detail::list<
		Choices
	>
	list;

	typedef
	fcppt::reference<
		list
	>
	list_ref;

	typedef
	fcppt::reference<
		sge::sprite::count
	>
	count_ref;

	connection(
		list_ref,
		count_ref
	);

	~connection()
	override;

	typedef
	sge::sprite::intrusive::connection<
		Choices
	>
	base;

	typedef
	typename
	base::object
	object;

	void
	add(
		object &
	)
	override;

	void
	remove()
	override;
private:
	list_ref list_;

	count_ref count_;
};

}
}
}
}

#endif
