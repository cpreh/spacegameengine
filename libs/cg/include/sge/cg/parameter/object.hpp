//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CG_PARAMETER_OBJECT_HPP_INCLUDED
#define SGE_CG_PARAMETER_OBJECT_HPP_INCLUDED

#include <sge/cg/detail/symbol.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>

namespace sge::cg::parameter
{

class object
{
public:
  explicit object(CGparameter);

  [[nodiscard]] SGE_CG_DETAIL_SYMBOL CGparameter get() const;

private:
  CGparameter parameter_;
};

}

#endif
