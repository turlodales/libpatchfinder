//
//  elfpatchfinder32.hpp
//  libpatchfinder
//
//  Created by tihmstar on 21.02.26.
//

#ifndef elfpatchfinder32_hpp
#define elfpatchfinder32_hpp

#include <libpatchfinder/patchfinder32.hpp>

struct symtab_command;
namespace tihmstar {
    namespace patchfinder {
        
        class elfpatchfinder32 : public patchfinder32{
            void loadSegments();
            void init();
            
        public:
            elfpatchfinder32(const char *filename);
            elfpatchfinder32(const void *buffer, size_t bufSize, bool takeOwnership = false);

            elfpatchfinder32(const elfpatchfinder32 &cpy) = delete; //delete copy constructor
            elfpatchfinder32(elfpatchfinder32 &&mv); //move constructor
            
        };
    };
};
#endif /* elfpatchfinder32_hpp */
