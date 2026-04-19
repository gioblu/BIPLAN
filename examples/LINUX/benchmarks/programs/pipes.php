<?php

$s = "This is a test string.\n";
$pipe = popen('sh -c "cat > /tmp/biplan-benchmark-pipes.txt"', 'w');
for($i = 0; $i < 1000; $i++)
  fwrite($pipe, $s);
pclose($pipe);
