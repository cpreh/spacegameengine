#include "../vertex_format.hpp"
#include "../conversion.hpp"
#include "../../../core/main/raw_vector.hpp"

namespace
{
	void fill_offset_info(sge::offset_info&, sge::vertex_size offset,
		                  sge::vertex_usage u);
	BYTE get_vertex_type(sge::vertex_usage u);
}

sge::d3d::vertex_format::vertex_format(d3d_device_ptr device, const sge::vertex_format& f)
{
	raw_vector<D3DVERTEXELEMENT9> vertex_elements;

	vertex_size offset = 0;
	const sge::vertex_format::usage_list& l = f.get_elements();
	for(sge::vertex_format::usage_list::const_iterator it = l.begin(); it != l.end(); ++it)
	{
		const vertex_usage usage = it->get_usage();
		D3DVERTEXELEMENT9 elem;
		elem.Stream = 0;
		elem.Method = D3DDECLMETHOD_DEFAULT;
		elem.Offset = static_cast<WORD>(offset);
		elem.Type = get_vertex_type(usage);
		elem.Usage = static_cast<BYTE>(convert_cast<D3DDECLUSAGE>(usage));
		for(elem.UsageIndex = 0; elem.UsageIndex < it->get_count(); ++elem.UsageIndex)
			vertex_elements.push_back(elem);
		fill_offset_info(oi,offset,usage);
		offset += it->get_stride();
	}
	stride = offset;
	
	const D3DVERTEXELEMENT9 end_token = D3DDECL_END();
	vertex_elements.push_back(end_token);

	IDirect3DVertexDeclaration9* decl;
	if(device->CreateVertexDeclaration(&vertex_elements.front(),&decl) != D3D_OK)
		throw std::runtime_error("CreateVertexDeclaration)= failed");
	vertex_declaration = decl;

	//if(D3DXFVFFromDeclarator(&vertex_elements.front(),&fvf) != D3D_OK)
	//	fvf = 0;
}

namespace
{
	BYTE get_vertex_type(const sge::vertex_usage u)
	{
		using namespace sge;
		switch(u) {
		case VU_Pos:
		case VU_Normal:
			return D3DDECLTYPE_FLOAT3;
		case VU_Tex:
			return D3DDECLTYPE_FLOAT2;
		case VU_Diffuse:
			return D3DDECLTYPE_D3DCOLOR;
		default:
			throw std::runtime_error("wrong vertex_usage");
		}
	}
}
