//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_VF_CONVERT_EXTRA_TYPE_VISITOR_HPP_INCLUDED
#define SGE_D3D9_VF_CONVERT_EXTRA_TYPE_VISITOR_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/vf/dynamic/color_fwd.hpp>
#include <sge/renderer/vf/dynamic/vector_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace vf
{
namespace convert
{

class extra_type_visitor
{
public:
	typedef D3DDECLTYPE result_type;

	result_type
	operator()(
		sge::renderer::vf::dynamic::color const &
	) const;

	result_type
	operator()(
		sge::renderer::vf::dynamic::vector const &
	) const;
};

}
}
}
}

#endif
