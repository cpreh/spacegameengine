<?php

function make_cb_project(&$data) {

$type = array(
  'exe' => 1,
	'lib' => 3,
	'plugin' => 3
);

ob_start(); ?>
<<?php echo '?'; ?>xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<CodeBlocks_project_file>
	<FileVersion major="1" minor="6" />
	<Project>
		<Option title="<?php echo htmlspecialchars($data['name']); ?>" />
		<Option pch_mode="2" />
		<Option compiler="gcc" />
		<Build>
			<Target title="Debug">
				<Option output="..\..\..\bin\<?php echo (($data['type']=='plugin')?'plugins\\':'').htmlspecialchars($data['target']); ?>" prefix_auto="1" extension_auto="1" />
				<Option object_output="obj\Debug\" />
				<Option type="<?php echo $type[$data['type']]; ?>" />
				<Option compiler="gcc" />
<?php if ($type[$data['type']] == 3) { ?>
				<Option createDefFile="1" />
				<Option createStaticLib="1" />
<?php } ?>
				<Compiler>
					<Add option="-g" />
				</Compiler>
				<Linker>
<?php foreach($data['libraries'] as $lib) { ?>
					<Add library='<?php echo htmlspecialchars($lib); ?>' />
<?php } ?>
					<Add directory="..\..\..\bin" />
				</Linker>
			</Target>
			<Target title="Release">
				<Option output="..\..\..\bin\<?php echo (($data['type']=='plugin')?'plugins\\':'').htmlspecialchars($data['target']); ?>" prefix_auto="1" extension_auto="1" />
				<Option object_output="obj\Release\" />
				<Option type="<?php echo $type[$data['type']]; ?>" />
				<Option compiler="gcc" />
<?php if ($type[$data['type']] == 3) { ?>
				<Option createDefFile="1" />
				<Option createStaticLib="1" />
<?php } ?>
				<Compiler>
					<Add option="-O2" />
				</Compiler>
				<Linker>
<?php foreach($data['libraries'] as $lib) { ?>
					<Add library='<?php echo htmlspecialchars($lib); ?>' />
<?php } ?>
					<Add directory="..\..\..\bin" />
				</Linker>
			</Target>
		</Build>
		<Compiler>
			<Add option="-W" />
			<Add option="-Wall" />
<?php if (!$data['flags']['unstrict']) { ?>
			<Add option="-pedantic" />
			<Add option="-ansi" />
<?php } ?>
<?php foreach($data['options'] as $option) { ?>
			<Add option='<?php echo htmlspecialchars($option); ?>' />
<?php } ?>
		</Compiler>
<?php foreach($data['files'] as $file) { ?>
		<Unit filename="..\..\..\<?php echo htmlspecialchars($file); ?>" />
<?php } ?>
		<Extensions>
			<code_completion />
		</Extensions>
	</Project>
</CodeBlocks_project_file>
<?php

mkdir('projects/codeblocks/'.$data['name'].'/');
file_put_contents('projects/codeblocks/'.$data['name'].'/'.$data['name'].'.cbp', ob_get_contents());
ob_end_clean();

}

function make_cb_workspace(&$projects) {
$a=0;
ob_start();
?>
<<?php echo '?'; ?>xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<CodeBlocks_workspace_file>
	<Workspace title="sge">
<?php foreach($projects as $p) { ?>
		<Project filename="<?php echo $p; ?>\<?php echo $p; ?>.cbp"<?php if (!$a++) { ?>active="1"<?php } ?> />
<?php } ?>
	</Workspace>
</CodeBlocks_workspace_file><?php

file_put_contents('projects/codeblocks/sge.workspace', ob_get_contents());
ob_end_clean();

}
