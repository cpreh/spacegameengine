#ifndef SGE_SCENIC_SKY_DOME_VF_FORMAT_HPP_INCLUDED
#define SGE_SCENIC_SKY_DOME_VF_FORMAT_HPP_INCLUDED

#include <sge/renderer/vf/format.hpp>
#include <sge/scenic/sky/dome/vf/format_part.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace scenic
{
namespace sky
{
namespace dome
{
namespace vf
{
typedef
sge::renderer::vf::format
<
	boost::mpl::vector1<sge::scenic::sky::dome::vf::format_part>
>
format;
}
}
}
}
}

#endif

