//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GDIFONT_OBJECT_HPP_INCLUDED
#define SGE_GDIFONT_OBJECT_HPP_INCLUDED

#include <sge/font/metrics.hpp>
#include <sge/font/object.hpp>
#include <sge/font/parameters_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/hfont_unique_ptr.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/image/color/optional_format_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace gdifont
{

class object : public sge::font::object
{
  FCPPT_NONCOPYABLE(object);

public:
  object(sge::gdifont::device_context const &, sge::font::parameters const &);

  ~object() override;

private:
  sge::font::text_unique_ptr
  create_text(sge::font::string const &, sge::font::text_parameters const &) override;

  sge::image::color::optional_format preferred_color_format() const override;

  sge::font::metrics metrics() const override;

  sge::gdifont::device_context const &device_context_;

  sge::gdifont::hfont_unique_ptr const font_;

  sge::font::metrics const metrics_;
};

}
}

#endif
