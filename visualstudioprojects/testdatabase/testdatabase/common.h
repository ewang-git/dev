struct R2TRecord
{
        int lrgId ;
        int numberOfCalls ;
        int numberOfCoveredBlocks ;
        unsigned char *bitmap ;         // bitmap of hit blocks for a routine
} ;

typedef struct R2TRecord R2TRecord;