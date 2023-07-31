//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GRAPH_AXIS_CONSTRAINT_HPP_INCLUDED
#define SGE_GRAPH_AXIS_CONSTRAINT_HPP_INCLUDED

#include <sge/graph/axis_constraint_fwd.hpp>
#include <sge/graph/scalar.hpp>
#include <sge/graph/detail/symbol.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp>

namespace sge::graph
{

class axis_constraint
{
public:
  FCPPT_DECLARE_STRONG_TYPEDEF(sge::graph::scalar, min_type);
  FCPPT_DECLARE_STRONG_TYPEDEF(sge::graph::scalar, max_type);

  SGE_GRAPH_DETAIL_SYMBOL
  axis_constraint(min_type, max_type);

  [[nodiscard]] SGE_GRAPH_DETAIL_SYMBOL sge::graph::scalar min() const;

  [[nodiscard]] SGE_GRAPH_DETAIL_SYMBOL sge::graph::scalar max() const;

private:
  sge::graph::scalar min_;
  sge::graph::scalar max_;
};

}

#endif
