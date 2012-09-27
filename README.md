libxml-cpp-wrapper
==================

A simple C++ wrapper to the libxml

I created this small library to simplify the libxml's API for C++ developers.

Example
====================
For a xml like this:
```xml
<CustomerList>
    <Customer>
        <Name>John Smith</Name>
        <ContactInfo>
            <Address>22 Acacia Avenue</Address>
            <OfficePhone>123456</OfficePhone>
        </ContactInfo>
    </Customer>
</CustomerList>
```
The code to parse and get the value of OfficePhone tag is:
```c++
list<XMLNode> nodes;
XMLReader reader(xml_string);
reader.parse(nodes);
XMLNode &node = *nodes.begin();
string office_phone = node["Customer"]["ContactInfo"]["OfficePhone"].text;
```


Pre-requisites:
===================
    * libxml2
    * cmake


Installation
===================
1) Clone git repository
```
    git clone git://github.com/filipenf/libxml-cpp-wrapper.git
```

** Easiest way: **
    2) Just copy the .cpp and .h files to your project and build it.

** 2nd easiest way :-): **

2) Build the project
```
    mkdir build && cd build
    cmake ../libxml-cpp-wrapper
    make && sudo make install
```
If may find some errors about the inclusion of libxml headers. Make sure your
libxml2 include directory is /usr/local/include/libxml2 or you can adjust it
in the CMakeFiles.txt

After the instalation a library named xmlcppwrapper will be installed in your
system. You should link your project to it.

