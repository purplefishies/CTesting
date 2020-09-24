/* gcc main.c -lsystemd */

#include <systemd/sd-bus.h>
#include <stdio.h>
#include <stdlib.h>
#include <systemd/sd-bus.h>

static inline const char*
strna(const char* s)
{
    return s ?: "n/a";
}

int32_t
message_callback(sd_bus_message* m, void* userdata, sd_bus_error* ret_error)
{
    printf("callback: path=%s interface=%s member=%s\n",
           strna(sd_bus_message_get_path(m)),
           strna(sd_bus_message_get_interface(m)),
           strna(sd_bus_message_get_member(m)));
    return 0;
}

#define LOG_OBJECT_PATH "/com/seescan/Logging1"
#define LOG_INTERFACE_NAME "com.seescan.Logging1.Log"
#define LOG_SERVICE_NAME "com.seescan.Logging1"
#define LOG_HEARTBEAT_SIGNAL "heartbeat"

typedef struct waiting_control_t
{
    sd_bus_slot* slot;
    int found;
} waiting_control_t;

static int32_t
test_callback(sd_bus_message* message, void* userdata, sd_bus_error* error)
{

    waiting_control_t* ud = userdata;
    if (ud)
    {
        printf("callback called\n");
        ud->found = 1;
        sd_bus_slot_unref(ud->slot);
    }

    return EXIT_SUCCESS;
}

#define SECONDS(X) (X * 1000 * 1000)

int32_t
wait_for_signal(sd_bus* bus, char* match, uint64_t time_microseconds)
{

    int32_t r;
    int32_t found          = 0;
    waiting_control_t data = { .slot = NULL, .found = 0 };
    sd_bus_error err       = SD_BUS_ERROR_NULL;



    int32_t tcb(sd_bus_message* message, void* userdata, sd_bus_error* error)
    {
        
        waiting_control_t* ud = userdata;
        if (ud)
        {
            printf("CALLBACK CALLED\n");
            ud->found = 1;
            sd_bus_slot_unref(ud->slot);
        }
        
        return EXIT_SUCCESS;
    }

    sd_bus_add_match(bus, &data.slot, match, tcb, &data);
    /* sd_bus_add_match(bus, &data.slot, match, test_callback, &data); */
    do
    {

        r = sd_bus_process(bus, NULL);
        if (r < 0)
        {
            fprintf(stderr, "Failed to process bus: %s\n", strerror(-r));
            break;
        }
        r = sd_bus_wait(bus, 1000);
    } while (!data.found && (time_microseconds-=1000) > 0);

    if (data.found)
        return 0;
    else
        return -1;
}

int
main(int argc, char* argv[])
{

    sd_bus* bus = NULL;

    char* msg      = NULL;
    void* userdata = NULL;
    if (argc != 2)
    {
        fprintf(stderr, "Usage: wait_for_signal  WAIT_TIME_IN_SECONDS\n");
        exit(1);
    }
    int wait_time_seconds = atoi(argv[1]);

    int32_t r = sd_bus_open_user(&bus);

#ifdef NEWSYSTEMD
    sd_bus_match_signal(bus,                  /* bus */
                        NULL,                 /* slot */
                        NULL,                 /* sender */
                        LOG_OBJECT_PATH,      /* path */
                        LOG_INTERFACE_NAME,   /* interface */
                        LOG_HEARTBEAT_SIGNAL, /* member */
                        test_callback userdata);
#else
    sd_bus_add_match(bus,
                     NULL,
                     "type='signal',interface='com.seescan.Logging1.Log',member='heartbeat'",
                     test_callback,
                     userdata);
#endif

    r = wait_for_signal(bus,
                        "type='signal',interface='com.seescan.Logging1.Log',member='heartbeat'",
                        SECONDS(wait_time_seconds));

    if ( r < 0 ) {
        printf("Bad\n");
    } else {
        printf("Good\n");
    }
    /* sd_bus_message_unref(ret); */
    sd_bus_unref(bus);
    return 0;
}
