<?php

for($i = 0; $i < 100000; $i++)
  if(op($i, 1) < $i)
    echo "This is string should never appear";

function op($a, $b) {
  return sum($a, $b);
}

function sum($a, $b) {
  return $a + $b;
}
