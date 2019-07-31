//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_VECTOR_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_VECTOR_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vf/dynamic/element_count.hpp>
#include <sge/renderer/vf/dynamic/element_type.hpp>
#include <sge/renderer/vf/dynamic/vector_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

class vector
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	vector(
		sge::renderer::vf::dynamic::element_type,
		sge::renderer::vf::dynamic::element_count
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vf::dynamic::element_type
	element_type() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vf::dynamic::element_count
	element_count() const;
private:
	sge::renderer::vf::dynamic::element_type element_type_;

	sge::renderer::vf::dynamic::element_count element_count_;
};

}
}
}
}

#endif
