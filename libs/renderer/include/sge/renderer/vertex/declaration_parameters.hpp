//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VERTEX_DECLARATION_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_DECLARATION_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vertex/declaration_parameters_fwd.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>

namespace sge::renderer::vertex
{

class declaration_parameters
{
public:
  SGE_RENDERER_DETAIL_SYMBOL
  explicit declaration_parameters(sge::renderer::vf::dynamic::format format);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::vf::dynamic::format const &format() const;

private:
  sge::renderer::vf::dynamic::format format_;
};

}

#endif
