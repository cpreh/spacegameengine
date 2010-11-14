#ifndef SGE_SHADER_OBJECT_HPP_INCLUDED
#define SGE_SHADER_OBJECT_HPP_INCLUDED

#include <sge/shader/value_type.hpp>
#include <sge/shader/variable_sequence.hpp>
#include <sge/shader/sampler_sequence.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/texture_base_ptr.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/glsl/program_ptr.hpp>
#include <sge/renderer/glsl/uniform/variable_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace shader
{
class object
{
FCPPT_NONCOPYABLE(object)
public:
	// NOTE: Currently, we restrict ourselves to shaders from
	// files. There could be stream support, too. It's just laziness
	explicit
	object(
		renderer::device_ptr,
		fcppt::filesystem::path const &vertex,
		fcppt::filesystem::path const &fragment,
		fcppt::string const &format_declaration,
		variable_sequence const &variables,
		sampler_sequence const &samplers);

	void
	set_uniform(
		renderer::glsl::string const &name,
		value_type const &);

	void
	update_texture(
		renderer::glsl::string const &name,
		renderer::texture_base_ptr);

	renderer::glsl::program_ptr const
	program();

	// This is called by the scoped class, but you may call it manually, too
	void
	activate();

	// This is called by the scoped class, but you may call it manually, too
	void
	deactivate();

	// noncopyable classes are supposed to have a destructor
	~object();
private:
	// This is unordered because std::maps perform badly with strings
	typedef
	boost::unordered_map
	<
		renderer::glsl::string,
		renderer::glsl::uniform::variable_ptr
	>
	uniform_map;

	renderer::device_ptr renderer_;
	renderer::glsl::program_ptr program_;
	uniform_map uniforms_;
	sampler_sequence samplers_;
};
}
}

#endif
