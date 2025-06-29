
// Searches for the first occurrence of a substring within a string
// Returns -1 if no occurrence is found or a numeric index if found

function find_substring($haystack, $needle, locals: $r)
	$r = -1
	for #h = 0 to size :[$haystack] 
	  	if :[$haystack][#h] == 0 break end
	  	for #n = 0 to size :[$needle]
			if :[$needle][#n] != :[$haystack][#h + #n] break end
	  		if :[$needle][#n] == 0 $r = #h - size :[$needle] end
	  	next
  	next
return $r

// Searches for the first occurrence of a character within a string
// Returns -1 if no occurrence is found or a numeric index if found

function find_char($str, $chr)
	$r = - 1
	for #i = 0 to size :[$str]
		if :[$str][#i] == $chr $r = #i end
	next
return $r