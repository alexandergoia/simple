<?php

unlink("/tmp/index.html");
unlink("/tmp/linux.txt");
unlink("/tmp/result.txt");

$version = $_POST['version'];
$big =   strtok($version, '.');
$major = strtok('.');
$minor = strtok('.');

$output = 'cd /tmp ; wget http://cdn.kernel.org/pub/linux/kernel/v'.$big.'.x/';
shell_exec($output);

$output2 = '/usr/local/bin/html2text -o /tmp/linux.txt -ascii -nobs /tmp/index.html';
shell_exec($output2);

if($minor != null)
	$output3 = 'cd /tmp ; grep linux-'.$big.'.'.$major.'.'.$minor.'.tar.gz linux.txt |'.
' tr -s " " | cut -d " " -f 2 > /tmp/result.txt';
else
	$output3 = 'cd /tmp ; grep linux-'.$big.'.'.$major.'.tar.gz linux.txt |'.
	' tr -s " " | cut -d " " -f 2 > /tmp/result.txt';

shell_exec($output3);

$f = fopen("/tmp/result.txt", 'r');
$result = fread($f, 1024);
echo "<h2>Linux version $version was released on $result</h2>";

fclose($f);

?>
