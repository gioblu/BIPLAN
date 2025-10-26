
<?php

$a = 0;

for($i = 0; $i < 100000; $i++)
  $a = round(microtime(true) * 1000);

echo $a;
