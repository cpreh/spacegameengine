//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_LINE_DRAWER_LINE_HPP_INCLUDED
#define SGE_LINE_DRAWER_LINE_HPP_INCLUDED

#include <sge/image/color/any/object_fwd.hpp>
#include <sge/line_drawer/color.hpp>
#include <sge/line_drawer/color_format.hpp>
#include <sge/line_drawer/detail/symbol.hpp>
#include <sge/renderer/vector3.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp>

namespace sge::line_drawer
{

class line
{
public:
  FCPPT_DECLARE_STRONG_TYPEDEF(sge::renderer::vector3, begin_type);
  FCPPT_DECLARE_STRONG_TYPEDEF(sge::renderer::vector3, end_type);
  FCPPT_DECLARE_STRONG_TYPEDEF(sge::image::color::any::object, begin_color_type);
  FCPPT_DECLARE_STRONG_TYPEDEF(sge::image::color::any::object, end_color_type);

  SGE_LINE_DRAWER_DETAIL_SYMBOL
  line(begin_type, end_type);

  SGE_LINE_DRAWER_DETAIL_SYMBOL
  line(begin_type, end_type, begin_color_type const &, end_color_type const &);

  [[nodiscard]] SGE_LINE_DRAWER_DETAIL_SYMBOL sge::renderer::vector3 const &begin() const;

  [[nodiscard]] SGE_LINE_DRAWER_DETAIL_SYMBOL sge::renderer::vector3 const &end() const;

  [[nodiscard]] SGE_LINE_DRAWER_DETAIL_SYMBOL sge::line_drawer::color const &begin_color() const;

  [[nodiscard]] SGE_LINE_DRAWER_DETAIL_SYMBOL sge::line_drawer::color const &end_color() const;

private:
  sge::renderer::vector3 begin_;

  sge::renderer::vector3 end_;

  sge::line_drawer::color begin_color_;

  sge::line_drawer::color end_color_;
};

}

#endif
