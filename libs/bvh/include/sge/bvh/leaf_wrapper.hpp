//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_BVH_LEAF_WRAPPER_HPP_INCLUDED
#define SGE_BVH_LEAF_WRAPPER_HPP_INCLUDED

#include <fcppt/reference_impl.hpp>


namespace sge::bvh
{
template<typename Leaf>
class leaf_wrapper
{
public:
	using
	leaf
	=
	Leaf;

	explicit
	leaf_wrapper(
		leaf &_value)
	:
		value_(
			_value)
	{
	}

	[[nodiscard]]
	leaf &
	value() const
	{
		return
			value_.get();
	}
private:
	fcppt::reference<
		leaf
	> value_;
};
}

#endif
