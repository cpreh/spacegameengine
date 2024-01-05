//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_ASSIGN_PRE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_ASSIGN_PRE_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/detail/unlink.hpp>
#include <sge/sprite/detail/config/is_intrusive.hpp>
#include <sge/sprite/intrusive/detail/object_base_hook.hpp> // IWYU pragma: keep
#include <fcppt/not.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::detail
{

template <typename Choices>
std::enable_if_t<sge::sprite::detail::config::is_intrusive<Choices>::value, void>
assign_pre(sge::sprite::object<Choices> &_this, sge::sprite::object<Choices> const &_other)
{
  sge::sprite::detail::unlink(_this);

  _this.sge::sprite::intrusive::detail::object_base_hook::operator=(_other);
}

template <typename Choices>
std::enable_if_t<fcppt::not_(sge::sprite::detail::config::is_intrusive<Choices>::value), void>
assign_pre(sge::sprite::object<Choices> &, sge::sprite::object<Choices> const &)
{
}

}

#endif
