
// HARD 
// rendement   0.500000 
// Eb_N0       1.400000 

#define codw_N 1024
#define K      512


char fb_table_tileN_origi[]={
4,4,4,2,4,2,4,4,0,4,0,4,4,4,0,4,4,4,3,4,4,4,0,4,0,4,0,4,4,4,2,4,2,4,4,4,2,4,4,4,1,4,4,4,2,4,2,4,4,4,4,3,4,3,1,4,4,4,4,3,4,3,1,1,4,4,4,4,2,4,2,4,2,4,4,4,2,4,2,4,4,4,4,3,4,3,1,4,4,4,4,0,4,4,4,3,4,4,4,3,4,3,1,4,4,4,4,1,1,1,4,4,4,4,4,2,4,4,4,3,4,4,4,1,1,4,4,4,3,1,1,1,4,4,4,4,3,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
};
char* fb_table_tileN = fb_table_tileN_origi ; 

int8_t froozen_bits[]={
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,0,0,0,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,0,1,0,0,0,1,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};
int8_t U[]={
 1,0,1,1,1,0,0,1,0,1,0,1,0,1,1,1,1,1,0,1,0,0,0,1,0,0,0,0,1,0,1,1,1,0,1,1,0,1,0,1,1,1,0,1,0,0,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,0,1,0,1,1,1,1,0,0,1,1,1,0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,1,1,1,0,1,0,1,1,1,0,0,1,1,0,1,1,0,1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,1,1,1,1,0,1,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,1,1,1,1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,1,0,1,0,1,0,0,1,1,0,0,0,1,1,0,1,1,0,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,0,1,0,1,0,0,0,0,1,0,1,1,1,0,1,1,0,0,1,1,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,0,0,1,1,1,0,0,1,1,1,0,1,0,1,1,1,0,1,0,0,1,1,0,0,0,1,1,1,0,1,0,0,0,1,0,1,0,0,0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,0,1,0,0,1,0,0,1,0,0,0,1,1,0,1,0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1,1,0,1,1,0,0,1,1,1,0,1,0,1,0,0,0,1,1,1,0,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,0,0,1,1,1,1,0,1,0,0,1,0,0,0,1,0,0,1,0,1,1,0,0,1,1,1,0,0,0,1,0,1,1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,0,1,1,1,0,0,0,1,0,1,1,1,0,0,0,0,1,1,0,0,1,1,1,0,1,0,0,1,1,1,1,0,0,1,1,1,1,1,0,1,
};
int8_t codw[]={
 0,9,-4,-1,11,0,1,-2,-12,-12,-2,7,7,7,-17,7,-8,-5,-12,-3,-4,-7,5,-10,0,-4,7,14,-4,9,11,-8,5,-2,3,5,3,-7,1,21,0,-7,-6,4,1,-2,5,-12,14,9,-1,10,0,-1,0,8,0,-2,-11,4,-11,-10,-8,-2,-7,10,2,-10,7,-9,-3,2,-14,-12,8,15,2,6,-14,7,-13,-9,-16,7,-6,4,0,0,3,-6,-1,3,-8,5,-8,10,5,0,2,-7,8,6,0,2,-4,11,-2,-7,-3,4,2,2,-5,-6,-10,14,-3,-11,-4,-8,-4,4,7,6,1,14,-10,-9,-1,0,-5,9,1,-3,2,10,1,9,7,-3,-8,-10,5,13,3,7,-8,-3,0,-1,17,-2,0,1,-6,8,-10,-12,-8,2,2,-12,8,6,9,-2,5,3,-6,5,6,7,-2,2,-12,13,-7,-5,-10,5,4,1,5,-9,-1,0,5,6,-18,-12,-18,11,5,-9,4,-4,-12,-11,1,3,-9,6,2,1,14,-5,-13,-3,8,-10,0,11,17,-8,4,-6,-6,-11,13,-8,6,-10,-9,-9,-4,-2,-7,11,-1,1,-5,6,-1,-9,1,6,10,13,-6,7,5,-7,3,0,4,8,-9,4,-6,-17,-8,-11,-9,-11,14,-5,14,6,-14,-2,15,3,-10,-7,-6,5,-6,2,-8,3,-3,-2,7,-1,-10,0,11,9,6,-16,5,2,2,-2,-4,-18,5,-13,12,10,-9,-4,2,7,9,-5,-3,0,14,0,7,3,12,12,6,-6,10,2,11,-13,10,-10,8,0,-6,10,-4,4,4,-3,0,0,-6,5,11,-3,-10,13,0,-5,-3,-7,-8,8,2,1,-6,1,4,8,0,-7,-11,0,-1,-3,-10,0,18,10,-4,10,9,7,11,-10,3,-7,-8,-6,-11,4,-4,1,-5,10,-6,-6,3,11,5,-3,8,-8,-2,-12,-2,0,5,3,-3,-15,7,-12,-5,4,3,3,5,6,-15,-7,0,0,-11,-3,10,0,-7,-6,-3,-1,2,-9,-5,4,-12,-1,5,20,-1,11,-7,-12,0,7,-9,2,19,-3,-2,9,2,10,-4,5,12,0,-9,-3,-4,-6,-6,9,-2,-8,-5,-8,17,10,-3,0,-14,16,-1,-1,10,-1,5,3,2,4,0,2,0,-1,3,4,10,-9,4,-4,-9,-10,2,-1,-4,13,-1,12,2,-6,1,5,7,-2,-5,5,-4,2,-2,-3,9,-5,-2,6,8,3,10,0,9,8,2,7,8,4,-13,0,-2,0,2,4,1,3,8,-2,5,16,-7,2,-11,5,4,7,-5,3,5,3,-13,0,11,-14,-8,0,-5,0,-6,11,12,-8,1,-3,11,2,5,-2,9,-7,0,-10,8,-8,8,-10,-3,10,10,-11,5,-2,8,-13,-5,8,-3,0,-8,-4,1,5,-3,-6,-2,7,-1,13,1,-12,-3,-4,10,9,1,0,4,5,-12,11,-7,-7,17,7,11,8,3,5,-12,-7,5,-7,5,-6,-5,-7,0,0,10,0,-6,-3,8,9,12,-7,-9,-3,-7,5,-6,5,-9,11,-3,8,-5,15,1,9,3,3,-3,0,-11,-2,-6,-7,-2,7,-4,7,-4,2,-11,9,4,-8,1,8,10,6,-15,3,0,-4,3,4,-1,11,12,5,-13,-14,-9,11,-1,-7,12,0,9,-3,10,-15,-24,0,-12,-5,6,-12,0,11,-7,-3,12,4,-4,-3,-9,-6,0,1,0,-14,-10,-7,-10,-9,-7,-4,0,-8,-3,0,7,1,0,3,0,-10,1,-10,9,-18,-2,2,16,-5,3,3,11,18,-5,5,-8,-6,-5,1,-14,-8,4,18,0,-6,0,9,-8,3,5,2,-10,-8,4,4,14,12,-1,-2,12,-6,5,10,-12,-8,-9,5,6,-5,-2,-5,4,-6,6,-16,-4,-14,6,-9,13,1,-12,-8,7,0,5,-4,-2,-8,6,0,-8,-3,-1,1,6,-6,-7,2,11,-7,14,16,2,10,-3,3,0,7,-6,-1,-11,4,10,2,2,-4,0,-7,-13,0,-10,-7,7,1,7,-10,-10,-5,-12,9,-15,-15,11,-7,-9,2,8,-8,5,8,-6,8,2,-5,-2,11,2,-3,-10,2,3,8,-4,0,0,7,-1,15,6,12,6,12,-3,1,0,-10,-3,12,0,2,-12,-9,-1,9,9,3,-7,5,14,-1,6,8,-2,-5,2,-3,-12,4,5,-8,-12,-18,7,-1,8,0,2,-4,12,0,-9,-1,11,-1,0,10,-4,2,1,6,4,-8,-7,-1,0,-1,5,7,-11,-1,-4,12,1,-6,11,-8,-1,-2,1,9,8,2,-7,14,0,-11,1,-8,-10,7,10,-3,14,6,-11,-7,0,-14,0,-4,7,6,2,6,9,7,-6,-4,4,-3,17,-11,-6,11,0,-5,-7,2,12,4,3,-9,10,-2,-8,-9,11,2,4,5,4,6,-2,9,-16,2,-3,4,13,-3,8,-8,-4,-6,-17,0,-5,6,-15,5,-6,-2,-6,-7,-11,13,6,-3,-11,-10,18,10,-1,-8,4,-1,-8,0,6,0,3,13,0,-3,0,1,-6,-9,-9,-5,-10,6,4,-2,0,-10,-9,9,0,4,-6,-10,-5,-12,10,-13,
};