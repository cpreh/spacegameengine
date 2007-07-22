<?php

require_once('projects/cbproject.template.php');
$projects = array(); $lineno = 0;

$filelist = array(); $dirs = array('src','test');
while(sizeof($dirs)) {
  $cd = array_shift($dirs); $d = opendir($cd);
	while (false !== ($cf = readdir($d))) {
	  if ($cf=='.' || $cf=='..') continue;
		if (is_dir($fn = $cd.'/'.$cf)) $dirs[] = $fn; else $filelist[] = $fn;
	}
}

if (!function_exists('fnmatch')) {
  function fnmatch($mask, $fn, $flags_unused=0) {
	  return preg_match($x='#^'.strtr(preg_quote($mask, '#'), array('\\*' => '.*', '\\?' => '.')). '(?:/.*)?$#i', $fn);
	}
}

function commit_project() {
  global $project;
	array_unique($project['files']);
	sort($project['files']);
	make_cb_project($project);
}

function commit_workspace() {
  global $projects;
	make_cb_workspace($projects);
}

foreach(file('projects.ini') as $line) { ++$lineno;
  if (sizeof($line = explode('=', $line, 2)) == 2) switch(trim($line[0])) {
	  case 'name':
			if (isset($project)) commit_project();
		  $project = array(
			  'name' => trim($line[1]),
				'type' => '',
				'target' => '',
				'libraries' => array(),
				'options' => array(),
				'files' => array(),
				'flags' => array(
					'unstrict' => false
				)
			);
			$projects[]= trim($line[1]);
			break;

		case 'type':
			$project['type'] = trim($line[1]);
			break;

		case 'target':
			$project['target'] = trim($line[1]);
			break;

		case 'option':
			$project['options'][] = trim($line[1]);
			break;

		case 'lib':
			$project['libraries'][] = trim($line[1]);
			break;

		case 'flag':
			$project['flags'][trim($line[1])] = true;
			break;

		case 'include':
		  $mask = trim($line[1]);
			foreach($filelist as $f)
				if (fnmatch($mask, $f))#, FNM_LEADING_DIR | FNM_CASEFOLD))
					$project['files'][] = $f;
			break;

		case 'exclude':
		  $mask = trim($line[1]);
			$tempfilelist = $project['files']; $project['files'] = array();
			foreach($tempfilelist as $f)
				if (!fnmatch($mask, $f))#, FNM_LEADING_DIR | FNM_CASEFOLD))
					$project['files'][] = $f;
			unset($tempfilelist);
			break;

	  default: printf("Warning: Unknown keyword '%s' on line %d.\n", $line[0], $lineno);
	}
}
commit_project();
commit_workspace();
