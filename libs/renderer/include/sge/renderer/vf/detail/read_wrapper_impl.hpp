//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_DETAIL_READ_WRAPPER_IMPL_HPP_INCLUDED
#define SGE_RENDERER_VF_DETAIL_READ_WRAPPER_IMPL_HPP_INCLUDED

#include <sge/renderer/vf/detail/read_wrapper_decl.hpp> // IWYU pragma: export
#include <fcppt/no_init.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

template <typename T, typename Enable>
inline sge::renderer::vf::detail::read_wrapper<T, Enable>::read_wrapper() : value_(fcppt::no_init())
{
}

namespace sge::renderer::vf::detail
{
template <typename T, typename Enable>
inline read_wrapper<T, Enable>::~read_wrapper() = default;
}

template <typename T, typename Enable>
inline T &sge::renderer::vf::detail::read_wrapper<T, Enable>::get()
{
  return value_;
}

template <typename T>
inline sge::renderer::vf::detail::read_wrapper<
    T,
    std::enable_if_t<std::is_fundamental_v<T>>>::
    read_wrapper() // NOLINT(hicpp-use-equals-default,modernize-use-equals-default)
// Don't initialize value_
{
}

namespace sge::renderer::vf::detail
{
template <typename T>
inline read_wrapper<T, std::enable_if_t<std::is_fundamental_v<T>>>::~read_wrapper() = default;
}

template <typename T>
inline T &
sge::renderer::vf::detail::read_wrapper<T, std::enable_if_t<std::is_fundamental_v<T>>>::get()
{
  return value_;
}

#endif
