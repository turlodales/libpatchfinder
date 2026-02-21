//
//  elfpatchfinder32.cpp
//  libpatchfinder
//
//  Created by tihmstar on 21.02.26.
//

#include "../include/libpatchfinder/elfpatchfinder32.hpp"
#include "elf.h"
#include <libgeneral/Utils.hpp>

using namespace tihmstar::patchfinder;
using namespace tihmstar::libinsn;
using namespace tihmstar::libinsn::arm32;


#pragma mark elfpatchfinder32
elfpatchfinder32::elfpatchfinder32(const char *filename) :
    patchfinder32(true)
{
    auto f = tihmstar::readFile(filename);
    _buf = f.data();
    _bufSize = f.size();
    f.disown();
    init();
}

elfpatchfinder32::elfpatchfinder32(const void *buffer, size_t bufSize, bool takeOwnership) :
patchfinder32(takeOwnership)
{
    _bufSize = bufSize;
    _buf = (uint8_t*)buffer;
    init();
}

elfpatchfinder32::elfpatchfinder32(elfpatchfinder32 &&mv)
: patchfinder32(std::move(mv))
{
    _bufSize = mv._bufSize;
    _buf = mv._buf;
}

#pragma mark private

void elfpatchfinder32::loadSegments(){
    std::vector<vsegment> segments;
    Elf32_Ehdr *hdr = (Elf32_Ehdr*)_buf;
    _entrypoint = hdr->e_entry;
    for (uint32_t i=0; i<hdr->e_phnum; i++) {
        Elf32_Phdr *phdr = &((Elf32_Phdr*)(_buf+hdr->e_phoff))[i];
        if (phdr->p_type == PT_LOAD) {

            vmprot prots = kVMPROTALL;
            std::string segname = "LOAD_";

            if (phdr->p_flags & PF_R) {
                prots = (vmprot)((int)prots | kVMPROTREAD);
                segname += "R";
            }else{
                segname += "-";
            }
            if (phdr->p_flags & PF_W) {
                prots = (vmprot)((int)prots | kVMPROTWRITE);
                segname += "W";
            }else{
                segname += "-";
            }
            if (phdr->p_flags & PF_X) {
                prots = (vmprot)((int)prots | kVMPROTEXEC);
                segname += "X";
            }else{
                segname += "-";
            }
            segments.push_back({_buf+phdr->p_offset, phdr->p_filesz, (loc_t)phdr->p_vaddr, prots, segname});

            if (i==0){
                _base = (loc_t)phdr->p_vaddr; //first segment is base. Is this correct??
            }
        }
    }
    _vmemThumb = new vmem_thumb(segments,0, kVMPROTALL);
    _vmemArm = new vmem_arm(segments,0, kVMPROTALL);

    if (_entrypoint){
        try {
            _vmemThumb->deref(_entrypoint);
        } catch (tihmstar::out_of_range &e) {
            reterror("Entrypoint is outside of mapped segments");
        }
    }
    
    info("Inited elfpatchfinder32 %s %s",VERSION_COMMIT_COUNT, VERSION_COMMIT_SHA);
}

void elfpatchfinder32::init(){
    Elf32_Ehdr *hdr = (Elf32_Ehdr*)_buf;
    retassure(_bufSize > sizeof(*hdr), "buf too small");
    retassure(*(uint32_t*)_buf == 0x464c457f, "Bad elf magic");
    retassure(hdr->e_ident[EI_CLASS] == ELFCLASS32, "This class only works for 32bit elf");
    retassure(hdr->e_ident[EI_DATA] == ELFDATA2LSB, "We only support little endian");
    loadSegments();
}
