//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_DYNAMIC_POS_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_POS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vf/dynamic/pos_fwd.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>

namespace sge::renderer::vf::dynamic
{

class pos
{
public:
  SGE_RENDERER_DETAIL_SYMBOL
  explicit pos(sge::renderer::vf::dynamic::vector const &);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::vf::dynamic::vector const &type() const;

private:
  sge::renderer::vf::dynamic::vector type_;
};

SGE_RENDERER_DETAIL_SYMBOL
bool operator==(sge::renderer::vf::dynamic::pos const &, sge::renderer::vf::dynamic::pos const &);

}

#endif
