<?php

for($i = 0; $i < 100000; $i++)
   factorial(20);

function factorial($n) {
   $r = 1;
   for($i = 2; $i < $n + 1; $i++) 
      $r = $r * $i;
   return $r; 
}
   