# string_view_list
C++17 class for string_view concatenation

string_view_list allows to add instances of string_view without copying data.

## Example
```cpp
std::string_view str1 = "Hello, ";
std::string_view str2 = "world";
std::string_view str3 = "!";

string_view_list list = str1 + str2 + str3; 
std::cout << list; // "Hello, world!"

string_view_list substr = list.substr(3, 5); // "lo wo"
bool starts_with = list.starts_with("Hell"); // true
bool ends_with = list.ends_with("d!"); // true

char sym = list[6]; // w

for (const auto& sym : list) {
	//do smth
}

```
