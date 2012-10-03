#include <iostream>
#include "XMLBuilder.h"
#include "XMLNode.h"

using namespace std;

int main(int argc, char* argv[]) {
    XMLMemoryWriter writer;
    XMLBuilder<XMLMemoryWriter> builder(writer);
    XMLNode &root = builder.addNode("CustomerList");
    root.attributes["version"] = "1.0";
    root["Customer"]["Name"].text = "John Smith";
    root["Customer"]["ContactInfo"]["Address"].text = "22 Acacia Avenue";
    root["Customer"]["ContactInfo"]["OfficePhone"].text = "+11 222 333 444";
    builder.write();
    cout << writer.getContent() << endl;
}
