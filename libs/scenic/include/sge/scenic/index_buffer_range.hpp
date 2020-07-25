//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_INDEX_BUFFER_RANGE_HPP_INCLUDED
#define SGE_SCENIC_INDEX_BUFFER_RANGE_HPP_INCLUDED

#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/scenic/detail/symbol.hpp>


namespace sge
{
namespace scenic
{

class index_buffer_range
{
public:
	SGE_SCENIC_DETAIL_SYMBOL
	index_buffer_range(
		sge::renderer::index::first const &,
		sge::renderer::index::count const &
	);

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::renderer::index::first const &
	first_index() const;

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::renderer::index::count const &
	index_count() const;
private:
	sge::renderer::index::first first_index_;
	sge::renderer::index::count index_count_;
};

}
}

#endif
