<?php

// author & (hope so) improved version : monk/rabunix/alexander goia
// Christmas 2025

// version 2

// still not for multitasking (/tmp races still occur)
// personal version

unlink("/tmp/index.html");
unlink("/tmp/linux.txt");
unlink("/tmp/result.txt");

$version = $_POST['version'];
$big =   strtok($version, '.');
$major = strtok('.');
$minor = strtok('.');
$ultra_minor = strtok('.');

if($big == 1 || $big == 2) 
	$output = 'cd /tmp ; wget http://cdn.kernel.org/pub/linux/kernel/v' . $big . '.' . $major . '/' ;
	else
	$output = 'cd /tmp ; wget http://cdn.kernel.org/pub/linux/kernel/v'. $big . '.x/';
shell_exec($output);

$output2 = 'html2text /tmp/index.html > /tmp/linux.txt';
shell_exec($output2);

// ultra minor happens only in 2.6.xx.yy releases
// raison : very stable kernel line

if($ultra_minor == null)
{
if($minor != null)
	$output3 = 'cd /tmp ; grep linux-'.$big.'.'.$major.'.'.$minor.'.tar.gz linux.txt |'.
			' tr -s " " | cut -d " " -f 3 > /tmp/result.txt';
else {  
	if(($big < 3) && ($major == 0)) {
		$output3 = 'cd /tmp ; grep linux-'.$big.'.0.tar.gz linux.txt |'.
			'tr -s " " | cut -d " " -f 3 > /tmp/result.txt';
	} 
	
	else
		
	if($big == 2 || $big == 1) {
		$output3 = 'cd /tmp ; grep linux-'.$big.'.'.$major.'.0.tar.gz linux.txt |'.
			'tr -s " " | cut -d " " -f 3 > /tmp/result.txt';	
	} 
	
	else
		
	$output3 = 'cd /tmp ; grep linux-'.$big.'.'.$major.'.tar.gz linux.txt |'.
	' tr -s " " | cut -d " " -f 3 > /tmp/result.txt';
	}
}

else $output3 = 'cd /tmp ; grep linux-2.6.'.$minor.'.'.$ultra_minor.'.tar.gz linux.txt |'.
		'tr -s " " | cut -d " " -f 3 > /tmp/result.txt';

shell_exec($output3);

$f = fopen("/tmp/result.txt", 'r');
$result = fread($f, 1024);
echo "<h2>Linux version $version was released on $result</h2>";

fclose($f);

unlink("/tmp/index.html");
unlink("/tmp/linux.txt");
unlink("/tmp/result.txt");

?>
