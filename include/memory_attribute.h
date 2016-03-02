/*****************************************************
  Usage:
   1. function: (a or b)
      a. int ATTR_TEXT_IN_TCM func(int par);
      b. int ATTR_TEXT_IN_TCM func(int par)
        {
        }
   2. RO data:
      a. const int ATTR_RODATA_IN_TCM b = 8;
   3. RW data:
      a. int ATTR_RWDATA_IN_TCM b = 8;
   4. ZI data:
      a. int ATTR_ZIDATA_IN_TCM b;
      
*****************************************************/

#ifndef MEMORY_ATTRIBUTE_H_
#define MEMORY_ATTRIBUTE_H_

#define ATTR_TEXT_IN_TCM               __attribute__ ((__section__(".ramTEXT")))
#define ATTR_RODATA_IN_TCM
#define ATTR_RWDATA_IN_TCM
#define ATTR_ZIDATA_IN_TCM            __attribute__ ((__section__(".tcmBSS")))


#define ATTR_TEXT_IN_RAM
#define ATTR_RWDATA_IN_NONCACHED_RAM
#define ATTR_ZIDATA_IN_NONCACHED_RAM


#define ATTR_RWDATA_IN_NONCACHED_RAM_4BYTE_ALIGN  __attribute__ ((__aligned__(4)))
#define ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN  __attribute__ ((__aligned__(4)))

#endif
