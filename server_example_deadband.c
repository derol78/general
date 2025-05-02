 #include "iec61850_server.h"
#include "hal_thread.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "static_model.h"

extern IedModel iedModel;

static int running = 0;
static IedServer iedServer = NULL;
static int sleepTime = 1000;   // Default sleep time in ms
static int nrOffSignals = 1;  // Default number of signals

void sigint_handler(int signalId) {
    running = 0;
}

static void connectionHandler(IedServer self, ClientConnection connection, bool connected, void* parameter) {
    if (connected)
        printf("Connection opened\n");
    else
        printf("Connection closed\n");
}

// Function to retrieve the configuration file path
void getConfigFilePath(char* path, int size) {
    snprintf(path, size, "./config.txt"); // Assuming config file is in the application's root directory
}

// Function to read values from the configuration file
void readConfigFile() {
    char configPath[256];
    getConfigFilePath(configPath, sizeof(configPath));

    FILE *file = fopen(configPath, "r");
    if (file) {
        char line[100];
        char key[50];
        int value;

        while (fgets(line, sizeof(line), file) != NULL) {
            // Ignore comment lines
            if (line[0] == '#') continue;

            // Parse key-value pairs
            if (sscanf(line, "%49s %d", key, &value) == 2) {
                if (strcmp(key, "sleepTime") == 0) {
                    sleepTime = value;
                } else if (strcmp(key, "nrOffSignals") == 0) {
                    nrOffSignals = value;
                }
            }
        }
        fclose(file);
    } else {
        printf("Warning: Config file not found. Using default values.\n");
    }
}


int main(int argc, char** argv) {
    printf("Using libIEC61850 version %s\n", LibIEC61850_getVersionString());

    readConfigFile();  // Load configuration values

    printf("Configured sleepTime: %d ms\n", sleepTime);
    printf("Configured nrOffSignals: %d\n", nrOffSignals);

    IedServerConfig config = IedServerConfig_create();
    IedServerConfig_setReportBufferSize(config, 200000);
    IedServerConfig_setEdition(config, IEC_61850_EDITION_2);
    IedServerConfig_enableFileService(config, false);
    IedServerConfig_enableDynamicDataSetService(config, true);
    IedServerConfig_enableLogService(config, false);
    IedServerConfig_setMaxMmsConnections(config, 5);

    iedServer = IedServer_createWithConfig(&iedModel, NULL, config);
    IedServerConfig_destroy(config);

    IedServer_setServerIdentity(iedServer, "libiec61850.com", "deadband example", "1.5.0");
    IedServer_setConnectionIndicationHandler(iedServer, connectionHandler, NULL);
    IedServer_setWriteAccessPolicy(iedServer, IEC61850_FC_CF, ACCESS_POLICY_ALLOW);

    IedServer_start(iedServer, 102);
    if (!IedServer_isRunning(iedServer)) {
        printf("Starting server failed! Exit.\n");
        IedServer_destroy(iedServer);
        exit(-1);
    }

    running = 1;
    signal(SIGINT, sigint_handler);

    float acc = 0;
    while (running) {
        uint64_t timestamp = Hal_getTimeInMs();
        if(acc==10){
            acc=0;
        }
        acc += 1;

        Timestamp iecTimestamp;
        Timestamp_clearFlags(&iecTimestamp);
        Timestamp_setTimeInMilliseconds(&iecTimestamp, timestamp);
        Timestamp_setLeapSecondKnown(&iecTimestamp, true);

        IedServer_lockDataModel(iedServer);

        // Update all signals dynamically based on nrOffSignals

        if(nrOffSignals >= 1){
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn1_mag_f, acc);
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn1_instMag_f, acc);
            IedServer_updateTimestampAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn1_t, &iecTimestamp);
        }
        if(nrOffSignals >= 2){
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn2_mag_f, acc);
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn2_instMag_f, acc);
            IedServer_updateTimestampAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn2_t, &iecTimestamp);
        }
        if(nrOffSignals >= 3){
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn3_mag_f, acc);
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn3_instMag_f, acc);
            IedServer_updateTimestampAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn3_t, &iecTimestamp);
        }
        if(nrOffSignals >= 4){
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn4_mag_f, acc);
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn4_instMag_f, acc);
            IedServer_updateTimestampAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn4_t, &iecTimestamp);
        }
        if(nrOffSignals >= 5){
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn5_mag_f, acc);
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn5_instMag_f, acc);
            IedServer_updateTimestampAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn5_t, &iecTimestamp);
        }
        if(nrOffSignals >= 6){
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn6_mag_f, acc);
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn6_instMag_f, acc);
            IedServer_updateTimestampAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn6_t, &iecTimestamp);
        }
        if(nrOffSignals >= 7){
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn7_mag_f, acc);
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn7_instMag_f, acc);
            IedServer_updateTimestampAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn7_t, &iecTimestamp);
        }
        if(nrOffSignals >= 8){
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn8_mag_f, acc);
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn8_instMag_f, acc);
            IedServer_updateTimestampAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn8_t, &iecTimestamp);
        }
        if(nrOffSignals >= 9){
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn9_mag_f, acc);
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn9_instMag_f, acc);
            IedServer_updateTimestampAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn9_t, &iecTimestamp);
        }
        if(nrOffSignals >= 10){
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn10_mag_f, acc);
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn10_instMag_f, acc);
            IedServer_updateTimestampAttributeValue(iedServer, IEDMODEL_LD1_AnInGGIO1_AnIn10_t, &iecTimestamp);
        }


        IedServer_unlockDataModel(iedServer);
        Thread_sleep(sleepTime);
    }

    IedServer_stop(iedServer);
    IedServer_destroy(iedServer);

    return 0;
}
