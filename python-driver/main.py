from SimConnect import *
from time import sleep

# https://pastebin.com/fMdB7at2

# Fonctionne avec WASImUI et l'instuction :
# 1 (>H:AS1000_MFD_SOFTKEYS_1) dans execute_calculator_code

sm = SimConnect()

aq = AircraftRequests(sm, _time=20)

altitude = aq.get("PLANE_ALTITUDE")
print(altitude)
# altitude = altitude + 10000

# # Set the aircraft's current altitude
# aq.set("PLANE_ALTITUDE", altitude)
# sleep(0.1)

ae = AircraftEvents(sm)

event = ae.find(b"MobiFlight.AS1000_PFD_SOFTKEYS_8")
print(event())
sleep(0.01)


sm.exit()

quit()
