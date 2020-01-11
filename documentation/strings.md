
## Strings
String are identified by `:`, their name must be composed by lowercase and or uppercase letters and must not contain symbols or numbers. Each string is just an entry of a global array of strings.
```php
:test = "Hello world!"
```
String can be accessed by name:
```php
print :test
# Prints "Hello world!"
```
String can be accessed by reference treating all global strings as entries of an array:
```php
print :[0]
# Prints "Hello world!" or value of test (first string defined in the program)
```
Characters of strings can be accessed as shown below:
```php
:test = "Hello world!"
print :test[0]
# Prints "H"
```
