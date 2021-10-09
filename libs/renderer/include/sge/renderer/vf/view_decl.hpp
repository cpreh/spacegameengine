//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_VIEW_DECL_HPP_INCLUDED
#define SGE_RENDERER_VF_VIEW_DECL_HPP_INCLUDED

#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vf/is_const_tag.hpp>
#include <sge/renderer/vf/is_part.hpp>
#include <sge/renderer/vf/iterator_fwd.hpp>
#include <sge/renderer/vf/pointer.hpp>
#include <sge/renderer/vf/view_fwd.hpp>
#include <sge/renderer/vf/dynamic/basic_view_fwd.hpp>

namespace sge::renderer::vf
{

template <typename Part, typename Constness>
class view
{
public:
  static_assert(sge::renderer::vf::is_part<Part>::value);

  static_assert(sge::renderer::vf::is_const_tag<Constness>::value);

  using iterator = sge::renderer::vf::iterator<Part, Constness>;

  using pointer = sge::renderer::vf::pointer<Constness>;

  using dynamic_view_type = sge::renderer::vf::dynamic::basic_view<pointer>;

  using size_type = sge::renderer::vertex::count;

  explicit view(dynamic_view_type const &);

  template <typename OtherView>
  explicit view(sge::renderer::vf::dynamic::basic_view<OtherView> const &);

  [[nodiscard]] iterator begin() const;

  [[nodiscard]] iterator end() const;

private:
  pointer data_;

  size_type size_;
};

}

#endif
