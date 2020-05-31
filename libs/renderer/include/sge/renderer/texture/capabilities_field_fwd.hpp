//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TEXTURE_CAPABILITIES_FIELD_FWD_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_CAPABILITIES_FIELD_FWD_HPP_INCLUDED

#include <sge/renderer/texture/capabilities.hpp>
#include <fcppt/container/bitfield/enum_object_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{

using
capabilities_field
=
fcppt::container::bitfield::enum_object<
	sge::renderer::texture::capabilities
>;

}
}
}

#endif
