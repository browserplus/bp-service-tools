#include "bptypeutil.h"
#include <iostream>

int
main(void) 
{
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

    return 0;
}
