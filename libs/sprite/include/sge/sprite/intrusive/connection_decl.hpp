//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_INTRUSIVE_CONNECTION_DECL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_CONNECTION_DECL_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/intrusive/connection_fwd.hpp>
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
class connection
{
	FCPPT_NONMOVABLE(
		connection
	);
protected:
	connection()
	= default;
public:
	using
	object
	=
	sge::sprite::object<
		Choices
	>;

	virtual
	void
	add(
		object &
	) = 0;

	virtual
	void
	remove() = 0;

	virtual
	~connection()
	= default;
};

}
}
}

#endif
