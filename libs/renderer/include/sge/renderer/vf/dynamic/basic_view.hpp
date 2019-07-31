//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_BASIC_VIEW_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_BASIC_VIEW_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vf/dynamic/basic_view_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_cref.hpp>
#include <sge/renderer/vf/dynamic/part_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

template<
	typename Pointer
>
class basic_view
{
public:
	typedef
	Pointer
	pointer;

	typedef
	sge::renderer::vertex::count
	size_type;

	SGE_RENDERER_DETAIL_SYMBOL
	basic_view(
		pointer data,
		size_type elements,
		sge::renderer::vf::dynamic::part_cref,
		sge::renderer::vf::dynamic::part_index
	);

	SGE_RENDERER_DETAIL_SYMBOL
	pointer
	data() const;

	SGE_RENDERER_DETAIL_SYMBOL
	size_type
	size() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vf::dynamic::part const &
	part() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vf::dynamic::part_index
	part_index() const;
private:
	pointer data_;

	size_type size_;

	sge::renderer::vf::dynamic::part_cref part_;

	sge::renderer::vf::dynamic::part_index part_index_;
};

}
}
}
}

#endif
