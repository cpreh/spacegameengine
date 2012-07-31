#ifndef SGE_MODEL_OBJ_VF_FORMAT_PART_HPP_INCLUDED
#define SGE_MODEL_OBJ_VF_FORMAT_PART_HPP_INCLUDED

#include <sge/model/obj/vf/normal.hpp>
#include <sge/model/obj/vf/position.hpp>
#include <sge/model/obj/vf/texcoord.hpp>
#include <sge/renderer/vf/part.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace model
{
namespace obj
{
namespace vf
{
typedef
sge::renderer::vf::part
<
	boost::mpl::vector3
	<
		sge::model::obj::vf::position,
		sge::model::obj::vf::normal,
		sge::model::obj::vf::texcoord
	>
>
format_part;
}
}
}
}

#endif

