//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_LOCKED_PART_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_LOCKED_PART_HPP_INCLUDED

#include <sge/renderer/lock_segment.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vf/dynamic/locked_part_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

class locked_part
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	locked_part(
		sge::renderer::raw_pointer,
		sge::renderer::lock_segment const &,
		sge::renderer::lock_flags::method
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::raw_pointer
	data() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vertex::first
	pos() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vertex::count
	count() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::lock_flags::method
	lock_flags() const;
private:
	sge::renderer::raw_pointer data_;

	sge::renderer::lock_segment segment_;

	sge::renderer::lock_flags::method lock_flags_;
};

}
}
}
}

#endif
