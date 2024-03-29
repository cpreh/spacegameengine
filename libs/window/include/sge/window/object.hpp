//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_WINDOW_OBJECT_HPP_INCLUDED
#define SGE_WINDOW_OBJECT_HPP_INCLUDED

#include <sge/window/dim_fwd.hpp>
#include <sge/window/event_function.hpp>
#include <sge/window/event_function_type.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <sge/window/system_ref.hpp>
#include <sge/window/detail/symbol.hpp>
#include <awl/window/object_fwd.hpp>
#include <awl/window/reference.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_decl.hpp>

namespace sge::window
{

class object
{
  FCPPT_NONMOVABLE(object);

public:
  SGE_WINDOW_DETAIL_SYMBOL
  object(sge::window::system_ref, awl::window::reference);

  SGE_WINDOW_DETAIL_SYMBOL
  ~object();

  [[nodiscard]] SGE_WINDOW_DETAIL_SYMBOL sge::window::dim size() const;

  SGE_WINDOW_DETAIL_SYMBOL
  void show();

  [[nodiscard]] SGE_WINDOW_DETAIL_SYMBOL awl::window::object &awl_object() const;

  [[nodiscard]] SGE_WINDOW_DETAIL_SYMBOL fcppt::signal::auto_connection
      event_handler(sge::window::event_function);

  [[nodiscard]] SGE_WINDOW_DETAIL_SYMBOL sge::window::system &system() const;

private:
  sge::window::system_ref const system_;

  awl::window::reference const awl_object_;

  using event_signal = fcppt::signal::object<sge::window::event_function_type>;

  event_signal event_signal_;

  fcppt::signal::auto_connection const connection_;
};

}

#endif
