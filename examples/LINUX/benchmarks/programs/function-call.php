<?php

for($i = 0; $i < 100000; $i++)
  if(sum($i, 1) < $i)
    echo "This is string should never appear";

function sum($a, $b) {
  return $a + $b;
}
