//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CONSOLE_OBJECT_HPP_INCLUDED
#define SGE_CONSOLE_OBJECT_HPP_INCLUDED

#include <sge/console/arg_list.hpp>
#include <sge/console/error_callback.hpp>
#include <sge/console/error_function.hpp>
#include <sge/console/fallback.hpp>
#include <sge/console/fallback_signal.hpp>
#include <sge/console/function_map.hpp>
#include <sge/console/message_callback.hpp>
#include <sge/console/message_function.hpp>
#include <sge/console/prefix_fwd.hpp>
#include <sge/console/callback/parameters_fwd.hpp>
#include <sge/console/detail/symbol.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <sge/font/string.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>

namespace sge::console
{

class SGE_CORE_DETAIL_CLASS_SYMBOL object
{
  FCPPT_NONMOVABLE(object);

public:
  SGE_CONSOLE_DETAIL_SYMBOL
  explicit object(sge::console::prefix);

  SGE_CONSOLE_DETAIL_SYMBOL
  ~object();

  [[nodiscard]] SGE_CONSOLE_DETAIL_SYMBOL fcppt::signal::auto_connection
  insert(sge::console::callback::parameters &&);

  [[nodiscard]] SGE_CONSOLE_DETAIL_SYMBOL fcppt::signal::auto_connection
  register_fallback(sge::console::fallback &&);

  [[nodiscard]] SGE_CONSOLE_DETAIL_SYMBOL fcppt::signal::auto_connection
  register_error_callback(sge::console::error_callback &&);

  [[nodiscard]] SGE_CONSOLE_DETAIL_SYMBOL fcppt::signal::auto_connection
  register_message_callback(sge::console::message_callback &&);

  SGE_CONSOLE_DETAIL_SYMBOL
  void eval(sge::font::string const &);

  SGE_CONSOLE_DETAIL_SYMBOL
  void eval(sge::console::arg_list const &);

  [[nodiscard]] SGE_CONSOLE_DETAIL_SYMBOL sge::console::function_map const &functions() const;

  [[nodiscard]] SGE_CONSOLE_DETAIL_SYMBOL sge::console::prefix prefix() const;

  SGE_CONSOLE_DETAIL_SYMBOL
  void emit_error(sge::font::string const &);

  SGE_CONSOLE_DETAIL_SYMBOL
  void emit_message(sge::font::string const &);

private:
  fcppt::signal::object<sge::console::error_function> error_;

  fcppt::signal::object<sge::console::message_function> message_;

  sge::console::prefix const prefix_;

  sge::console::function_map funcs_;

  sge::console::fallback_signal fallback_;

  fcppt::signal::auto_connection const help_connection_;

  fcppt::signal::auto_connection const man_connection_;

  void help_callback(sge::console::arg_list const &);

  void man_callback(sge::console::arg_list const &);

  void remove_function(sge::font::string const &);
};

}

#endif
