// C
// std::tan,std::sin,std::cos
#include <cmath>
// std::time
#include <ctime>
// std::srand
#include <cstdlib>
// assert
#include <cassert>
// C++
#include <iostream>
// sge
/*#include ../../src/math/matrix.hpp>
#include ../../src/plugin_manager.hpp>
#include ../../src/plugin.hpp>
#include ../../src/renderer/renderer.hpp>
#include ../../src/renderer/renderer_system.hpp>
#include ../../src/input/input_system.hpp>
#include ../../src/input/key_state_tracker.hpp>
#include ../../src/timer.hpp>
#include ../../src/image/image_loader.hpp>
#include ../../src/image/image.hpp>
#include ../../src/renderer/color.hpp>
#include ../../src/renderer/lock_ptr.hpp>
#include ../../src/math/constants.hpp>
#include ../../src/math/rect.hpp>*/

#include "../../src/math/matrix.hpp"
#include "../../src/plugin_manager.hpp"
#include "../../src/plugin.hpp"
#include "../../src/renderer/renderer.hpp"
#include "../../src/renderer/renderer_system.hpp"
#include "../../src/input/input_system.hpp"
#include "../../src/input/key_state_tracker.hpp"
#include "../../src/timer.hpp"
#include "../../src/image/image_loader.hpp"
#include "../../src/image/image.hpp"
#include "../../src/renderer/color.hpp"
#include "../../src/renderer/lock_ptr.hpp"
#include "../../src/math/constants.hpp"
#include "../../src/math/rect.hpp"
#include "../../src/media.hpp"
#include "mathstuff.hpp"

inline sge::math::space_matrix matrix_perspective(const sge::space_unit aspect, const sge::space_unit fov, const sge::space_unit near, const sge::space_unit far)
{
	const sge::space_unit h = static_cast<sge::space_unit>(1) / std::tan(fov / static_cast<sge::space_unit>(2)),
	                 w = h / aspect,
	                 q = -(far+near)/(far-near);
	return sge::math::space_matrix
	       (w, 0,                     0, 0,
	        0, h,                     0, 0,
	        0, 0,                     q, -1,
	        0, 0, -2*far*near/(far-near), 0);
}

class quadtree
{
	public:
	typedef long index_type;
	typedef std::vector<index_type> index_container_type;
	struct indexed_triangle { index_type vertices[3]; };

	protected:
	typedef std::vector<indexed_triangle>   triangle_container_type;
	typedef std::vector<sge::math::vector3> vertex_container_type;

	triangle_container_type triangles;
	vertex_container_type   vertices;
	int                     tree_depth;

	class subtree
	{
		boost::scoped_ptr<subtree> lefttop,righttop,leftbottom,rightbottom;
		triangle_container_type    acquired_triangles;
		sge::math::rect            rect;
		bool                       leaf;

		public:
		subtree() : leaf(false) {}
		subtree(const vertex_container_type &vertices,const triangle_container_type &triangles,sge::math::rect _rect,int tree_depth) : rect(_rect),leaf(tree_depth == 0)
		{
			// Sind wir bei einem Blatt angelangt? Dann entsprechende Dreiecke hinzufuegen
			if (tree_depth == 0)
			{
				for (triangle_container_type::const_iterator i = triangles.begin(); i != triangles.end(); ++i)
				{
					sge::math::vector3 a = vertices[i->vertices[0]],b = vertices[i->vertices[1]],c = vertices[i->vertices[2]];
					triangle t(sge::math::vector2(a.x(),a.z()),sge::math::vector2(b.x(),b.z()),sge::math::vector2(c.x(),c.z()));
					if (triangle_inside_2d(t,rect))
						acquired_triangles.push_back(*i);
				}
			}
			else
			{
				create_children(vertices,triangles,tree_depth);
			}
		}

