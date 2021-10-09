//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/core/impl/export_class_instantiation.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/index/const_tag.hpp>
#include <sge/renderer/index/iterator.hpp>
#include <sge/renderer/index/nonconst_tag.hpp>
#include <sge/renderer/index/view.hpp>
#include <sge/renderer/index/detail/pp_formats.hpp>
#include <sge/renderer/index/dynamic/const_view.hpp>
#include <sge/renderer/index/dynamic/make_format.hpp>
#include <sge/renderer/index/dynamic/view.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>

template <typename Format, typename Constness>
sge::renderer::index::view<Format, Constness>::view(pointer const _data, size_type const _size)
    : data_{_data}, size_{_size}
{
  if (this->data_ == nullptr)
  {
    throw sge::renderer::exception{FCPPT_TEXT("Data in index::view is null!")};
  }
}

template <typename Format, typename Constness>
sge::renderer::index::view<Format, Constness>::view(dynamic_view_type const &_view)
    : data_(_view.data()), size_(_view.size())
{
  if (_view.format() != sge::renderer::index::dynamic::make_format<Format>())
  {
    throw sge::renderer::exception{FCPPT_TEXT("Mismatched formats in index::view!")};
  }
}

template <typename Format, typename Constness>
typename sge::renderer::index::view<Format, Constness>::pointer
sge::renderer::index::view<Format, Constness>::data() const
{
  return this->data_;
}

template <typename Format, typename Constness>
sge::renderer::size_type sge::renderer::index::view<Format, Constness>::size() const
{
  return this->size_;
}

template <typename Format, typename Constness>
typename sge::renderer::index::view<Format, Constness>::iterator
sge::renderer::index::view<Format, Constness>::begin() const
{
  return iterator(this->data());
}

template <typename Format, typename Constness>
typename sge::renderer::index::view<Format, Constness>::iterator
sge::renderer::index::view<Format, Constness>::end() const
{
  return this->begin() + fcppt::cast::to_signed(this->size());
}

#define SGE_RENDERER_INDEX_DEFINE_VIEW_BASE(format, constness) \
  template class SGE_CORE_IMPL_EXPORT_CLASS_INSTANTIATION \
      sge::renderer::index::view<format, constness>;

#define SGE_RENDERER_INDEX_DEFINE_VIEW(seq, _, format) \
  SGE_RENDERER_INDEX_DEFINE_VIEW_BASE(format, sge::renderer::index::nonconst_tag)

#define SGE_RENDERER_INDEX_DEFINE_CONST_VIEW(seq, _, format) \
  SGE_RENDERER_INDEX_DEFINE_VIEW_BASE(format, sge::renderer::index::const_tag)

BOOST_PP_SEQ_FOR_EACH(SGE_RENDERER_INDEX_DEFINE_VIEW, _, SGE_RENDERER_INDEX_DETAIL_PP_FORMATS)

BOOST_PP_SEQ_FOR_EACH(SGE_RENDERER_INDEX_DEFINE_CONST_VIEW, _, SGE_RENDERER_INDEX_DETAIL_PP_FORMATS)
