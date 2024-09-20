//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_STORE_OBJECT_HPP_INCLUDED
#define SGE_IMAGE_STORE_OBJECT_HPP_INCLUDED

#include <sge/image/dim_fwd.hpp>
#include <sge/image/has_format.hpp>
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/store/basic_fwd.hpp>
#include <sge/image/store/elements.hpp>
#include <sge/image/store/object_fwd.hpp> // IWYU pragma: keep
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>
#include <fcppt/no_init_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/variant/from_list.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace sge::image::store
{

template <typename Tag>
class object
{
  FCPPT_NONCOPYABLE(object);

public:
  using store_elements = sge::image::store::elements<Tag>;

  using variant = fcppt::variant::from_list<store_elements>;

  using dim = sge::image::dim<Tag>;

  using format = sge::image::traits::pixel::format<sge::image::traits::image::color_tag<Tag>>;

  template <typename Format>
  explicit object(sge::image::store::basic<Format> &&_element)
      : object(variant{std::move(_element)})
  {
    static_assert(
        sge::image::has_format<
            sge::image::traits::image::color_tag<Tag>,
            typename Format::color_format>::value,
        "Invalid format store.");
  }

  SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
  explicit object(variant &&);

  SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
  object(format, dim const &, fcppt::no_init const &);

  SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
  object(object &&) noexcept;

  SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
  object &operator=(object &&) noexcept;

  SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
  ~object();

  [[nodiscard]] SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL variant &get();

  [[nodiscard]] SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL variant const &get() const;

private:
  variant variant_;
};

}

#endif
