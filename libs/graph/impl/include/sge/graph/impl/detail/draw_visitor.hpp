//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GRAPH_IMPL_DETAIL_DRAW_VISITOR_HPP_INCLUDED
#define SGE_GRAPH_IMPL_DETAIL_DRAW_VISITOR_HPP_INCLUDED

#include <sge/graph/object.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace graph
{
namespace detail
{

class draw_visitor
{
public:
	explicit
	draw_visitor(
		sge::graph::object &_graph
	)
	:
		graph_(
			_graph
		)
	{
	}

	template<
		typename T
	>
	void
	operator()(
		T const &_t
	) const
	{
		this->graph_.get().draw_data(
			_t
		);
	}
private:
	fcppt::reference<
		sge::graph::object
	> graph_;
};

}
}
}

#endif
