//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_FONT_DRAW_STATIC_TEXT_HPP_INCLUDED
#define SGE_FONT_DRAW_STATIC_TEXT_HPP_INCLUDED

#include <sge/font/dim_fwd.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/font/rect_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_fwd.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/vector_fwd.hpp>
#include <sge/font/draw/set_matrices_fwd.hpp>
#include <sge/font/draw/set_states_fwd.hpp>
#include <sge/font/draw/static_text_fwd.hpp>
#include <sge/font/draw/detail/static_text_impl_fwd.hpp>
#include <sge/font/draw/detail/symbol.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/texture/emulate_srgb_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace sge::font::draw
{

class static_text
{
  FCPPT_NONCOPYABLE(static_text);

public:
  SGE_FONT_DRAW_DETAIL_SYMBOL
  static_text(
      sge::renderer::device::ffp_ref,
      sge::font::object_ref,
      sge::font::string const &,
      sge::font::text_parameters const &,
      sge::font::vector const &,
      sge::image::color::any::object const &,
      sge::renderer::texture::emulate_srgb);

  SGE_FONT_DRAW_DETAIL_SYMBOL
  static_text(static_text &&) noexcept;

  SGE_FONT_DRAW_DETAIL_SYMBOL
  static_text &operator=(static_text &&) noexcept;

  SGE_FONT_DRAW_DETAIL_SYMBOL
  ~static_text();

  SGE_FONT_DRAW_DETAIL_SYMBOL
  void draw(sge::renderer::context::ffp & // NOLINT(google-runtime-references)
  ) const; // NOLINT(google-runtime-references)

  SGE_FONT_DRAW_DETAIL_SYMBOL
  void draw_advanced(
      sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
      sge::font::draw::set_matrices const &,
      sge::font::draw::set_states const &) const;

  SGE_FONT_DRAW_DETAIL_SYMBOL
  void pos(sge::font::vector const &);

  SGE_FONT_DRAW_DETAIL_SYMBOL
  void color(sge::image::color::any::object const &);

  [[nodiscard]] SGE_FONT_DRAW_DETAIL_SYMBOL sge::font::vector pos() const;

  [[nodiscard]] SGE_FONT_DRAW_DETAIL_SYMBOL sge::font::rect rect() const;

  [[nodiscard]] SGE_FONT_DRAW_DETAIL_SYMBOL sge::font::dim logical_size() const;

  [[nodiscard]] SGE_FONT_DRAW_DETAIL_SYMBOL sge::font::text const &text() const;

private:
  using impl_ptr = fcppt::unique_ptr<sge::font::draw::detail::static_text_impl>;

  impl_ptr impl_;
};

}

#endif
