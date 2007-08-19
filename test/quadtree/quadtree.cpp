#include <cassert>
#include "mathstuff.hpp"
#include "quadtree.hpp"

sge::quadtree::subtree::subtree() : leaf(false) {}

sge::quadtree::subtree::subtree(const vertex_container_type &vertices,const triangle_container_type &triangles,math::rect _rect,unsigned tree_depth_) 
	: rect(_rect),leaf(tree_depth_ == 0)
{
	for (triangle_container_type::const_iterator i = triangles.begin(); i != triangles.end(); ++i)
	{
		sge::math::vector3 a = vertices[i->vertices[0]],b = vertices[i->vertices[1]],c = vertices[i->vertices[2]];
		triangle t(sge::math::vector2(a.x(),a.z()),sge::math::vector2(b.x(),b.z()),sge::math::vector2(c.x(),c.z()));
		if (triangle_inside_2d(t,rect))
			acquired_triangles.push_back(*i);
	}

	if (tree_depth_ != 0)
		create_children(vertices,tree_depth_);
}

void sge::quadtree::subtree::create_children(const vertex_container_type &vertices,const unsigned tree_depth_)
{
	const space_unit left = rect.left,right = rect.right,top = rect.top,bottom = rect.bottom,
													vertical_center = (top+bottom)/2,horizontal_center = (left+right)/2;
	lefttop.reset(new subtree(vertices,acquired_triangles,math::rect(left,top,horizontal_center,vertical_center),tree_depth_-1));
	righttop.reset(new subtree(vertices,acquired_triangles,math::rect(horizontal_center,top,right,vertical_center),tree_depth_-1));
	leftbottom.reset(new subtree(vertices,acquired_triangles,math::rect(left,vertical_center,horizontal_center,bottom),tree_depth_-1));
	rightbottom.reset(new subtree(vertices,acquired_triangles,math::rect(horizontal_center,vertical_center,right,bottom),tree_depth_-1));
}

sge::math::rect sge::quadtree::subtree::determine_bounds(const vertex_container_type &vertices) const
{
	math::rect bounds;
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

void sge::quadtree::subtree::add_all(index_container_type &indices) const
{
	for (triangle_container_type::const_iterator i = acquired_triangles.begin(); i != acquired_triangles.end(); ++i)
	{
		indices.push_back(i->vertices[0]);
		indices.push_back(i->vertices[1]);
		indices.push_back(i->vertices[2]);
	}
}

void sge::quadtree::subtree::get_visible(const frustum_info &frustum,index_container_type &indices) const
{
	if (leaf)
	{
		add_all(indices);
	}
	else
	{
		if (possibly_inside(lefttop->rect,frustum))
			lefttop->get_visible(frustum,indices);
		if (possibly_inside(righttop->rect,frustum))
			righttop->get_visible(frustum,indices);
		if (possibly_inside(rightbottom->rect,frustum))
			rightbottom->get_visible(frustum,indices);
		if (possibly_inside(leftbottom->rect,frustum))
			leftbottom->get_visible(frustum,indices);
	}
}

void sge::quadtree::subtree::reset(const unsigned tree_depth_,const vertex_container_type &vertices,const triangle_container_type &triangles)
{
	rect = determine_bounds(vertices);
	acquired_triangles = triangles;
	create_children(vertices,tree_depth_);
}

sge::quadtree::quadtree(const unsigned tree_depth_) : tree_depth_(tree_depth_),locked_(false) {}

void sge::quadtree::pack() 
{ 
	assert(locked_); 
	tree_root.reset(tree_depth_,vertices_,triangles_); 
}

void sge::quadtree::tree_depth(const unsigned n)
{
	if (!locked_) 
		throw exception("object is not locked, cannot change tree depth!"); 
	tree_depth_ = n;
}

void sge::quadtree::lock() { locked_ = true; }

void sge::quadtree::unlock() { pack(); locked_ = false; }

sge::quadtree::triangle_container_type &sge::quadtree::triangles() 
{ 
	if (!locked_) 
		throw exception("object is not locked, cannot add triangles!"); 
	return triangles_;
}

sge::quadtree::vertex_container_type &sge::quadtree::vertices() { return vertices_; }

void sge::quadtree::get_visible(const frustum_info &frustum,quadtree::index_container_type &indices) { tree_root.get_visible(frustum,indices); }
