//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_PIXEL_OBJECT_HPP_INCLUDED
#define SGE_IMAGE_PIXEL_OBJECT_HPP_INCLUDED

#include <sge/image/has_format.hpp>
#include <sge/image/mizuiro_color_traits.hpp> // IWYU pragma: keep
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/pixel/elements.hpp>
#include <sge/image/pixel/mizuiro_type_fwd.hpp>
#include <sge/image/pixel/object_fwd.hpp>
#include <fcppt/variant/from_list.hpp>

namespace sge::image::pixel
{

template <typename Tag>
class object
{
public:
  using elements = sge::image::pixel::elements<Tag>;

  using variant = fcppt::variant::from_list<elements>;

  template <typename Format>
  explicit object(sge::image::pixel::mizuiro_type<Format> const &_color) : object(variant{_color})
  {
    static_assert(sge::image::has_format<Tag, Format>::value, "Invalid format.");
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
