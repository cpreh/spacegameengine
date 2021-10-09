//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_TEXTURE_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sge/renderer/texture/base_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace sge
{
namespace renderer
{
namespace texture
{

using base_unique_ptr = fcppt::unique_ptr<sge::renderer::texture::base>;

}
}
}

#endif
