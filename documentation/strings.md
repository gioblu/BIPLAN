

## Strings
String are identified by `:`, their name must be composed by lowercase and or uppercase letters and must not contain symbols or numbers. Each string is just an entry of a global array of strings.
```php
:boot = "Oh my god I am alive!"
:run  = "Why?!"
:seek = "Input!?"
```
String can be accessed by name:
```php
print :boot
# Prints "Oh my god I am alive"
```
String can be accessed by reference using a numeric variable:
```php
print :>2
# Prints "Input!?" or value of seek (the second string defined in the program)
```
Or passing a numeric variable:
```php
$test = 1
print :>$test
```
Characters of strings can be accessed as shown below:
```php
:test = "Hello world!"
print :test[0]
# Prints "H"
```
