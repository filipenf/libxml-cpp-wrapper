libxml-cpp-wrapper
==================

A simple C++ wrapper to the libxml

I created this small library to simplify the libxml's API for C++ developers.

As simple as:

XMLReader reader(xml_string);
reader.parse();
string office_phone = reader.getNodes()[0]["Customer"]["ContactInfo"]["OfficePhone"].text;

for a xml like this:

<CustomerList>
    <Customer>
        <Name>John Smith</Name>
        <ContactInfo>
            <Address>22 Acacia Avenue</Address>
            <OfficePhone>123456</OfficePhone>
        </ContactInfo>
    </Customer>
</CustomerList>


Pre-requisites:
===================
    * libxml2
    * cmake


Installation
===================
Easy way:
    Just copy the .cpp and .h files to your project and build it.

Not so easy way:

1) Clone git repository
    # git clone git://github.com/filipenf/libxml-cpp-wrapper.git
2) Build the project
    # mkdir build && cd build
    # cmake ../libxml-cpp-wrapper
    # make && sudo make install

While making it's possible that you get some error about including libxml2
headers. The included path in the cmake is /usr/local/include/libxml2/, you
can adjust it for your system.

After the instalation a library named xmlcppwrapper will be installed in your
system. You should link your project to it.

