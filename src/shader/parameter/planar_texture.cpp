#include <sge/shader/pair.hpp>
#include <sge/shader/parameter/planar_texture.hpp>
#include <sge/cg/parameter/named.hpp>
#include <sge/cg/program/object.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/cg/loaded_texture.hpp>
#include <sge/renderer/cg/scoped_texture.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/assert/pre.hpp>


sge::shader::parameter::planar_texture::planar_texture(
	sge::shader::pair &_parent,
	sge::renderer::device &_renderer,
	sge::cg::program::object &_program,
	sge::shader::parameter::name const &_name,
	optional_value const &_value)
:
	parent_(
		_parent),
	renderer_(
		_renderer),
	parameter_(
		_program.parameter(
			_name.get())),
	loaded_texture_(),
	scoped_texture_(),
	optional_render_context_(),
	value_(
		_value)
{
	parent_.add_planar_texture(
		*this);
}

void
sge::shader::parameter::planar_texture::set(
	sge::renderer::texture::planar &_value)
{
	value_ =
		optional_value(
			_value);

	if(optional_render_context_)
	{
		scoped_texture_.reset();

		loaded_texture_.reset();

		loaded_texture_.take(
			renderer_.load_cg_texture(
				parameter_.object(),
				_value));

		scoped_texture_.take(
			fcppt::make_unique_ptr<sge::renderer::cg::scoped_texture>(
				fcppt::ref(
					*optional_render_context_),
				fcppt::cref(
					*loaded_texture_)));
	}
}

void
sge::shader::parameter::planar_texture::activate(
	sge::renderer::context::object &_render_context)
{
	FCPPT_ASSERT_PRE(
		!optional_render_context_);

	FCPPT_ASSERT_PRE(
		!scoped_texture_);

	optional_render_context_ =
		optional_render_context(
			_render_context);

	if(value_)
		this->set(*value_);
}

void
sge::shader::parameter::planar_texture::deactivate()
{
	FCPPT_ASSERT_PRE(
		optional_render_context_);

	scoped_texture_.reset();
	loaded_texture_.reset();
	optional_render_context_ =
		optional_render_context();
}

sge::renderer::cg::loaded_texture &
sge::shader::parameter::planar_texture::loaded_texture()
{
	return
		*loaded_texture_;
}

sge::renderer::texture::stage const
sge::shader::parameter::planar_texture::stage() const
{
	FCPPT_ASSERT_PRE(
		scoped_texture_);
	return
		scoped_texture_->stage();
}

sge::shader::parameter::planar_texture::~planar_texture()
{
	parent_.remove_planar_texture(
		*this);
}
