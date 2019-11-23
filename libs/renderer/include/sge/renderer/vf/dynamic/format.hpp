//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_FORMAT_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_FORMAT_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vf/dynamic/format_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_list.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

class format
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	format(
		sge::renderer::vf::dynamic::part_list &&
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vf::dynamic::part_list const &
	parts() const;
private:
	sge::renderer::vf::dynamic::part_list parts_;
};

}
}
}
}

#endif
