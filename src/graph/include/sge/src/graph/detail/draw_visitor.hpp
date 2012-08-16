#ifndef SGE_SRC_GRAPH_DETAIL_DRAW_VISITOR_HPP_INCLUDED
#define SGE_SRC_GRAPH_DETAIL_DRAW_VISITOR_HPP_INCLUDED

#include <sge/graph/object.hpp>
#include <fcppt/nonassignable.hpp>

namespace sge
{
namespace graph
{
namespace detail
{
class draw_visitor
{
FCPPT_NONASSIGNABLE(
	draw_visitor);
public:
	typedef
	void
	result_type;

	explicit
	draw_visitor(
		sge::graph::object &_graph)
	:
		graph_(
			_graph)
	{
	}

	template<typename T>
	result_type
	operator()(
		T const &_t) const
	{
		graph_.draw_data(
			_t);
	}
private:
	sge::graph::object &graph_;
};
}
}
}

#endif
