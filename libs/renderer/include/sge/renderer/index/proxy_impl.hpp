//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_INDEX_PROXY_IMPL_HPP_INCLUDED
#define SGE_RENDERER_INDEX_PROXY_IMPL_HPP_INCLUDED

#include <sge/renderer/index/const_proxy_impl.hpp> // IWYU pragma: keep
#include <sge/renderer/index/proxy_decl.hpp> // IWYU pragma: export
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage_in_libc_call.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstring>
#include <fcppt/config/external_end.hpp>

template <typename Format>
sge::renderer::index::proxy<Format>::proxy(pointer const _data) : data_{_data}
{
}

template <typename Format>
sge::renderer::index::proxy<Format> &
sge::renderer::index::proxy<Format>::operator=(value_type const _value)
{
  this->set(_value);

  return *this;
}

template <typename Format>
void sge::renderer::index::proxy<Format>::set(value_type const _value)
{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE_IN_LIBC_CALL
  std::memcpy(this->data_, &_value, sizeof(value_type));
FCPPT_PP_POP_WARNING
}

template <typename Format>
typename sge::renderer::index::proxy<Format>::value_type
sge::renderer::index::proxy<Format>::get() const
{
  return sge::renderer::index::const_proxy<Format>(this->data_).get();
}

#endif
