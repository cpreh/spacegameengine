//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_BASIC_VIEW_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_BASIC_VIEW_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vf/dynamic/basic_view_fwd.hpp>
#include <sge/renderer/vf/dynamic/const_part_ref.hpp>
#include <sge/renderer/vf/dynamic/part_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>


namespace sge::renderer::vf::dynamic
{

template<
	typename Pointer
>
class basic_view
{
public:
	using
	pointer
	=
	Pointer;

	using
	size_type
	=
	sge::renderer::vertex::count;

	SGE_RENDERER_DETAIL_SYMBOL
	basic_view(
		pointer data,
		size_type elements,
		sge::renderer::vf::dynamic::const_part_ref,
		sge::renderer::vf::dynamic::part_index
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	pointer
	data() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	size_type
	size() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vf::dynamic::part const &
	part() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vf::dynamic::part_index
	part_index() const;
private:
	pointer data_;

	size_type size_;

	sge::renderer::vf::dynamic::const_part_ref part_;

	sge::renderer::vf::dynamic::part_index part_index_;
};

}

#endif
