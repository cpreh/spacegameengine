//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/vf/client_state.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/log/out.hpp>

namespace
{

template <typename Set>
void insert_checked(
    fcppt::log::object &, // NOLINT(google-runtime-references)
    fcppt::reference<Set>,
    typename Set::value_type);

template <typename Set>
void erase_checked(
    fcppt::log::object &, // NOLINT(google-runtime-references)
    fcppt::reference<Set>,
    typename Set::value_type);

}

sge::opengl::vf::client_state::client_state(fcppt::log::object_reference const _log)
    : log_{_log}, normal_states_(), texture_states_(), attribute_states_()
{
}

void sge::opengl::vf::client_state::enable(GLenum const _value)
{
  ::insert_checked(log_.get(), fcppt::make_ref(normal_states_), _value);
}

void sge::opengl::vf::client_state::disable(GLenum const _value)
{
  ::erase_checked(log_.get(), fcppt::make_ref(normal_states_), _value);
}

void sge::opengl::vf::client_state::enable_texture(sge::renderer::texture::stage const _value)
{
  ::insert_checked(log_.get(), fcppt::make_ref(texture_states_), _value);
}

void sge::opengl::vf::client_state::disable_texture(sge::renderer::texture::stage const _value)
{
  ::erase_checked(log_.get(), fcppt::make_ref(texture_states_), _value);
}

void sge::opengl::vf::client_state::enable_attribute(GLuint const _value)
{
  ::insert_checked(log_.get(), fcppt::make_ref(attribute_states_), _value);
}

void sge::opengl::vf::client_state::disable_attribute(GLuint const _value)
{
  ::erase_checked(log_.get(), fcppt::make_ref(attribute_states_), _value);
}

sge::opengl::vf::client_state::normal_state_set const &
sge::opengl::vf::client_state::normal_states() const
{
  return normal_states_;
}

sge::opengl::vf::client_state::texture_state_set const &
sge::opengl::vf::client_state::texture_states() const
{
  return texture_states_;
}

sge::opengl::vf::client_state::index_state_set const &
sge::opengl::vf::client_state::attribute_states() const
{
  return attribute_states_;
}

namespace
{

fcppt::string common_error()
{
  return fcppt::string{
      FCPPT_TEXT(" This usually happens if you forget to call "
                 "renderer::device::unset_vertex_buffer() before setting a new one.")};
}

template <typename Set>
void insert_checked(
    fcppt::log::object &_log,
    fcppt::reference<Set> const _set,
    typename Set::value_type const _value)
{
  if (!_set.get().insert(_value).second)
  {
    FCPPT_LOG_ERROR(
        _log,
        fcppt::log::out << FCPPT_TEXT("Duplicate state inserted in opengl::vf!") << common_error())
  }
}

template <typename Set>
void erase_checked(
    fcppt::log::object &_log,
    fcppt::reference<Set> const _set,
    typename Set::value_type const _value)
{
  if (!_set.get().erase(_value))
  {
    FCPPT_LOG_ERROR(
        _log,
        fcppt::log::out << FCPPT_TEXT("State erased in opengl::vf that was not there!")
                        << common_error())
  }
}

}
