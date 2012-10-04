#include <iostream>
#include "XMLBuilder.h"
#include "XMLNode.h"

using namespace std;

int main(int argc, char* argv[]) {
    LIBXML_TEST_VERSION;

    XMLMemoryWriter writer;
    DTDInfo dtd("dtd_name", "id", "http://x.y.z");
    XMLBuilder<XMLMemoryWriter> builder(writer, dtd);
    XMLNode &root = builder.addNode("CustomerList");
    root.attributes["version"] = "1.0";
    root["Customer"]["Name"].text = "John Smith";
    root["Customer"]["ContactInfo"]["Address"].text = "22 Acacia Avenue";
    root["Customer"]["ContactInfo"]["OfficePhone"].text = "+11 222 333 444";
    builder.write();
    cout << writer.getContent() << endl;

    cout << "********** Creating XML directly through libxml's api " << endl;

    // writing directly to libxml's api
    xmlBufferPtr buffer_ = xmlBufferCreate();
    xmlTextWriterPtr writer_ = xmlNewTextWriterMemory(buffer_, 0);
    if ( xmlTextWriterStartDocument(writer_, "1.0", "UTF-8", NULL) < 0 )
//    if ( xmlTextWriterStartDocument(writer_, NULL, "ISO-8859-1", NULL) < 0 )
        throw XMLError("Error starting the document.");
    if (xmlTextWriterSetIndent(writer_, 2) < 0 )
        throw XMLError("Error set document indentation");
    if (xmlTextWriterStartDTD(writer_, 
                BAD_CAST dtd.name.c_str(),
                BAD_CAST dtd.id.c_str(), 
                BAD_CAST dtd.url.c_str()) < 0)
        throw XMLError("Error setting DTD information");
    if (xmlTextWriterEndDTD(writer_) < 0 )
        throw XMLError("Error setting DTD information");

    /// Adding CustomerList tag
    if (xmlTextWriterStartElement(writer_, BAD_CAST "CustomerList") < 0)
        throw XMLError("Error starting element CustomerList");
    if ( xmlTextWriterWriteAttribute(writer_,
                BAD_CAST "version",
                BAD_CAST "1.0") < 0)
            throw XMLError("Error adding attribute");
    ///Adding CustomerTag
    if (xmlTextWriterStartElement(writer_, BAD_CAST "Customer") < 0)
        throw XMLError("Error starting element Customer");
    ///Adding name tag
    if (xmlTextWriterStartElement(writer_, BAD_CAST "Name") < 0)
        throw XMLError("Error starting element Name");
    if (xmlTextWriterWriteString(writer_, BAD_CAST "John Smith") < 0)
        throw XMLError("Error seting node's value");
    if (xmlTextWriterEndElement(writer_) < 0)
        throw XMLError("Error closing element");
 
    ///Adding ContactInfo tag
    if (xmlTextWriterStartElement(writer_, BAD_CAST "ContactInfo") < 0)
        throw XMLError("Error starting element ContactInfo");
    // Adding Address tag
    if (xmlTextWriterStartElement(writer_, BAD_CAST "Address") < 0)
        throw XMLError("Error starting element Address");
    if (xmlTextWriterWriteString(writer_, BAD_CAST "22 Acacia Avenue") < 0)
        throw XMLError("Error seting node's value");
    if (xmlTextWriterEndElement(writer_) < 0)
        throw XMLError("Error closing element");
    // Adding OfficePhone tag
    if (xmlTextWriterStartElement(writer_, BAD_CAST "ContactPhone") < 0)
        throw XMLError("Error starting element ContactPhone");
    if (xmlTextWriterWriteString(writer_, BAD_CAST "+11 222 333 444") < 0)
        throw XMLError("Error seting node's value");
    if (xmlTextWriterEndElement(writer_) < 0) // OfficePhone
        throw XMLError("Error closing element");
    if (xmlTextWriterEndElement(writer_) < 0) // ContactInfo
        throw XMLError("Error closing element");

     /// End of Customer tag
    if (xmlTextWriterEndElement(writer_) < 0)
        throw XMLError("Error closing element");
    /// End of CustomerList tag
    if (xmlTextWriterEndElement(writer_) < 0)
        throw XMLError("Error closing element ");
    /// Close the document
    if ( xmlTextWriterEndDocument(writer_) < 0 )
        throw XMLError("Error trying to close the document");

    cout << buffer_->content << endl;
}
