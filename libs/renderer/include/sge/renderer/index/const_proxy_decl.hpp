//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_INDEX_CONST_PROXY_DECL_HPP_INCLUDED
#define SGE_RENDERER_INDEX_CONST_PROXY_DECL_HPP_INCLUDED

#include <sge/renderer/index/const_proxy_fwd.hpp>
#include <sge/renderer/index/const_tag.hpp>
#include <sge/renderer/index/format.hpp>
#include <sge/renderer/index/is_format.hpp>
#include <sge/renderer/index/pointer.hpp>

namespace sge::renderer::index
{

template <typename Format>
class const_proxy
{
public:
  static_assert(sge::renderer::index::is_format<Format>::value);

  using value_type = typename Format::index_type;

  using pointer = sge::renderer::index::pointer<sge::renderer::index::const_tag>;

  explicit const_proxy(pointer);

  value_type get() const;

private:
  pointer data_;
};

}

#endif
