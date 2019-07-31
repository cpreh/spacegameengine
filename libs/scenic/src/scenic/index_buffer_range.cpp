//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/scenic/index_buffer_range.hpp>


sge::scenic::index_buffer_range::index_buffer_range(
	sge::renderer::index::first const &_first_index,
	sge::renderer::index::count const &_index_count)
:
	first_index_(
		_first_index),
	index_count_(
		_index_count)
{
}

sge::renderer::index::first const &
sge::scenic::index_buffer_range::first_index() const
{
	return
		first_index_;
}

sge::renderer::index::count const &
sge::scenic::index_buffer_range::index_count() const
{
	return
		index_count_;
}
