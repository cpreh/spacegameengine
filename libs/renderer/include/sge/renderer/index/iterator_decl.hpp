//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_INDEX_ITERATOR_DECL_HPP_INCLUDED
#define SGE_RENDERER_INDEX_ITERATOR_DECL_HPP_INCLUDED

#include <sge/renderer/index/is_const_tag.hpp>
#include <sge/renderer/index/is_format.hpp>
#include <sge/renderer/index/iterator_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/index/pointer.hpp>
#include <sge/renderer/index/detail/iterator_base.hpp>
#include <fcppt/iterator/base_impl.hpp> // IWYU pragma: keep

namespace sge::renderer::index
{

template <typename Format, typename Constness>
class iterator final : public sge::renderer::index::detail::iterator_base<Format, Constness>
{
  using base = sge::renderer::index::detail::iterator_base<Format, Constness>;

  static_assert(sge::renderer::index::is_format<Format>::value);

  static_assert(sge::renderer::index::is_const_tag<Constness>::value);

public:
  using value_type = typename base::value_type;

  using reference = typename base::reference;

  using pointer = sge::renderer::index::pointer<Constness>;

  using difference_type = typename base::difference_type;

  using iterator_category = typename base::iterator_category;

  explicit iterator(pointer);

  [[nodiscard]] pointer data() const;

  iterator &operator+=(difference_type);

  void increment();

  [[nodiscard]] bool equal(iterator const &) const;

  [[nodiscard]] reference dereference() const;

private:
  pointer data_;
};

}

#endif
