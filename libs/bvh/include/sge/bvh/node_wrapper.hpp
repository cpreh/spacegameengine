//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_BVH_NODE_WRAPPER_HPP_INCLUDED
#define SGE_BVH_NODE_WRAPPER_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace bvh
{

template<
	typename Node,
	typename Box
>
class node_wrapper
{
public:
	using
	node
	=
	Node;

	using
	box
	=
	Box;

	node_wrapper(
		node const &_value,
		box _bounding_box
	)
	:
		value_(
			_value
		),
		bounding_box_(
			std::move(
				_bounding_box
			)
		)
	{
	}

	[[nodiscard]]
	node &
	value()
	{
		return
			value_;
	}

	[[nodiscard]]
	node const &
	value() const
	{
		return
			value_;
	}

	[[nodiscard]]
	box const &
	bounding_box() const
	{
		return
			bounding_box_;
	}
private:
	node value_;
	box bounding_box_;
};
}
}

#endif
