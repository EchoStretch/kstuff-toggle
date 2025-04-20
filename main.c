#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <ps5/kernel.h>

typedef struct notify_request {
  char useless[45];
  char message[3075];
} notify_request_t;

int sceKernelSendNotificationRequest(int, notify_request_t*, size_t, int);

static void
notify(const char* fmt, ...) {
  notify_request_t req;
  va_list args;

  bzero(&req, sizeof req);
  va_start(args, fmt);
  vsnprintf(req.message, sizeof req.message, fmt, args);
  va_end(args);

  sceKernelSendNotificationRequest(0, &req, sizeof req, 0);
}

int
main() {
  intptr_t sysentvec = 0;
  intptr_t sysentvec_ps4 = 0;

  switch(kernel_get_fw_version() & 0xffff0000) {
  case 0x1000000:
  case 0x1010000:
  case 0x1020000:
  case 0x1050000:
  case 0x1100000:
  case 0x1110000:
  case 0x1120000:
  case 0x1130000:
  case 0x1140000:
  case 0x2000000:
  case 0x2200000:
  case 0x2250000:
  case 0x2260000:
  case 0x2300000:
  case 0x2500000:
  case 0x2700000:
    // probably running byepervisor instead of kstuff
    return 0;

  case 0x3000000:
  case 0x3100000:
  case 0x3200000:
  case 0x3210000:
    sysentvec     = KERNEL_ADDRESS_DATA_BASE + 0xca0cd8;
    sysentvec_ps4 = KERNEL_ADDRESS_DATA_BASE + 0xca0e50;
    break;

  case 0x4000000:
  case 0x4020000:
  case 0x4030000:
  case 0x4500000:
  case 0x4510000:
    sysentvec     = KERNEL_ADDRESS_DATA_BASE + 0xd11bb8;
    sysentvec_ps4 = KERNEL_ADDRESS_DATA_BASE + 0xd11d30;
    break;

  case 0x5000000:
  case 0x5020000:
  case 0x5100000:
  case 0x5500000:
    sysentvec     = KERNEL_ADDRESS_DATA_BASE + 0xe00be8;
    sysentvec_ps4 = KERNEL_ADDRESS_DATA_BASE + 0xe00d60;
    break;

  case 0x6000000:
  case 0x6020000:
  case 0x6500000:
    sysentvec     = KERNEL_ADDRESS_DATA_BASE + 0xe210a8;
    sysentvec_ps4 = KERNEL_ADDRESS_DATA_BASE + 0xe21220;
    break;

  case 0x7000000:
  case 0x7010000:
    sysentvec     = KERNEL_ADDRESS_DATA_BASE + 0xe21ab8;
    sysentvec_ps4 = KERNEL_ADDRESS_DATA_BASE + 0xe21c30;
    break;
  case 0x7200000:
  case 0x7400000:
  case 0x7600000:
  case 0x7610000:
    sysentvec     = KERNEL_ADDRESS_DATA_BASE + 0xe21b78;
    sysentvec_ps4 = KERNEL_ADDRESS_DATA_BASE + 0xe21cf0;
    break;
	
  default:
    notify("Unsupported firmware");
    return -1;
  }

  if(kernel_getshort(sysentvec_ps4 + 14) == 0xffff) {
    kernel_setshort(sysentvec + 14, 0xdeb7);
    kernel_setshort(sysentvec_ps4 + 14, 0xdeb7);
    notify("kstuff enabled");
  } else {
    kernel_setshort(sysentvec + 14, 0xffff);
    kernel_setshort(sysentvec_ps4 + 14, 0xffff);
    notify("kstuff disabled");
  }

  return 0;
}

