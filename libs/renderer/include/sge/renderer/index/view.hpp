//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_INDEX_VIEW_HPP_INCLUDED
#define SGE_RENDERER_INDEX_VIEW_HPP_INCLUDED

#include <sge/core/detail/export_class_declaration.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/index/const_tag.hpp>
#include <sge/renderer/index/format.hpp>
#include <sge/renderer/index/is_const_tag.hpp>
#include <sge/renderer/index/is_format.hpp>
#include <sge/renderer/index/iterator_fwd.hpp>
#include <sge/renderer/index/nonconst_tag.hpp>
#include <sge/renderer/index/pointer.hpp>
#include <sge/renderer/index/view_fwd.hpp>
#include <sge/renderer/index/detail/pp_formats.hpp>
#include <sge/renderer/index/dynamic/basic_view_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::index
{

template <typename Format, typename Constness>
class view
{
public:
  static_assert(sge::renderer::index::is_format<Format>::value);

  static_assert(sge::renderer::index::is_const_tag<Constness>::value);

  using format_type = Format;

  using value_type = typename format_type::index_type;

  using pointer = sge::renderer::index::pointer<Constness>;

  using size_type = sge::renderer::size_type;

  using iterator = sge::renderer::index::iterator<Format, Constness>;

  using dynamic_view_type = sge::renderer::index::dynamic::basic_view<
      std::is_same_v<Constness, sge::renderer::index::const_tag>>;

  SGE_RENDERER_DETAIL_SYMBOL
  view(pointer, size_type);

  SGE_RENDERER_DETAIL_SYMBOL
  explicit view(dynamic_view_type const &);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL pointer data() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL size_type size() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL iterator begin() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL iterator end() const;

private:
  pointer data_;

  size_type size_;
};

}

#define SGE_RENDERER_INDEX_DETAIL_DECLARE_VIEW_BASE(format, constness) \
  extern template class SGE_CORE_DETAIL_EXPORT_CLASS_DECLARATION \
      sge::renderer::index::view<format, constness>;

#define SGE_RENDERER_INDEX_DETAIL_DECLARE_VIEW(seq, _, format) \
  SGE_RENDERER_INDEX_DETAIL_DECLARE_VIEW_BASE(format, sge::renderer::index::nonconst_tag)

#define SGE_RENDERER_INDEX_DETAIL_DECLARE_CONST_VIEW(seq, _, format) \
  SGE_RENDERER_INDEX_DETAIL_DECLARE_VIEW_BASE(format, sge::renderer::index::const_tag)

BOOST_PP_SEQ_FOR_EACH(
    SGE_RENDERER_INDEX_DETAIL_DECLARE_VIEW, _, SGE_RENDERER_INDEX_DETAIL_PP_FORMATS)

BOOST_PP_SEQ_FOR_EACH(
    SGE_RENDERER_INDEX_DETAIL_DECLARE_CONST_VIEW, _, SGE_RENDERER_INDEX_DETAIL_PP_FORMATS)

#endif
