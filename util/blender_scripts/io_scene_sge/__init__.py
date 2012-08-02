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

	def _process_mesh(self, ob, entity):
		entity["scale"] = tuple(ob.scale)
		return entity

	def _process_camera(self, ob, entity):
		render = context.scene.render
		aspect = render.resolution_x / render.resolution_y
		entity["fov"] = ob.data.angle / aspect
		entity["near"] = ob.data.clip_start
		entity["far"] = ob.data.clip_end
		return entity

	def _process_lamp(self, ob, entity):
		if ob.data.type == 'HEMI' or ob.data.type == 'SUN':
			light_type = 'directional'
		elif ob.data.type == 'POINT':
			light_type = 'point'
		elif ob.data.type == 'SPOT':
			light_type = 'spot'
			entity["spot_cutoff"] = ob.data.spot_size
			# FIXME: does this make sense for OpenGL?
			entity["spot_exponent"] = ob.data.spot_blend * 128.0
		else:
			self.report({'WARNING'}, "Unsupported lamp type: {}".format(ob.data.type))
			return None
		entity["light_type"] = light_type
		entity["energy"] = ob.data.energy
		entity["color"] = tuple(ob.data.color)
		return entity

	def _process(self, ob, result):
		entity = dict()
		entity["position"] = tuple(ob.location)
		entity["rotation"] = tuple(ob.rotation_euler)
		entity["name"] = ob.data.name

		if ob.type == 'MESH':
			entity = self._process_mesh(ob, entity)
			if entity:
				result["meshes"].append(entity)
		elif ob.type == 'LAMP':
			entity = self._process_lamp(ob, entity)
			if entity:
				result["lights"].append(entity)
		elif ob.type == 'CAMERA':
			if result["camera"] != None:
				raise Exception("Cannot export more than one camera object!")
			result["camera"] = self._process_camera(ob, entity)

	def execute(self, context):
		self.context = context
		objects = context.selected_objects if self.selected_only else context.scene.objects

		result = dict()
		result["meshes"] = []
		result["lights"] = []
		result["camera"] = None
		result["world"] = dict()

		world = context.scene.world

		# fog
		fog_start = world.mist_settings.start
		# FIXME: how to map blender mist modes to GL fog modes?
		result["world"]["fog-mode"] = "linear"
		result["world"]["fog-start"] = fog_start
		result["world"]["fog-end"] = fog_start + world.mist_settings.depth
		result["world"]["fog-color"] = tuple(world.horizon_color)
		# FIXME: what to do about fog density?

		for ob in objects:
			try:
				self._process(ob, result)
			except Exception as e:
				self.report({'ERROR_INVALID_INPUT'}, str(e))
				return {'CANCELLED'}

		actual_indentation = self.indentation_level if self.format_output else None

		self.report({'INFO'}, "Dumped scene information: " + json.dumps(result))
		with open(self.filepath, 'w') as output:
			json.dump(
				result,
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
