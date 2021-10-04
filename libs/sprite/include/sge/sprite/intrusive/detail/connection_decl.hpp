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
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_decl.hpp>


namespace sge::sprite::intrusive::detail
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
	FCPPT_NONMOVABLE(
		connection
	);
public:
	using
	list
	=
	sge::sprite::intrusive::detail::list<
		Choices
	>;

	using
	list_ref
	=
	fcppt::reference<
		list
	>;

	using
	count_ref
	=
	fcppt::reference<
		sge::sprite::count
	>;

	connection(
		list_ref,
		count_ref
	);

	~connection()
	override;

	using
	base
	=
	sge::sprite::intrusive::connection<
		Choices
	>;

	using
	object
	=
	typename
	base::object;

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

#endif
