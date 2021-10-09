//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_INDEX_CONST_PROXY_IMPL_HPP_INCLUDED
#define SGE_RENDERER_INDEX_CONST_PROXY_IMPL_HPP_INCLUDED

#include <sge/renderer/index/const_proxy_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstring>
#include <fcppt/config/external_end.hpp>

template <typename Format>
sge::renderer::index::const_proxy<Format>::const_proxy(pointer const _data) : data_{_data}
{
}

template <typename Format>
typename sge::renderer::index::const_proxy<Format>::value_type
sge::renderer::index::const_proxy<Format>::get() const
{
  value_type ret;

  std::memcpy(&ret, data_, sizeof(value_type));

  return ret;
}

#endif
