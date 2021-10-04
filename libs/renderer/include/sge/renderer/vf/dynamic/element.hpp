//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_ELEMENT_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_ELEMENT_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vf/dynamic/any.hpp>
#include <sge/renderer/vf/dynamic/element_fwd.hpp>


namespace sge::renderer::vf::dynamic
{

class element
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	element(
		sge::renderer::vf::dynamic::any const &
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vf::dynamic::any const &
	info() const;
private:
	sge::renderer::vf::dynamic::any info_;
};

SGE_RENDERER_DETAIL_SYMBOL
bool
operator==(
	sge::renderer::vf::dynamic::element const &,
	sge::renderer::vf::dynamic::element const &
);

}

#endif
