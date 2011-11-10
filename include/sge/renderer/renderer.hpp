/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_RENDERER_RENDERER_HPP_INCLUDED
#define SGE_RENDERER_RENDERER_HPP_INCLUDED

#include <sge/renderer/active_target.hpp>
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/add_depth_stencil_surface_to_target.hpp>
#include <sge/renderer/ambient_color.hpp>
#include <sge/renderer/aspect.hpp>
#include <sge/renderer/aspect_from_viewport.hpp>
#include <sge/renderer/basic_dim.hpp>
#include <sge/renderer/basic_lock_box.hpp>
#include <sge/renderer/basic_scoped_buffer_lock.hpp>
#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/bit_depth_bytes.hpp>
#include <sge/renderer/buffer_has_depth.hpp>
#include <sge/renderer/buffer_has_stencil.hpp>
#include <sge/renderer/clear_flags.hpp>
#include <sge/renderer/clear_flags_field.hpp>
#include <sge/renderer/clip_plane.hpp>
#include <sge/renderer/clip_plane_index.hpp>
#include <sge/renderer/color_surface.hpp>
#include <sge/renderer/color_surface_fwd.hpp>
#include <sge/renderer/color_surface_ptr.hpp>
#include <sge/renderer/const_basic_scoped_buffer_lock.hpp>
#include <sge/renderer/const_optional_vertex_declaration.hpp>
#include <sge/renderer/const_optional_vertex_declaration_fwd.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/const_scoped_color_surface_lock.hpp>
#include <sge/renderer/const_scoped_index_lock.hpp>
#include <sge/renderer/const_scoped_vertex_lock.hpp>
#include <sge/renderer/create_index_buffer_from_view.hpp>
#include <sge/renderer/create_vertex_buffer_from_view.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/depth_stencil_format.hpp>
#include <sge/renderer/depth_stencil_surface.hpp>
#include <sge/renderer/depth_stencil_surface_fwd.hpp>
#include <sge/renderer/depth_stencil_surface_ptr.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/diffuse_color.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/dim3.hpp>
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/display_mode_fwd.hpp>
#include <sge/renderer/emissive_color.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/first_index.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/index_buffer_ptr.hpp>
#include <sge/renderer/index_buffer_types.hpp>
#include <sge/renderer/index_count.hpp>
#include <sge/renderer/indexed_primitive_type.hpp>
#include <sge/renderer/indices_per_primitive.hpp>
#include <sge/renderer/lock_box.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/lock_rect_to_coords.hpp>
#include <sge/renderer/material.hpp>
#include <sge/renderer/material_fwd.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/multi_sample_type.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/nonindexed_primitive_count.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/renderer/npos.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/onscreen_target_fwd.hpp>
#include <sge/renderer/optional_dim2.hpp>
#include <sge/renderer/optional_target.hpp>
#include <sge/renderer/optional_target_fwd.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/pixel_unit.hpp>
#include <sge/renderer/plugin.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/raw_value.hpp>
#include <sge/renderer/refresh_rate.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/scissor_area.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/renderer/scoped_scissor_area.hpp>
#include <sge/renderer/scoped_target.hpp>
#include <sge/renderer/scoped_transform.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/screen_mode.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/screenshot.hpp>
#include <sge/renderer/shininess.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/specular_color.hpp>
#include <sge/renderer/surface_index.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/system_ptr.hpp>
#include <sge/renderer/target.hpp>
#include <sge/renderer/target_base.hpp>
#include <sge/renderer/target_base_fwd.hpp>
#include <sge/renderer/target_base_ptr.hpp>
#include <sge/renderer/target_from_texture.hpp>
#include <sge/renderer/target_fwd.hpp>
#include <sge/renderer/target_ptr.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/vector4.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/vertex_buffer_types.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/renderer/viewport_size.hpp>
#include <sge/renderer/visual_depth.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/caps/caps.hpp>
#include <sge/renderer/glsl/glsl.hpp>
#include <sge/renderer/index/index.hpp>
#include <sge/renderer/light/light.hpp>
#include <sge/renderer/lock_flags/lock_flags.hpp>
#include <sge/renderer/projection/projection.hpp>
#include <sge/renderer/state/state.hpp>
#include <sge/renderer/texture/texture.hpp>
#include <sge/renderer/vf/vf.hpp>


#endif
