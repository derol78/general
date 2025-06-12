Detta projekt avänder sig av /libiec61850-1.5.1/examples/server_example_deadband.
för att genrera 61850 rapporter i olika stora dataset samt frekvens. Inställningar görs i filen config.txt

1. packa upp libiec61850-1.5.1.tar.gz som finns i repot
2. ersätt filerna /libiec61850-1.5.1/examples/server_example_deadband med det nya som finns i repot:
cid_example_deadband.cid
config.txt
static_model.c
static_model.h
server_example_deadband.c
3. bygg med make och kör server_example_deadband
4 starta upp en 61850 klient och aktivera rapporten AnalogEvents
