/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
