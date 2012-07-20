#ifndef SGE_SHADER_PIXEL_PROFILE_HPP_INCLUDED
#define SGE_SHADER_PIXEL_PROFILE_HPP_INCLUDED

#include <sge/cg/profile/object_fwd.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace shader
{
FCPPT_MAKE_STRONG_TYPEDEF(
	sge::cg::profile::object const &,
	pixel_profile);
}
}

#endif

