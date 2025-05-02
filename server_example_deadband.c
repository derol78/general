/*
 *  server_example_deadband.c
 *
 *  - How to handle dead bands for measured values (MV)
 *  - Use variable and fixed dead band with db and dbRef (edition 2.1)
 *  - Use fixed dead band with db and rangeC (edition 2)
 */

#include "iec61850_server.h"
#include "hal_thread.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "static_model.h"

/* import IEC 61850 device model created from SCL-File */
extern IedModel iedModel;

static int running = 0;
static IedServer iedServer = NULL;

void
sigint_handler(int signalId)
{
    running = 0;
}

static void
connectionHandler (IedServer self, ClientConnection connection, bool connected, void* parameter)
{
    if (connected)
        printf("Connection opened\n");
    else
        printf("Connection closed\n");
}

int
main(int argc, char** argv)
{
    printf("Using libIEC61850 version %s\n", LibIEC61850_getVersionString());

    /* Create new server configuration object */
    IedServerConfig config = IedServerConfig_create();

    /* Set buffer size for buffered report control blocks to 200000 bytes */
    IedServerConfig_setReportBufferSize(config, 200000);

    /* Set stack compliance to a specific edition of the standard (WARNING: data model has also to be checked for compliance) */
    IedServerConfig_setEdition(config, IEC_61850_EDITION_2);

    /* disable MMS file service */
    IedServerConfig_enableFileService(config, false);

    /* enable dynamic data set service */
    IedServerConfig_enableDynamicDataSetService(config, true);

    /* disable log service */
    IedServerConfig_enableLogService(config, false);

    /* set maximum number of clients */
    IedServerConfig_setMaxMmsConnections(config, 5);

    /* Create a new IEC 61850 server instance */
    iedServer = IedServer_createWithConfig(&iedModel, NULL, config);

    /* configuration object is no longer required */
    IedServerConfig_destroy(config);

    /* set the identity values for MMS identify service */
    IedServer_setServerIdentity(iedServer, "libiec61850.com", "deadband example", "1.5.0");

    IedServer_setConnectionIndicationHandler(iedServer, (IedConnectionIndicationHandler) connectionHandler, NULL);

    /* Allow write access to CF parameters (here "db" and "rangeC") */
    IedServer_setWriteAccessPolicy(iedServer, IEC61850_FC_CF, ACCESS_POLICY_ALLOW);

    /* MMS server will be instructed to start listening for client connections. */
    IedServer_start(iedServer, 102);

    if (!IedServer_isRunning(iedServer)) {
        printf("Starting server failed (maybe need root permissions or another server is already using the port)! Exit.\n");
        IedServer_destroy(iedServer);
        exit(-1);
    }

    running = 1;

    signal(SIGINT, sigint_handler);

    float t = 0.f;
    float acc = -1;

    while (running) {
        uint64_t timestamp = Hal_getTimeInMs();

        acc += 1;

        Timestamp iecTimestamp;

        Timestamp_clearFlags(&iecTimestamp);
        Timestamp_setTimeInMilliseconds(&iecTimestamp, timestamp);
        Timestamp_setLeapSecondKnown(&iecTimestamp, true);
        IedServer_lockDataModel(iedServer);
        
        
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn1_mag_f, acc);
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn1_instMag_f, acc);
        IedServer_updateTimestampAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn1_t, &iecTimestamp);
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn2_mag_f, acc);
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn2_instMag_f, acc);
        IedServer_updateTimestampAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn2_t, &iecTimestamp);
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn3_mag_f, acc);
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn3_instMag_f, acc);
        IedServer_updateTimestampAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn3_t, &iecTimestamp);
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn4_mag_f, acc);
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn4_instMag_f, acc);
        IedServer_updateTimestampAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn4_t, &iecTimestamp);
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn5_mag_f, acc);
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn5_instMag_f, acc);
        IedServer_updateTimestampAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn5_t, &iecTimestamp);
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn6_mag_f, acc);
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn6_instMag_f, acc);
        IedServer_updateTimestampAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn6_t, &iecTimestamp);
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn7_mag_f, acc);
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn7_instMag_f, acc);
        IedServer_updateTimestampAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn7_t, &iecTimestamp);
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn8_mag_f, acc);
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn8_instMag_f, acc);
        IedServer_updateTimestampAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn8_t, &iecTimestamp);
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn9_mag_f, acc);
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn9_instMag_f, acc);
        IedServer_updateTimestampAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn9_t, &iecTimestamp);
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn10_mag_f, acc);
        IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn10_instMag_f, acc);
        IedServer_updateTimestampAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn10_t, &iecTimestamp);
        
        IedServer_unlockDataModel(iedServer);

        Thread_sleep(1000);
    }

    /* stop MMS server - close TCP server socket and all client sockets */
    IedServer_stop(iedServer);

    /* Cleanup - free all resources */
    IedServer_destroy(iedServer);

    return 0;
} /* main() */
