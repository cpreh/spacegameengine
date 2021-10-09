//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/dpi.hpp>
#include <sge/font/optional_dpi.hpp>
#include <sge/font/optional_family.hpp>
#include <sge/font/optional_ttf_size.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/ttf_size.hpp>
#include <sge/font/weight/optional_unit.hpp>
#include <sge/font/weight/unit.hpp>
#include <fcppt/string.hpp>

sge::font::parameters::parameters() : dpi_(), ttf_size_(), family_(), weight_(), italic_(false) {}

sge::font::parameters &sge::font::parameters::dpi(sge::font::dpi const &_dpi)
{
  dpi_ = sge::font::optional_dpi(_dpi);

  return *this;
}

sge::font::parameters &sge::font::parameters::ttf_size(sge::font::ttf_size const _ttf_size)
{
  ttf_size_ = sge::font::optional_ttf_size(_ttf_size);

  return *this;
}

sge::font::parameters &sge::font::parameters::family(fcppt::string const &_family)
{
  family_ = sge::font::optional_family(_family);

  return *this;
}

sge::font::parameters &sge::font::parameters::weight(sge::font::weight::unit const _weight)
{
  weight_ = sge::font::weight::optional_unit(_weight);

  return *this;
}

sge::font::parameters &sge::font::parameters::italic()
{
  italic_ = true;

  return *this;
}

sge::font::optional_dpi const &sge::font::parameters::dpi() const { return dpi_; }

sge::font::optional_ttf_size const &sge::font::parameters::ttf_size() const { return ttf_size_; }

sge::font::optional_family const &sge::font::parameters::family() const { return family_; }

sge::font::weight::optional_unit const &sge::font::parameters::weight() const { return weight_; }

bool sge::font::parameters::italic() const { return italic_; }
