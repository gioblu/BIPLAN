<?php

$i = 0;
for($y = 0; $y < 100000; $y++)
  $i = leap_year($y);

function leap_year($y) {
  $r = 0;
  if(($y % 4 == 0) && ($y % 100 != 0) || ($y % 400 == 0)) $r = true;
  else $r = false;
  return $r;
}
