//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_ITERATOR_DECL_HPP_INCLUDED
#define SGE_RENDERER_VF_ITERATOR_DECL_HPP_INCLUDED

#include <sge/renderer/vf/is_const_tag.hpp>
#include <sge/renderer/vf/is_part.hpp>
#include <sge/renderer/vf/iterator_fwd.hpp>
#include <sge/renderer/vf/pointer.hpp>
#include <sge/renderer/vf/view_fwd.hpp>
#include <sge/renderer/vf/detail/iterator_base.hpp>

namespace sge::renderer::vf
{

template <typename Part, typename Constness>
class iterator final : public sge::renderer::vf::detail::iterator_base<Part, Constness>
{
  using base = sge::renderer::vf::detail::iterator_base<Part, Constness>;

  static_assert(sge::renderer::vf::is_part<Part>::value);

  static_assert(sge::renderer::vf::is_const_tag<Constness>::value);

public:
  using value_type = typename base::value_type;

  using reference = typename base::reference;

  using pointer = typename base::pointer;

  using difference_type = typename base::difference_type;

  using iterator_category = typename base::iterator_category;

  using vertex_type = value_type;

  using internal_pointer = sge::renderer::vf::pointer<Constness>;

  static difference_type stride();

  explicit iterator(internal_pointer);

  void increment();

  [[nodiscard]] bool equal(iterator const &) const;

  [[nodiscard]] vertex_type dereference() const;

  iterator &operator+=(difference_type);

private:
  internal_pointer data_;

  template <typename, typename>
  friend class sge::renderer::vf::view;
};

}

#endif
