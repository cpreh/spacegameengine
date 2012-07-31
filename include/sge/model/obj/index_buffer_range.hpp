#ifndef SGE_MODEL_OBJ_INDEX_BUFFER_RANGE_HPP_INCLUDED
#define SGE_MODEL_OBJ_INDEX_BUFFER_RANGE_HPP_INCLUDED

#include <sge/model/obj/symbol.hpp>
#include <sge/renderer/first_index.hpp>
#include <sge/renderer/index_count.hpp>

namespace sge
{
namespace model
{
namespace obj
{
class index_buffer_range
{
public:
	SGE_MODEL_OBJ_SYMBOL
	index_buffer_range(
		sge::renderer::first_index const &,
		sge::renderer::index_count const &);

	SGE_MODEL_OBJ_SYMBOL
	sge::renderer::first_index const &
	first_index() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::renderer::index_count const &
	index_count() const;
private:
	sge::renderer::first_index first_index_;
	sge::renderer::index_count index_count_;
};
}
}
}

#endif
