//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_ASSIGN_POST_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_ASSIGN_POST_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/detail/config/is_intrusive.hpp>
#include <sge/sprite/roles/connection.hpp>
#include <fcppt/not.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::detail
{

template <typename Choices>
std::enable_if_t<sge::sprite::detail::config::is_intrusive<Choices>::value, void>
assign_post(sge::sprite::object<Choices> &_this)
{
  _this.template get<sge::sprite::roles::connection>().get().add(_this);
}

template <typename Choices>
std::enable_if_t<fcppt::not_(sge::sprite::detail::config::is_intrusive<Choices>::value), void>
assign_post(sge::sprite::object<Choices> &)
{
}

}

#endif
