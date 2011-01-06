#ifndef SGE_SHADER_TEXTURE_VARIANT_HPP_INCLUDED
#define SGE_SHADER_TEXTURE_VARIANT_HPP_INCLUDED

#include <sge/renderer/texture_ptr.hpp>
#include <sge/renderer/cube_texture_ptr.hpp>
#include <sge/renderer/volume_texture_ptr.hpp>
#include <fcppt/variant/object.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sge
{
namespace shader
{
typedef
fcppt::variant::object
<
	boost::mpl::vector3
	<
		sge::renderer::texture_ptr,
		sge::renderer::volume_texture_ptr,
		sge::renderer::cube_texture_ptr
	>
>
texture_variant;
}
}

#endif
