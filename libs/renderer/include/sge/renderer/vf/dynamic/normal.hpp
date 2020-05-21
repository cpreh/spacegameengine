//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_NORMAL_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_NORMAL_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vf/dynamic/element_type.hpp>
#include <sge/renderer/vf/dynamic/normal_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

class normal
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	normal(
		sge::renderer::vf::dynamic::element_type
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vf::dynamic::element_type
	element_type() const;
private:
	sge::renderer::vf::dynamic::element_type element_type_;
};

SGE_RENDERER_DETAIL_SYMBOL
bool
operator==(
	sge::renderer::vf::dynamic::normal const &,
	sge::renderer::vf::dynamic::normal const &
);

}
}
}
}

#endif