		void create_children(const vertex_container_type &vertices,const triangle_container_type &triangles,int tree_depth)
		{
			sge::space_unit left = rect.left,right = rect.right,top = rect.top,bottom = rect.bottom,
														 vertical_center = (top+bottom)/2,horizontal_center = (left+right)/2;
			lefttop.reset(new subtree(vertices,triangles,sge::math::rect(left,top,horizontal_center,vertical_center),tree_depth-1));
			righttop.reset(new subtree(vertices,triangles,sge::math::rect(horizontal_center,top,right,vertical_center),tree_depth-1));
			leftbottom.reset(new subtree(vertices,triangles,sge::math::rect(left,vertical_center,horizontal_center,bottom),tree_depth-1));
			rightbottom.reset(new subtree(vertices,triangles,sge::math::rect(horizontal_center,vertical_center,right,bottom),tree_depth-1));
		}
		
		sge::math::rect determine_bounds(const vertex_container_type &vertices) const
		{
			sge::math::rect bounds;
			for (vertex_container_type::const_iterator i = vertices.begin(); i != vertices.end(); ++i)
			{
				if (i->x() > bounds.right)
					bounds.right = i->x();
				if (i->x() < bounds.left)
					bounds.left = i->x();
				if (i->z() < bounds.top)
					bounds.top = i->z();
				if (i->z() > bounds.bottom)
					bounds.bottom = i->z();
			}
			return bounds;
		}

		void add_all(index_container_type &indices) const
		{
			if (!leaf)
			{
				lefttop->add_all(indices);
				righttop->add_all(indices);
				leftbottom->add_all(indices);
				rightbottom->add_all(indices);
			}
			else
			{
				for (triangle_container_type::const_iterator i = acquired_triangles.begin(); i != acquired_triangles.end(); ++i)
				{
					indices.push_back(i->vertices[0]);
					indices.push_back(i->vertices[1]);
					indices.push_back(i->vertices[2]);
				}
			}
		}

		void get_visible(const frustum_info &frustum,index_container_type &indices) const
		{
			if (leaf)
			{
				add_all(indices);
				return;
			}

	//		std::cout << "Checke ob " << lefttop->rect << " innerhalb von " << frustum << " ist.\n";

			// Alle 4 Unterknoten auf Sichtbarkeit ueberpruefen
			if (completely_inside(lefttop->rect,frustum))
				lefttop->add_all(indices);
			//else if (partially_inside(lefttop->rect,frustum))
			//	lefttop->get_visible(frustum,indices);

			if (completely_inside(righttop->rect,frustum))
				righttop->add_all(indices);
			//else if (partially_inside(righttop->rect,frustum))
			//	righttop->get_visible(frustum,indices);

			if (completely_inside(rightbottom->rect,frustum))
				rightbottom->add_all(indices);
			//else if (partially_inside(rightbottom->rect,frustum))
			//	rightbottom->get_visible(frustum,indices);

			if (completely_inside(leftbottom->rect,frustum))
				leftbottom->add_all(indices);
			//else if (partially_inside(leftbottom->rect,frustum))
			//	leftbottom->get_visible(frustum,indices);
		}

		void reset(int tree_depth,const vertex_container_type &vertices,const triangle_container_type &triangles)
		{
			rect = determine_bounds(vertices);
			create_children(vertices,triangles,tree_depth);
		}
	};
	subtree tree_root;
	
	public:
	quadtree(int tree_depth) : tree_depth(tree_depth) {}
	
	template<typename T>
	void add_triangles(const T &t) { std::copy(t.begin(),t.end(),std::back_inserter(triangles)); }

	// set_vertices, nicht add_vertices, weil es bei Vertizes auf die korrekten Indizes ankommt und man nicht "wild" neue hinzufuegen soll
	// TODO: Das hier nochmal ueberdenken
	template<typename T>
	void set_vertices(const T &t) 
	{ 
		vertices.clear(); 
		std::copy(t.begin(),t.end(),std::back_inserter(vertices));
	}

	void pack()
	{
		tree_root.reset(tree_depth,vertices,triangles);
	}

