//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_OBJECT_DECL_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_OBJECT_DECL_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/image/color/impl/dynamic/format/object_base_decl.hpp>
#include <sge/image/color/impl/dynamic/format/object_fwd.hpp> // IWYU pragma: keep
#include <mizuiro/size_type.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace sge::image::color::impl::dynamic::format
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template <typename Space, typename BaseType, mizuiro::size_type NumChannels>
class object final
    : public sge::image::color::impl::dynamic::format::object_base<Space, BaseType, NumChannels>
{
  FCPPT_NONMOVABLE(object);

public:
  using base = sge::image::color::impl::dynamic::format::object_base<Space, BaseType, NumChannels>;

  using color_format_type = sge::image::color::format;

  template <typename Layout>
  object(Layout const &, color_format_type) noexcept;

  ~object();

  color_format_type const color_format; // NOLINT(misc-non-private-member-variables-in-classes)
};

FCPPT_PP_POP_WARNING

}

#endif
