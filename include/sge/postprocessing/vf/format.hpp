#ifndef SGE_POSTPROCESSING_VF_FORMAT_HPP_INCLUDED
#define SGE_POSTPROCESSING_VF_FORMAT_HPP_INCLUDED

#include <sge/postprocessing/vf/format_part.hpp>
#include <sge/renderer/vf/format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace postprocessing
{
namespace vf
{
typedef
sge::renderer::vf::format
<
	boost::mpl::vector1<sge::postprocessing::vf::format_part>
>
format;
}
}
}

#endif

