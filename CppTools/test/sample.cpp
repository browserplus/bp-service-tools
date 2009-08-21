/**
 * A collection of sample code demonstrating the data mapping,
 * version parsing, and description representation facilities of this
 * toolkit
 */

#include "bptypeutil.hh"
#include "bpserviceversion.hh"
#include "bpservicedescription.hh"
#include "bpurlutil.hh"

#include <iostream>
#include <assert.h>

static void
dataMappingSample(void)
{
    std::cout << std::endl << " --- The data mapping sample --- "
              << std::endl;

    bp::List l;
    l.append(new bp::String("foo"));
    l.append(new bp::Integer(77));
    l.append(new bp::Bool(false));    

    unsigned int i;
    for (i=0; i < l.size(); i++) {
        std::cout << i << ": " << bp::typeAsString(l.value(i)->type())
                  << std::endl;
    }

    std::cout << "And this is a struct BPElement_t ptr, ready to transmit "
              << std::endl
              << "across the browserplus/service boundary: " << l.elemPtr()
              << std::endl;

    std::cout << "the c++ types in bptypeutil.h store data in the C "
              << std::endl
              << "defined in the BrowserPlus ServiceAPI...  no more C type "
              << "munging!" << std::endl;
}

#define SAMPLE_VERSION "2.7.19"

static void
versionParsingSample(void)
{
    std::cout << std::endl << " --- The version parsing sample --- "
              << std::endl;
    
    bp::ServiceVersion v;
    assert( v.parse(SAMPLE_VERSION) == true );

    std::cout << "parsed \"" << SAMPLE_VERSION << "\":" << std::endl
              << "major: " << v.majorVer() << std::endl
              << "minor: " << v.minorVer() << std::endl
              << "micro: " << v.microVer() << std::endl;
}

static void
serviceDescSample(void)
{
    std::cout << std::endl << " --- The service description sample --- "
              << std::endl;

    // allocate and provide top level information about this service
    bp::service::Description desc;
    desc.setName("MySampleService");
    desc.setMajorVersion(7);
    desc.setMinorVersion(0);
    desc.setMicroVersion(10);
    desc.setDocString("This service does nothing, it simply demonstrtes "
                      "how one might build up a service description in "
                      "memory");
    
    // now let's define some functions
    std::list<bp::service::Function> functions;
    
    {
        bp::service::Function f1;
        f1.setName("myFirstFunction");
        f1.setDocString("This is the first of the two functions that I expose");
        
        // how about an argument or two?
        std::list<bp::service::Argument> arguments;

        {
            bp::service::Argument a("booleanArg", bp::service::Argument::Boolean);
            a.setRequired(false);
            a.setDocString("an optional boolean argument");
            arguments.push_back(a);
        }

        {
            bp::service::Argument a("stringArg", bp::service::Argument::String);
            a.setRequired(true);
            a.setDocString("a required string argument");
            arguments.push_back(a);
        }

        f1.setArguments(arguments);
        functions.push_back(f1);

        desc.setFunctions(functions);        
        std::cout << "First BPCoreledDef ptr: " << desc.toBPCoreletDefinition()
                  << std::endl;

        f1.setName("mySecondFunction");
        f1.setDocString("This is the second of the two functions that I expose");
        functions.push_back(f1);        
    }
    desc.setFunctions(functions);
    std::cout << "Second BPCoreledDef ptr: " << desc.toBPCoreletDefinition()
              << std::endl;

    
    // all built up, now let's print out a human readable description of
    // our services API
    std::cout << desc.toHumanReadableString();

    // bye.
}

static void
testPathConversion()
{
    static struct {
        const char * path;
        const char * url;
    } testData[] = {
#ifdef WIN32
        { "\\\\a\\b\\c.jpg", "file://a/b/c.jpg" },
        { "\\\\.a\\b.ext",  "file://.a/b.ext" },
        { "\\\\a:100\\c d\\e f.jpg", "file://a:100/c%20d/e%20f.jpg" },
        { "c:\\foo.txt",  "file:///c:/foo.txt" },
        { "\\some\\path", "file:///some/path" },
        { "\\a\\b\\c.jpg", "file:///a/b/c.jpg" },
        { "\\.a\\b.ext",  "file:///.a/b.ext" },
        { "\\a b\\c d\\e f.jpg", "file:///a%20b/c%20d/e%20f.jpg" }

#else
        { "/some/path", "file:///some/path" },
        { "/a/b/c.jpg", "file:///a/b/c.jpg" },
        { "/.a/b.ext",  "file:///.a/b.ext" },
        { "/a b/c d/e f.jpg", "file:///a%20b/c%20d/e%20f.jpg" }
#endif
    };

    std::cout << std::endl << " --- The path/url conversion test ---"
              << std::endl;

    unsigned int i = 0;
    unsigned int guten = 0;
    
    for (i=0; i<sizeof(testData)/sizeof(testData[0]); i++)
    {
        bool urlToPath = bp::urlutil::pathFromURL(testData[i].url).compare(
            testData[i].path) == 0;
        bool pathToUrl = bp::urlutil::urlFromPath(testData[i].path).compare(
            testData[i].url) == 0;
        
        std::cout << (i + 1) << " ("<< testData[i].path << ")\t"
                  << (urlToPath ? "." : "F")
                  << (pathToUrl ? "." : "F")
                  << std::endl;
        if (urlToPath && pathToUrl) guten++;
    }
    std::cout << guten << "/" << i << " tests guten" << std::endl;
}

int
main(void) 
{
    dataMappingSample();
    versionParsingSample();
    serviceDescSample();
    testPathConversion();
    
    return 0;
}

