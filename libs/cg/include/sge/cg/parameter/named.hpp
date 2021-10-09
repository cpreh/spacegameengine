//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CG_PARAMETER_NAMED_HPP_INCLUDED
#define SGE_CG_PARAMETER_NAMED_HPP_INCLUDED

#include <sge/cg/detail/symbol.hpp>
#include <sge/cg/parameter/named_fwd.hpp>
#include <sge/cg/parameter/object.hpp>

namespace sge::cg::parameter
{

class named
{
public:
  explicit named(sge::cg::parameter::object const &);

  [[nodiscard]] SGE_CG_DETAIL_SYMBOL sge::cg::parameter::object const &object() const;

private:
  sge::cg::parameter::object impl_;
};

}

#endif
