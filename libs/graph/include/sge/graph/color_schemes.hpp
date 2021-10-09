//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GRAPH_COLOR_SCHEMES_HPP_INCLUDED
#define SGE_GRAPH_COLOR_SCHEMES_HPP_INCLUDED

#include <sge/graph/color_scheme.hpp>
#include <sge/graph/detail/symbol.hpp>

namespace sge::graph::color_schemes
{

SGE_GRAPH_DETAIL_SYMBOL
sge::graph::color_scheme default_();

SGE_GRAPH_DETAIL_SYMBOL
sge::graph::color_scheme bright();

SGE_GRAPH_DETAIL_SYMBOL
sge::graph::color_scheme night();

SGE_GRAPH_DETAIL_SYMBOL
sge::graph::color_scheme minimal();

}

#endif
