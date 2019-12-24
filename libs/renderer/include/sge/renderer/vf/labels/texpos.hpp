//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_LABELS_TEXPOS_HPP_INCLUDED
#define SGE_RENDERER_VF_LABELS_TEXPOS_HPP_INCLUDED

#include <sge/renderer/vf/index_type.hpp>
#include <fcppt/record/make_label_arg.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace labels
{

FCPPT_RECORD_MAKE_LABEL_ARG(
	texpos,
	sge::renderer::vf::index_type
);

}
}
}
}

#endif
