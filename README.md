C/C++ library with syntax validator for parsing ini-style configuration files. 

### INTRODUCTION:

This file format is commonly used by many application, among them Samba 
and MySQL. The parsing can be customized by calling inifile_set_option(). 
Each entry in the file is retrieved as an triple with current section, the 
keyword and an optional value. 

### C++ CODE:

Simple C++ code example for parsing a file:

```c++
#include <iostream>
#include <fstream>
#include <inifile++.hpp>

using namespace inifilepp;

int main(int argc, char **argv)
{
        try {
                parser p("sample.conf");
                const parser::entry *ent;

                while ((ent = p.next())) {
                        std::cout << "sect='" << (ent->sect ? ent->sect : "") << "', "
                                << "key='" << (ent->key ? ent->key : "") << "', "
                                << "val='" << (ent->val ? ent->val : "") << "'\n";
                }
        } catch (parser::exception &e) {
                std::cerr << "parse error at (" << e.line << "," << e.cpos << ")\n";
                return 1;
        }

        return 0;
}
```

### EXAMPLE:

An example of the ini-file format:

```ini
     [section 1]
  
     key1 = val1
     key2 = val2

     [section 2]
    
     key3 = val3
```

The above C++ should generate this result on this ini-fragment:

```javascript
     ent( sect => section 1, key => key1, val => val1)
     ent( sect => section 1, key => key2, val => val2)
     ent( sect => section 2, key => key3, val => val3)
```

Empty and commented lines are ignored. Currently the hash character ('#') 
is recognized as comment begin and everthing after it is ignored.

### PROJECT:

See https://nowise.se/oss/libinifile for more examles.
