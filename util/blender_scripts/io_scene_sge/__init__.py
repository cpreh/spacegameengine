# NOT! <pep8 compliant>

import bpy
from bpy_extras.io_utils import (ExportHelper)
from bpy.props import (BoolProperty,
					   FloatProperty,
					   IntProperty,
					   StringProperty,
					   EnumProperty,
					   )
import json

bl_info = {
		"name": "sge scene format",
		"author": "Niels Meyering",
		"version": (0, 1),
		"blender": (2, 5, 8),
		"location": "File > Import-Export",
		"description":	"Exports currently selected objects (if supported) to a JSON file "
						"to be used in the sge game engine "
						"(freundlich.github.com/spacegameengine)",
		"warning": "this is an untested script, use at your own risk!",
		"category": "Import-Export"}

class ExportSge(bpy.types.Operator, ExportHelper):
	'''Save an sge compatible json scene file'''

	bl_idname = "export_scene.sge"
	bl_label = "Export sge scene"
	bl_options = {'PRESET'}

	filename_ext = ".json"
	filter_glob = StringProperty(
			default = "*.json",
			options = {'HIDDEN'},
			)

	selected_only = BoolProperty(
		name = "Selected Only",
		description = "export only selected objects, not the whole scene",
		default = False,
		)
	format_output = BoolProperty(
		name = "Formatted Output",
		description = "format JSON output for readability (using Python's JSON module)",
		default = True,
		)
	indentation_level = IntProperty(
		name = "Indentation Level",
		description = "when outputting formatted JSON, use this amount of indentation",
		default = 4,
		)

	def execute(self, context):
		objects = context.selected_objects if self.selected_only else context.scene.objects
		result_objects = []
		for ob in objects:
			entity = {"position": tuple(ob.location)}
			entity["rotation"] = tuple(ob.rotation_euler)
			entity["type"] = ob.type.lower()
			entity["name"] = ob.data.name

			# specific stuff, depending on object type...
			if ob.type == 'MESH':
				entity["scale"] = tuple(ob.scale)
			elif ob.type == 'LAMP':
				entity["energy"] = ob.data.energy
				entity["color"] = tuple(ob.data.color)
			elif ob.type == 'CAMERA':
				entity["fov"] = ob.data.angle
				entity["near"] = ob.data.clip_start
				entity["far"] = ob.data.clip_end

			result_objects.append(entity)

		actual_indentation = self.indentation_level if self.format_output else None
		self.report({'INFO'}, "Dumped scene information: " + json.dumps(result_objects))
		with open(self.filepath, 'w') as output:
			json.dump(
				result_objects,
				output,
				indent=actual_indentation)

		return {'FINISHED'}

def menu_func_export(self, context):
	self.layout.operator(ExportSge.bl_idname, text="sge scene (.json)")

def register():
	bpy.utils.register_module(__name__)

	bpy.types.INFO_MT_file_export.append(menu_func_export)


def unregister():
	bpy.utils.unregister_module(__name__)

	bpy.types.INFO_MT_file_export.remove(menu_func_export)

if __name__ == "__main__":
	register()
