<?php

for($i = 0; $i < 100000; $i++)
  fibonacci(40);

echo fibonacci(40);

function fibonacci($a) {
  $b = 1;
  $c = 0;
  for($r = 0; $r < $a; $r++) {
    $a = $b;
    $b = $c;
    $c = $a + $b;
  }
  return $c;
}
