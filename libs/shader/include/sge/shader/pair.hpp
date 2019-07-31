//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SHADER_PAIR_HPP_INCLUDED
#define SGE_SHADER_PAIR_HPP_INCLUDED

#include <sge/cg/program/object.hpp>
#include <sge/renderer/cg/loaded_program_unique_ptr.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/shader/context_fwd.hpp>
#include <sge/shader/optional_cflags.hpp>
#include <sge/shader/pixel_program_path.hpp>
#include <sge/shader/pixel_program_stream.hpp>
#include <sge/shader/scoped_pair_fwd.hpp>
#include <sge/shader/vertex_program_path.hpp>
#include <sge/shader/vertex_program_stream.hpp>
#include <sge/shader/detail/symbol.hpp>
#include <sge/shader/parameter/matrix.hpp>
#include <sge/shader/parameter/planar_texture_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_set>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace shader
{
class pair
{
FCPPT_NONCOPYABLE(
	pair);
public:
	SGE_SHADER_DETAIL_SYMBOL
	pair(
		sge::shader::context &,
		sge::renderer::vertex::declaration const &,
		sge::shader::vertex_program_path const &,
		sge::shader::pixel_program_path const &,
		sge::shader::optional_cflags const &);

	SGE_SHADER_DETAIL_SYMBOL
	pair(
		sge::shader::context &,
		sge::renderer::vertex::declaration const &,
		sge::shader::vertex_program_stream const &,
		sge::shader::pixel_program_stream const &,
		sge::shader::optional_cflags const &);

	SGE_SHADER_DETAIL_SYMBOL
	sge::shader::context &
	context() const;

	SGE_SHADER_DETAIL_SYMBOL
	sge::cg::program::object &
	vertex_program();

	SGE_SHADER_DETAIL_SYMBOL
	sge::cg::program::object &
	pixel_program();

	SGE_SHADER_DETAIL_SYMBOL
	sge::renderer::cg::loaded_program &
	loaded_vertex_program();

	SGE_SHADER_DETAIL_SYMBOL
	sge::renderer::cg::loaded_program &
	loaded_pixel_program();

	SGE_SHADER_DETAIL_SYMBOL
	~pair();
private:
	friend class sge::shader::parameter::planar_texture;
	friend class sge::shader::scoped_pair;

	typedef
	std::unordered_set<
		sge::shader::parameter::planar_texture *
	>
	planar_texture_sequence;

	sge::shader::context &context_;
	sge::cg::program::object vertex_program_;
	sge::cg::program::object pixel_program_;
	sge::renderer::cg::loaded_program_unique_ptr const loaded_vertex_program_;
	sge::renderer::cg::loaded_program_unique_ptr const loaded_pixel_program_;
	planar_texture_sequence planar_textures_;

	void
	add_planar_texture(
		sge::shader::parameter::planar_texture &);

	void
	remove_planar_texture(
		sge::shader::parameter::planar_texture &);
};
}
}

#endif
