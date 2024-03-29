//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GDIFONT_SYSTEM_HPP_INCLUDED
#define SGE_GDIFONT_SYSTEM_HPP_INCLUDED

#include <sge/font/added_unique_ptr.hpp>
#include <sge/font/object_unique_ptr.hpp>
#include <sge/font/parameters_fwd.hpp>
#include <sge/font/system.hpp>
#include <sge/gdifont/device_context.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace gdifont
{

class system : public sge::font::system
{
  FCPPT_NONCOPYABLE(system);

public:
  system();

  ~system() override;

private:
  sge::font::object_unique_ptr create_font(sge::font::parameters const &) override;

  sge::font::added_unique_ptr add_font(std::filesystem::path const &) override;

  sge::gdifont::device_context const device_context_;
};

}
}

#endif
