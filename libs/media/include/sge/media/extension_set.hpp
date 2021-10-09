//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_MEDIA_EXTENSION_SET_HPP_INCLUDED
#define SGE_MEDIA_EXTENSION_SET_HPP_INCLUDED

#include <sge/media/extension.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_set>
#include <fcppt/config/external_end.hpp>

namespace sge::media
{

using extension_set = std::unordered_set<sge::media::extension>;

}

#endif
