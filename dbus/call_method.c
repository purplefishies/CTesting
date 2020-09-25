/*
 * log_dbus.c - SeeScan GLR10 Locator Logging Client
 *
 * (c) Copyright 2016-2018 SeeScan, Inc.
 *
 * Confidential computer software. Valid license from SeeScan required for
 * possession, use or copying.
 */

/*
 * Routines for making Logging DBUS connections
 *
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <libgen.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/route.h>
#include <sys/ioctl.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <systemd/sd-bus.h>


int
main(int argc, char *argv[])
{
  sd_bus *bus = NULL;
  sd_bus_error error = SD_BUS_ERROR_NULL;
  sd_bus_message *message = NULL;
  int r,val;

  if ( argc != 2 ){
    fprintf(stderr,"USage tmp NUMBER\n");
    exit(1);
  }

  val = atoi(argv[1]);
  /* r = sd_bus_open_systaem(&bus); */
  r = sd_bus_open_user(&bus);
  if ( r < 0 )  {
    printf("Error : %s\n", strerror(r));
    exit(1);
  }

  r = sd_bus_call_method(bus,
                         "com.seescan.Logging1",
                         "/com/seescan/Logging1",
                         "com.seescan.Logging1.Log",
                         "setHeartbeatTime",
                         &error,
                         &message,
                         "u",
                         val
                         );

      if (r < 0)
  {
      fprintf(stderr, "Failed to issue method call: %s\n", error.message);
      exit(1);
  }



}
