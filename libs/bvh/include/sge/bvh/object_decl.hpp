//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_BVH_OBJECT_DECL_HPP_INCLUDED
#define SGE_BVH_OBJECT_DECL_HPP_INCLUDED

#include <sge/bvh/tree_traits.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace bvh
{

template<typename Traits>
class object
{
FCPPT_NONMOVABLE(
	object);
public:
	using
	traits
	=
	Traits;

	using
	leaf_sequence
	=
	typename
	traits::leaf_sequence;

	using
	tree_representation
	=
	typename
	traits::tree_representation;

	object();

	void
	insert(
		leaf_sequence const &
	);

	[[nodiscard]]
	tree_representation const &
	representation() const;

	~object();
private:
	leaf_sequence leaves_;

	tree_representation representation_;
};

}
}

#endif
