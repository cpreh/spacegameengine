//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_BVH_DUMMY_NODE_HPP_INCLUDED
#define SGE_BVH_DUMMY_NODE_HPP_INCLUDED

namespace sge::bvh
{
class dummy_node
{
public:
  template <typename Box>
  explicit dummy_node(Box const &)
  {
  }
};
}

#endif
