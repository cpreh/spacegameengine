//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_LIST_DECL_HPP_INCLUDED
#define SGE_SYSTEMS_LIST_DECL_HPP_INCLUDED

#include <sge/systems/list_fwd.hpp> // IWYU pragma: keep
#include <fcppt/tuple/push_back_result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::systems
{

template <typename Inits>
class list
{
public:
  explicit list(Inits &&);

  template <typename Param>
  [[nodiscard]] list<fcppt::tuple::push_back_result<Inits, std::remove_cvref_t<Param>>>
  operator()(Param &&) const;

  [[nodiscard]] Inits &get();

  [[nodiscard]] Inits const &get() const;

private:
  Inits inits_;
};

}

#endif
