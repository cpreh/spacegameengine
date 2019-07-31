//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/create_vertex_declaration.hpp>
#include <sge/d3d9/vertex/d3d_declaration_unique_ptr.hpp>
#include <sge/d3d9/vf/element_vector.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


sge::d3d9::vertex::d3d_declaration_unique_ptr
sge::d3d9::devicefuncs::create_vertex_declaration(
	IDirect3DDevice9 &_device,
	sge::d3d9::vf::element_vector const &_elements
)
{
	IDirect3DVertexDeclaration9 *decl;

	if(
		_device.CreateVertexDeclaration(
			_elements.data(),
			&decl
		)
		!= D3D_OK
	)
		throw
			sge::renderer::exception{
				FCPPT_TEXT("CreateVertexDeclaration() failed!")
			};

	return
		sge::d3d9::vertex::d3d_declaration_unique_ptr(
			decl
		);
}
