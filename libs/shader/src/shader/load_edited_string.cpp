//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cg/program/source.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/shader/exception.hpp>
#include <sge/shader/load_edited_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/stream_to_string.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

sge::cg::program::source sge::shader::load_edited_string(
    sge::renderer::device::core &_renderer,
    sge::renderer::vertex::declaration const &_vd,
    std::istream &_stream)
{
  return _renderer.transform_cg_vertex_program(
      _vd,
      sge::cg::program::source(fcppt::optional::to_exception(
          fcppt::io::stream_to_string(_stream),
          [] { return sge::shader::exception{FCPPT_TEXT("Failed to load edited string")}; })));
}
