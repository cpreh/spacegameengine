//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_EXTRA_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_EXTRA_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vf/dynamic/extra_any.hpp>
#include <sge/renderer/vf/dynamic/extra_fwd.hpp>
#include <sge/renderer/vf/dynamic/index.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

class extra
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	extra(
		sge::renderer::vf::dynamic::extra_any const &,
		sge::renderer::vf::dynamic::index
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vf::dynamic::extra_any const &
	type() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vf::dynamic::index
	index() const;
private:
	sge::renderer::vf::dynamic::extra_any type_;

	sge::renderer::vf::dynamic::index index_;
};

}
}
}
}

#endif
