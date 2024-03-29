//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/console/arg_list.hpp>
#include <sge/console/error_callback.hpp>
#include <sge/console/exception.hpp>
#include <sge/console/fallback.hpp>
#include <sge/console/function.hpp>
#include <sge/console/function_map.hpp>
#include <sge/console/message_callback.hpp>
#include <sge/console/object.hpp>
#include <sge/console/object_ref.hpp>
#include <sge/console/prefix.hpp>
#include <sge/console/signal.hpp>
#include <sge/console/callback/function.hpp>
#include <sge/console/callback/name.hpp>
#include <sge/console/callback/parameters.hpp>
#include <sge/console/impl/eval_grammar.hpp>
#include <sge/font/char_type.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/string.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/output_to_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/container/at_optional.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/container/get_or_insert.hpp>
#include <fcppt/container/maybe_front.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/parse/grammar_parse_string.hpp>
#include <fcppt/parse/parse_string_error.hpp>
#include <fcppt/parse/parse_string_error_output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/signal/unregister/function.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::console::object::object(sge::console::prefix const _prefix)
    : error_(),
      message_(),
      prefix_(_prefix),
      funcs_(),
      fallback_(),
      help_connection_(
          this->insert(sge::console::callback::parameters(
                           sge::console::callback::function{
                               [this](sge::console::arg_list const &_args, sge::console::object_ref)
                               { this->help_callback(_args); }},
                           sge::console::callback::name(SGE_FONT_LIT("help")))
                           .short_description(SGE_FONT_LIT("Display help message")))),
      man_connection_(this->insert(
          sge::console::callback::parameters(
              sge::console::callback::function{
                  [this](sge::console::arg_list const &_args, sge::console::object_ref)
                  { this->man_callback(_args); }},
              sge::console::callback::name(SGE_FONT_LIT("man")))
              .short_description(SGE_FONT_LIT("Display information for a specific function"))))
{
}
FCPPT_PP_POP_WARNING

sge::console::object::~object() = default;

fcppt::signal::auto_connection
// NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
sge::console::object::insert(sge::console::callback::parameters &&_params)
{
  return fcppt::container::get_or_insert(
             funcs_,
             _params.name(),
             [&_params](sge::font::string const &)
             {
               return sge::console::function(
                   std::move(_params.short_description()), std::move(_params.long_description()));
             })
      .signal()
      .connect(
          sge::console::callback::function{std::move(_params.function())},
          fcppt::signal::unregister::function{[this, name = std::move(_params.name())]()
                                              { this->remove_function(name); }});
}

fcppt::signal::auto_connection
sge::console::object::register_fallback(sge::console::fallback &&_callback)
{
  return fallback_.connect(std::move(_callback));
}

fcppt::signal::auto_connection
sge::console::object::register_error_callback(sge::console::error_callback &&_callback)
{
  return error_.connect(std::move(_callback));
}

fcppt::signal::auto_connection
sge::console::object::register_message_callback(sge::console::message_callback &&_callback)
{
  return message_.connect(std::move(_callback));
}

void sge::console::object::eval(sge::font::string const &_sp)
{
  fcppt::optional::maybe_void(
      fcppt::container::maybe_front(_sp),
      [this, &_sp](fcppt::reference<sge::font::char_type const> const _prefix)
      {
        if (_prefix.get() != prefix_.get())
        {
          fallback_(_sp);

          return;
        }

        fcppt::either::match(
            fcppt::parse::grammar_parse_string(_sp.substr(1), sge::console::impl::eval_grammar{}),
            [this](fcppt::parse::parse_string_error<sge::font::char_type> const &_error)
            {
              this->emit_error(
                  SGE_FONT_LIT("Failed to parse command \"") +
                  fcppt::output_to_string<sge::font::string>(_error) + SGE_FONT_LIT('"'));
            },
            [this](sge::console::arg_list const &_args) { this->eval(_args); });
      });
}

void sge::console::object::eval(sge::console::arg_list const &_args)
{
  // just typing the prefix is not an error
  fcppt::optional::maybe_void(
      fcppt::container::maybe_front(_args),
      [&_args, this](fcppt::reference<sge::font::string const> const _command)
      {
        fcppt::optional::to_exception(
            fcppt::container::find_opt_mapped(funcs_, _command.get()),
            [_command]
            {
              return sge::console::exception{
                  SGE_FONT_LIT("couldn't find command \"") + _command.get() + SGE_FONT_LIT('"')};
            })
            .get()
            .signal()(_args, fcppt::make_ref(*this));
      });
}

sge::console::function_map const &sge::console::object::functions() const { return funcs_; }

sge::console::prefix sge::console::object::prefix() const { return prefix_; }

void sge::console::object::emit_error(sge::font::string const &_string) { error_(_string); }

void sge::console::object::emit_message(sge::font::string const &_string) { message_(_string); }

void sge::console::object::help_callback(sge::console::arg_list const &)
{
  this->emit_message(
      fcppt::output_to_string<sge::font::string>(funcs_.size()) +
      SGE_FONT_LIT(" available functions:"));

  for (auto const &element : funcs_)
  {
    this->emit_message(
        element.first + SGE_FONT_LIT(": ") + element.second.short_description().get());
  }
}

void sge::console::object::man_callback(sge::console::arg_list const &_args)
{
  fcppt::optional::maybe(
      fcppt::container::at_optional(_args, 1U),
      [this] { this->emit_error(SGE_FONT_LIT("no function given")); },
      [this](fcppt::reference<sge::font::string const> const _command)
      {
        fcppt::optional::maybe(
            fcppt::container::find_opt_mapped(funcs_, _command.get()),
            [_command, this] {
              this->emit_error(
                  SGE_FONT_LIT("function \"") + _command.get() + SGE_FONT_LIT("\" not found"));
            },
            [this](fcppt::reference<sge::console::function> const _function)
            {
              this->emit_message(
                  _function.get().long_description().get().empty()
                      ? SGE_FONT_LIT("No manpage available")
                      : _function.get().long_description().get());
            });
      });
}

void sge::console::object::remove_function(sge::font::string const &_name)
{
  function_map::iterator const it{fcppt::optional::to_exception(
      fcppt::container::find_opt_iterator(funcs_, _name),
      [&_name]
      {
        return sge::console::exception{
            SGE_FONT_LIT("Console function ") + _name + SGE_FONT_LIT(" cannot be removed!")};
      })};

  if (it->second.signal().empty())
  {
    funcs_.erase(it);
  }
}
