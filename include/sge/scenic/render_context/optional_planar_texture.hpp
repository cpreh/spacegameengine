#ifndef SGE_SCENIC_RENDER_CONTEXT_OPTIONAL_PLANAR_TEXTURE_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_OPTIONAL_PLANAR_TEXTURE_HPP_INCLUDED

#include <sge/renderer/texture/planar_fwd.hpp>
#include <fcppt/optional.hpp>

namespace sge
{
namespace scenic
{
namespace render_context
{
typedef
fcppt::optional<sge::renderer::texture::planar &>
optional_planar_texture;
}
}
}

#endif
