<?php

$prime = 0;
for($i = 0; $i < 10000; $i++)
    $prime = isPrime($i);


function isPrime($num) {
    if ($num <= 1) {
        return false;
    }
    for ($i = 2; $i < $num; $i++) {
        if ($num % $i == 0) {
            return false; 
        }
    }

    return true; 
}