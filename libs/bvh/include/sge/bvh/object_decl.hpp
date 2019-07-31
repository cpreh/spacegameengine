//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_BVH_OBJECT_DECL_HPP_INCLUDED
#define SGE_BVH_OBJECT_DECL_HPP_INCLUDED

#include <sge/bvh/tree_traits.hpp>
#include <fcppt/noncopyable.hpp>
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
FCPPT_NONCOPYABLE(
	object);
public:
	typedef
	Traits
	traits;

	typedef
	typename
	traits::leaf_sequence
	leaf_sequence;

	typedef
	typename
	traits::tree_representation
	tree_representation;

	object();

	void
	insert(
		leaf_sequence const &);

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
