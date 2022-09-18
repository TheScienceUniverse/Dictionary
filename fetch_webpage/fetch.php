<?php
	error_reporting (E_ALL ^ E_WARNING);	// ignore warnings only

	if (!$argv [1]) {
		echo "Search item not found!\n";
		exit(1);
	}

	// echo $argv [1];

	// $url = "https://www.lexico.com/definition/".argv[1]; // Oxford
	$url = "https://www.dictionary.com/browse/" . $argv [1];

	$url_handle = fopen ($url, "r"); // or die("Can not open URL handle!");

	if (!$url_handle) {
		echo "[Error]\t\t:\t" . $argv [1] . "\n";
		exit(1);
	}

	$file_handle = fopen ("./output/" . $argv[1] . ".txt", "a+");

	if (!$file_handle) {
		echo "Can't Open file for writing!\n";
		exit(1);
	}

	if ($url_handle) {
		while (!feof($url_handle)) {
			$buffer = fgets ($url_handle, 4096);
			fwrite ($file_handle, $buffer);
		}

		fclose ($url_handle);
	}

	fclose ($file_handle);

	echo "[Success]\t:\t" . $argv [1] . "\n";
?>