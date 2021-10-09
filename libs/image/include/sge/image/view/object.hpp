//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_VIEW_OBJECT_HPP_INCLUDED
#define SGE_IMAGE_VIEW_OBJECT_HPP_INCLUDED

#include <sge/image/has_format.hpp>
#include <sge/image/mizuiro_color_traits.hpp>
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/view/elements.hpp>
#include <sge/image/view/mizuiro_type_fwd.hpp>
#include <sge/image/view/object_fwd.hpp>
#include <mizuiro/nonconst_tag.hpp>
#include <fcppt/variant/from_list.hpp>

namespace sge::image::view
{

template <typename Tag>
class object
{
public:
  using elements = sge::image::view::elements<Tag>;

  using variant = fcppt::variant::from_list<elements>;

  template <typename Format>
  explicit object(sge::image::view::mizuiro_type<Format, mizuiro::nonconst_tag> const &_view)
      : object(variant{_view})
  {
    static_assert(
        sge::image::has_format<
            sge::image::traits::image::color_tag<Tag>,
            typename Format::color_format>::value,
        "Invalid format.");
  }

  SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
  explicit object(variant const &);

  SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
  object(object const &);

  SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
  object(object &&) noexcept;

  SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
  object &operator=(object const &);

  SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
  object &operator=(object &&) noexcept;

  SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
  ~object();

  [[nodiscard]] SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL variant const &get() const;

private:
  variant variant_;
};

}

#endif
