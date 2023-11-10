#include "sha_1.h"

int main() {
	/* Addition power */
	uint64_t power = pow(2, 32);

	uint8_t* input = NULL;
	uint8_t* tempStr = NULL;
	uint8_t ch;
	uint64_t size = 1, len = 0;

	while ((ch = getchar()) != EOF && ch != '\n') {
		tempStr = realloc(input, ++size * 8);
		if (tempStr) {
			input = tempStr;
		}
		else {
			return 1;
		}
		input[len++] = ch;
	}
	
	/* 64 bit version of message length */
	uint64_t message_len_64 = len * 8;
	
	/* Append 1 to end of message */
	input[len++] = 128;
	
	while ((size * 8) % 512 != 448) {
        tempStr = realloc(input, 8 * size++);
        if (tempStr) {
			input = tempStr;
		}
		else {
			return 1;
		}
	    input[len++] = 0;
	}
	
	for (int index = 0; index < 8; index++) {
        uint64_t mask = 0xff00000000000000;
	    tempStr = realloc(input, size++ * 8);
	    input = tempStr;
	    mask = mask >> (8 * index);
	    uint64_t val = message_len_64 & mask;
	    val = val >> (8 * (7 - index));
	    input[len++] = (uint8_t) val;
	}
	
	/* Define H values */
	uint32_t H0 = 0x67452301;
	uint32_t H1 = 0xEFCDAB89;
	uint32_t H2 = 0x98BADCFE;
	uint32_t H3 = 0x10325476;
	uint32_t H4 = 0xC3D2E1F0;
	
	for (uint64_t i = 0; i < ((size * 8)/512); i++) {
	
	    /* Define chunk constants */
	    uint32_t A = H0;
	    uint32_t B = H1;
	    uint32_t C = H2;
	    uint32_t D = H3;
	    uint32_t E = H4;
        uint32_t words[80] = {0};
        uint32_t temp;
        
        for (int j = 0; j < 16; j++) {
            uint32_t word = 0;
            for (int k = 0; k < 4; k++) {
                uint32_t byte = input[i * 64 + 4 * j + k];
                word = word | byte;
                if (k < 3) {
                    word = word << 8;                
                }
            }
            words[j] = word;
        }
        
        /* Compression function */
        for (int index = 0; index < 80; index++) {
		    if (index >= 16) {
			    words[index] = circularLeftShift(words[index - 3] ^ words[index - 8] ^ words[index - 14] ^ words[index - 16], 1);
		    }

		    temp = (circularLeftShift(A, 5) + logicalFunction(index, B, C, D) + E + words[index] + K(index)) % power;
		    E = D;
		    D = C;
		    C = circularLeftShift(B, 30);
		    B = A;
		    A = temp;
	    }
	    
	    /* Apply changes for next chunk */
        H0 = H0 + A;
        H1 = H1 + B;
        H2 = H2 + C;
        H3 = H3 + D;
        H4 = H4 + E;
	}

	printf("\n	Hash value: %x %x %x %x %x\n\n", H0, H1, H2, H3, H4);
	return 0;
}
