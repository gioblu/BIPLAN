<?php

$a = '1';

for($i = 0; $i < 100000; $i++)
  if(is_numeric($a)) $i = $i + 1;

