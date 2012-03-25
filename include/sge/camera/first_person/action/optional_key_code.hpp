#ifndef SGE_CAMERA_FIRST_PERSON_ACTION_OPTIONAL_KEY_CODE_HPP_INCLUDED
#define SGE_CAMERA_FIRST_PERSON_ACTION_OPTIONAL_KEY_CODE_HPP_INCLUDED

#include <sge/input/keyboard/key_code.hpp>
#include <fcppt/optional_fwd.hpp>

namespace sge
{
namespace camera
{
namespace first_person
{
namespace action
{
typedef
fcppt::optional<input::keyboard::key_code::type>
optional_key_code;
}
}
}
}

#endif

