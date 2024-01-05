//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_BUFFERS_OPTION_TO_RESOURCE_FLAGS_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_OPTION_TO_RESOURCE_FLAGS_HPP_INCLUDED

#include <sge/renderer/resource_flags_field.hpp>
#include <sge/sprite/buffers/option_fwd.hpp>
#include <sge/sprite/detail/symbol.hpp>

namespace sge::sprite::buffers
{

SGE_SPRITE_DETAIL_SYMBOL
sge::renderer::resource_flags_field option_to_resource_flags(sge::sprite::buffers::option);

}

#endif
