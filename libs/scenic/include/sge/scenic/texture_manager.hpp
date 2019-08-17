//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_TEXTURE_MANAGER_HPP_INCLUDED
#define SGE_SCENIC_TEXTURE_MANAGER_HPP_INCLUDED

#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/scenic/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace scenic
{
class texture_manager
{
FCPPT_NONCOPYABLE(
	texture_manager);
public:
	SGE_SCENIC_DETAIL_SYMBOL
	texture_manager(
		sge::renderer::device::core &,
		sge::image2d::system &);

	SGE_SCENIC_DETAIL_SYMBOL
	sge::renderer::texture::planar &
	texture_for_path(
		std::filesystem::path const &);

	SGE_SCENIC_DETAIL_SYMBOL
	~texture_manager();
private:
	typedef
	std::map
	<
		std::filesystem::path,
		sge::renderer::texture::planar_unique_ptr
	>
	path_to_texture_map;

	sge::renderer::device::core &renderer_;
	sge::image2d::system &image_loader_;
	path_to_texture_map path_to_texture_;
};
}
}

#endif
