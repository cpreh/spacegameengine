//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_TEXPOS_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_TEXPOS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vf/dynamic/index.hpp>
#include <sge/renderer/vf/dynamic/texpos_fwd.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

class texpos
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	texpos(
		sge::renderer::vf::dynamic::vector const &,
		sge::renderer::vf::dynamic::index
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vf::dynamic::vector const &
	type() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vf::dynamic::index
	index() const;
private:
	sge::renderer::vf::dynamic::vector type_;

	sge::renderer::vf::dynamic::index index_;
};

}
}
}
}

#endif
