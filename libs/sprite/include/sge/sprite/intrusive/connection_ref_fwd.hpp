//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_INTRUSIVE_CONNECTION_REF_FWD_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_CONNECTION_REF_FWD_HPP_INCLUDED

#include <sge/sprite/intrusive/connection_fwd.hpp>
#include <fcppt/reference_fwd.hpp>

namespace sge::sprite::intrusive
{

template <typename Choices>
using connection_ref = fcppt::reference<sge::sprite::intrusive::connection<Choices>>;

}

#endif