	void get_visible(const sge::math::vector2 pos,const sge::space_unit rotation,const sge::space_unit fov,index_container_type &indices)
	{
		tree_root.get_visible(frustum_info(pos,fov,rotation),indices);
	}

	virtual ~quadtree() {}
};

int main()
{
	std::srand(std::time(0));

	sge::plugin_manager pm;
	const sge::plugin<sge::renderer_system>::ptr_type renderer_plugin = pm.get_plugin<sge::renderer_system>().load();
	const sge::plugin<sge::input_system>::ptr_type input_plugin = pm.get_plugin<sge::input_system>().load();

	const sge::renderer_system_ptr rs(renderer_plugin->get()());

	const sge::renderer_parameters param(sge::display_mode(1024,768,sge::bit_depth::depth32,100), true);
	const sge::renderer_ptr rend = rs->create_renderer(param);

	const sge::input_system_ptr is(input_plugin->get()(rend->get_window()));

	sge::key_state_tracker ks(is);
	sge::timer frame_timer(1000);

	// Heigghtmap einlesen
	const sge::plugin<sge::image_loader>::ptr_type image_loader_plugin = pm.get_plugin<sge::image_loader>().load();
	const sge::image_loader_ptr pl(image_loader_plugin->get()());
	const sge::image_ptr heightmap = pl->load_image(sge::media_path() + "newheightmap.bmp");

	const sge::math::dim2 field_dim(1,1);

	const sge::vertex_buffer_ptr model_vb = rend->create_vertex_buffer(sge::vertex_format().add(sge::vertex_usage::pos).add(sge::vertex_usage::tex), heightmap->height() * heightmap->width());

	quadtree tree(2);

	// Model daraus generieren
	float texture_granularity = 4;
	{
		//sge::image::const_pointer pp = heightmap->data();
		sge::lock_ptr<sge::vertex_buffer_ptr> _lock(model_vb);
		sge::vertex_buffer::iterator vbit = model_vb->begin();
		// Fuer den Tree
		std::vector<sge::math::vector3> vertices;
		for (sge::image::size_type y = 0; y < heightmap->height(); ++y)
		{
			for (sge::image::size_type x = 0; x < heightmap->width(); ++x)
			{
				//sge::math::vector3 pos = sge::math::vector3(x * field_dim.w(),30*sge::green_part_rgba_f(*pp++),-y * field_dim.h());
				sge::math::vector3 pos = sge::math::vector3(x * field_dim.w(),0,-y * field_dim.h());
				vertices.push_back(pos);
				vbit->pos() = pos;
				vbit->tex() = sge::math::vector2(sge::space_unit(x)/heightmap->width()*texture_granularity,sge::space_unit(y)/heightmap->height()*texture_granularity);
				vbit++;
			}
		}
		tree.set_vertices(vertices);
	}

	// Fuer den Tree
	std::vector<quadtree::indexed_triangle> triangles;
	for (sge::image::size_type y = 0; y < (heightmap->height()-1); ++y)
	{
		for (sge::image::size_type x = 0; x < (heightmap->width()-1); ++x)
		{
			quadtree::indexed_triangle right;
			right.vertices[0] = y * heightmap->width() + x;
			right.vertices[1] = y * heightmap->width() + x + 1;
			right.vertices[2] = (y + 1) * heightmap->width() + x + 1;
			quadtree::indexed_triangle left;
			left.vertices[0] = y * heightmap->width() + x;
			left.vertices[1] = (y + 1) * heightmap->width() + x + 1;
			left.vertices[2] = (y + 1) * heightmap->width() + x;
			triangles.push_back(right);
			triangles.push_back(left);
		}
	}
	tree.add_triangles(triangles);
	tree.pack();

	const sge::image_ptr grass_image = pl->load_image(sge::media_path() + "grass.png");

	const sge::texture_ptr textures[] = {
		rend->create_texture(grass_image->data(), grass_image->width(), grass_image->height(), sge::point_filter),
		rend->create_texture(grass_image->data(), grass_image->width(), grass_image->height(), sge::linear_filter),
		rend->create_texture(grass_image->data(), grass_image->width(), grass_image->height(), sge::mip_filter),
		rend->create_texture(grass_image->data(), grass_image->width(), grass_image->height(), sge::trilinear_filter)
	};

//	const sge::texture_ptr grass_texture = rend->create_texture(grass_image->data(), grass_image->width(), grass_image->height(), sge::linear_filter);

	bool running = true;

	unsigned selected_texture = 0;

	rend->set_texture(textures[selected_texture]);
	rend->set_bool_state(sge::bool_state::enable_zbuffer,true);
	rend->set_bool_state(sge::bool_state::clear_zbuffer,true);
	rend->set_bool_state(sge::bool_state::enable_culling,true);
	rend->set_bool_state(sge::bool_state::clear_backbuffer,true);
	rend->set_cull_mode(sge::cull_mode::back);
	rend->set_float_state(sge::float_state::zbuffer_clear_val,0);
	rend->set_depth_func(sge::depth_func::greater);

	sge::math::vector3 translation(-32,-3,-100);
	sge::space_unit fovy_deg = 90,near = 1,far = 100,rot = 0;

	sge::timer press_timer(500);
	while (running)
	{
		rend->begin_rendering();
		sge::window::dispatch();
		is->dispatch();

		translation.x() += ks[sge::KC_LEFT] * 0.01;
		translation.x() -= ks[sge::KC_RIGHT] * 0.01;
		translation.y() -= ks[sge::KC_UP] * 0.01;
		translation.y() += ks[sge::KC_DOWN] * 0.01;
		translation.z() += ks['w'] * 0.01;
		translation.z() -= ks['s'] * 0.01;

		if(ks['x'] && press_timer.update())
		{
			selected_texture = (selected_texture+1) % (sizeof(textures)/sizeof(sge::texture_ptr));
			rend->set_texture(textures[selected_texture]);
		}

		sge::space_unit aspect = static_cast<sge::space_unit>(rend->screen_width()) / rend->screen_height();
		sge::space_unit fovy_rad = fovy_deg*sge::math::PI/180,hnear = 2*std::tan(fovy_rad/2)*near,wnear = hnear * aspect,fovx_rad = 2*std::atan((wnear/2)/near);

		rend->transform(sge::math::matrix_translation(translation));
		// Projektionsmatrix setzen
	//	rend->projection(sge::math::matrix_perspective(static_cast../../src::space_unit>(rend->screen_width()) / rend->screen_height(),fovy_rad,near,far));
		rend->projection(matrix_perspective(static_cast<sge::space_unit>(rend->screen_width()) / rend->screen_height(),fovy_rad,near,far));

	//	sge::math::space_matrix perspect = 
	//				sge::math::transpose(sge::math::matrix_perspective(static_cast../../src::space_unit>(rend->screen_width()) / rend->screen_height(),fovy_rad,near,far));

	//	sge::math::vector3 nl(perspect[0][3]+perspect[0][0],perspect[1][3]+perspect[1][0],perspect[2][3]+perspect[2][0]);
	//	std::cout << "left normal: " << nl.normalize() << "\n";

		quadtree::index_container_type indices;
		tree.get_visible(sge::math::vector2(-translation.x(),-translation.z()),rot,fovx_rad,indices);
		if (indices.size() > 0)
		{
			const sge::index_buffer_ptr model_ib = rend->create_index_buffer(indices.size());
			{
				sge::lock_ptr<sge::index_buffer_ptr> _lock(model_ib);
				std::copy(indices.begin(),indices.end(),model_ib->begin());
			}
			rend->render(model_vb,model_ib,0,model_vb->size(),sge::indexed_primitive_type::triangle,indices.size()/3,0);
		}

		// Hier Programmlogik
		if (ks[sge::KC_ESC])
			running = false;

		rend->end_rendering();
	}
}
