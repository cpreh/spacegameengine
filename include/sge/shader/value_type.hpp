#ifndef SGE_SHADER_VALUE_TYPE_HPP_INCLUDED
#define SGE_SHADER_VALUE_TYPE_HPP_INCLUDED

#include <sge/shader/scalar.hpp>
#include <sge/shader/vec2.hpp>
#include <sge/shader/vec3.hpp>
#include <sge/shader/vec4.hpp>
#include <sge/shader/mat4.hpp>
#include <fcppt/variant/object_decl.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sge
{
namespace shader
{
typedef
fcppt::variant::object
<
	boost::mpl::vector6
	<
		vec2,
		vec3,
		vec4,
		mat4,
		scalar,
		int
	>
>
value_type;
}
}

#endif
