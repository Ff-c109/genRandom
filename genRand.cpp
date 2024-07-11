#include <stdlib.h>

int main() {
	return system("openssl rand 512 | clevis encrypt tpm2 '{}' | tail -c 512 | head -c 256 | base64");
}
