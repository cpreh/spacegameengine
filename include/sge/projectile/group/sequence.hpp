#ifndef SGE_PROJECTILE_GROUP_SEQUENCE_HPP_INCLUDED
#define SGE_PROJECTILE_GROUP_SEQUENCE_HPP_INCLUDED

#include <sge/projectile/group/object_fwd.hpp>
#include <fcppt/reference_wrapper.hpp>
#include <vector>

namespace sge
{
namespace projectile
{
namespace group
{
typedef
std::vector<fcppt::reference_wrapper<object> >
sequence;
}
}
}

#endif
