<?php
$b = "I am a string used for benchmarking.";

for($i = 0; $i < 100000; $i++)
  for($c = 0; $c < strlen($b); $c++)
    $b[$c] = $c;