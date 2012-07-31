#include <sge/model/obj/index_buffer_range.hpp>

sge::model::obj::index_buffer_range::index_buffer_range(
	sge::renderer::first_index const &_first_index,
	sge::renderer::index_count const &_index_count)
:
	first_index_(
		_first_index),
	index_count_(
		_index_count)
{
}

sge::renderer::first_index const &
sge::model::obj::index_buffer_range::first_index() const
{
	return
		first_index_;
}

sge::renderer::index_count const &
sge::model::obj::index_buffer_range::index_count() const
{
	return
		index_count_;
}
