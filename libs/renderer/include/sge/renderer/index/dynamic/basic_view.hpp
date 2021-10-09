//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_INDEX_DYNAMIC_BASIC_VIEW_HPP_INCLUDED
#define SGE_RENDERER_INDEX_DYNAMIC_BASIC_VIEW_HPP_INCLUDED

#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/index/dynamic/basic_view_fwd.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::index::dynamic
{

template <bool IsConst>
class basic_view
{
public:
  using pointer =
      std::conditional_t<IsConst, sge::renderer::const_raw_pointer, sge::renderer::raw_pointer>;

  using size_type = sge::renderer::size_type;

  SGE_RENDERER_DETAIL_SYMBOL
  basic_view(pointer, size_type, sge::renderer::index::dynamic::format);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL pointer data() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL size_type size() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::index::dynamic::format format() const;

private:
  pointer data_;

  size_type size_;

  sge::renderer::index::dynamic::format format_;
};

}

#endif
