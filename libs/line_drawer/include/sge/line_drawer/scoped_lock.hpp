//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_LINE_DRAWER_SCOPED_LOCK_HPP_INCLUDED
#define SGE_LINE_DRAWER_SCOPED_LOCK_HPP_INCLUDED

#include <sge/line_drawer/line_sequence.hpp>
#include <sge/line_drawer/object_fwd.hpp>
#include <sge/line_drawer/scoped_lock_fwd.hpp>
#include <sge/line_drawer/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>

namespace sge::line_drawer
{

class scoped_lock
{
  FCPPT_NONMOVABLE(scoped_lock);

public:
  SGE_LINE_DRAWER_DETAIL_SYMBOL
  explicit scoped_lock(fcppt::reference<sge::line_drawer::object>);

  [[nodiscard]] SGE_LINE_DRAWER_DETAIL_SYMBOL sge::line_drawer::line_sequence &value() const;

  SGE_LINE_DRAWER_DETAIL_SYMBOL
  ~scoped_lock();

private:
  fcppt::reference<sge::line_drawer::object> const object_;
};

}

#endif
