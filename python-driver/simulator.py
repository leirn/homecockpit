import pygame
import sys
from os import path as os_path
from time import sleep

# first we need to specify a .NET runtime config, which is stored in a file
# this is in case the default isn't .NET 5, which is what the WASimClient assembly uses
from clr_loader import get_coreclr
from pythonnet import set_runtime

set_runtime(get_coreclr(runtime_config="app.runtime.json"))
# now we can import clr from PythonNet
import clr

# this needs to be used  if DLL is not in the same folder or otherwise in the system path
# assembly_path = "./"
# sys.path.insert(0, assembly_path)

# this ensures this script's location (and the DLL) is in the search path in case it's  being run from a different location
sys.path.insert(0, os_path.dirname(os_path.realpath(__file__)))

# now we can finally load our assembly...
clr.AddReference("WASimCommander.WASimClient")
# ... and import what we need
from WASimCommander.CLI.Client import WASimClient
from WASimCommander.CLI import ValueTypes
from WASimCommander.CLI.Enums import (
    HR,
    LogLevel,
    LogFacility,
    LogSource,
    CalcResultType,
    LookupItemType,
    UpdatePeriod,
    CommandId,
)
from WASimCommander.CLI.Structs import VariableRequest, DataRequest, Command

from System import Single
from System.Threading import AutoResetEvent

# An event wait handle is used in this test/demo to keep the program alive while data processes in the background.
# (We could use a Python threading.Event() but those need to be reset manually, so the .NET one is simpler to use.)
g_dataUpdateEvent = AutoResetEvent(False)


# This is an event handler for printing Client and Server log messages
def LogHandler(log_record, log_source):
    Log(f"{log_source} Log: {log_record}", "@@")
    # LogRecord has a convenience ToString() override


# Event handler to print the current Client status.
def ClientStatusHandler(client_event):
    Log(
        f'Client event {client_event.eventType} - "{client_event.message}"; Client status: {client_event.status}',
        "^^",
    )


# Event handler for showing listing results (eg. local vars list)
def ListResultsHandler(list_result):
    Log(list_result.ToString())
    # just use the ToString() override
    # signal completion
    g_dataUpdateEvent.Set()


# Event handler to process data value subscription updates.
def DataSubscriptionHandler(data_request_record):
    print(
        f'<< Got Data for request {data_request_record.requestId} "{data_request_record.nameOrCode}" with Value: ',
        end="",
    )
    # Convert the received data into a value using DataRequestRecord's tryConvert() methods.
    # This could be more efficient in a "real" application, but it's good enough for our tests with only 2 value types.
    # Note that in Py we have to explicitly specify the generic parameter type, and use `System.Single` instead of a Py `float` type.
    (ok, f_val) = data_request_record.tryConvert[Single]()
    if ok:
        print(f"(float) {f_val:.2f}")
    else:
        # Our other value type is a string, so this tryConvert() should attempt to use the System.String overload
        (ok, s_val) = data_request_record.tryConvert()
        if ok:
            print(f'(string) "{s_val}"')
        else:
            print("Could not convert result data to value!")
    # signal completion
    g_dataUpdateEvent.Set()


def Log(msg, prfx=":="):
    print(prfx + " " + msg)


from data import Button
from ui import Ui


def connect_to_wasim():
    global client

    client = WASimClient(0x317E57E9)
    hr = HR.OK
    # store method invocation results for logging

    # Connect to Simulator (SimConnect) using default timeout period and network configuration (local Simulator)
    if (hr := client.connectSimulator()) != HR.OK:
        Log("Cannot connect to Simulator, quitting. Error: " + hr.ToString(), "XX")
        client.Dispose()
        return -2

    # Ping the WASimCommander server to make sure it's running and get the server version number (returns zero if no response).
    version = client.pingServer()
    if version == 0:
        Log("Server did not respond to ping, quitting.", "XX")
        client.Dispose()
        return -3

    # Decode version number to dotted format and print it
    Log(
        f"Found WASimModule Server v{version >> 24}.{(version >> 16) & 0xFF}.{(version >> 8) & 0xFF}.{version & 0xFF}"
    )

    # Try to connect to the server, using default timeout value.
    if (hr := client.connectServer()) != HR.OK:
        Log("Server connection failed, quitting. Error: " + hr.ToString(), "XX")
        client.Dispose()
        return -4

    return 0


client = WASimClient(0x317E57E9)


# WASimCommander setup
def main():
    global client
    # pygame setup
    running = True
    simui = Ui()
    connected = False

    Log("Initializing WASimClient...")

    # Monitor client state changes.
    client.OnClientEvent += ClientStatusHandler
    # Subscribe to incoming log record events.
    client.OnLogRecordReceived += LogHandler

    # As a test, set Client's callback logging level to display messages in the console.
    client.setLogLevel(LogLevel.Info, LogFacility.Remote, LogSource.Client)
    # Set client's console log level to None to avoid double logging to our console. (Client also logs to a file by default.)
    client.setLogLevel(LogLevel.Critical, LogFacility.Console, LogSource.Client)
    # Lets also see some log messages from the server
    client.setLogLevel(LogLevel.Info, LogFacility.Remote, LogSource.Server)

    result = connect_to_wasim()
    if result == 0:
        connected = True
    else:
        sleep(0.5)

    while running:
        # poll for events
        # pygame.QUIT event means the user clicked X to close your window
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

                if connected:
                    # Shutdown (really just the Dispose() will close any/all connections anyway, but this is for example).
                    client.disconnectServer()
                    client.disconnectSimulator()
                    # delete the client
                    client.Dispose()
                return 0
            if event.type == pygame.MOUSEBUTTONUP:
                pos = pygame.mouse.get_pos()
                for i in range(12):
                    if simui.pfd_softkey[i].collidepoint(pos):
                        print(f"clicked PFD Softkey {i+1}")
                    if simui.mfd_softkey[i].collidepoint(pos):
                        print(f"clicked MFD Softkey {i+1}")

                for i in Button:
                    if simui.buttons[i.value] is not None and simui.buttons[
                        i.value
                    ].collidepoint(pos):
                        print(f"clicked button {i}")
                        match i:
                            case Button.PFD_SELECT:
                                simui.led_status[Button.PFD_SELECT.value] = True
                                simui.led_status[Button.MFD_SELECT.value] = False
                            case Button.MFD_SELECT:
                                simui.led_status[Button.PFD_SELECT.value] = False
                                simui.led_status[Button.MFD_SELECT.value] = True
                            case Button.MIC1:
                                simui.led_status[Button.MIC1.value] = True
                                simui.led_status[Button.MIC2.value] = False
                                simui.led_status[Button.MIC3.value] = False
                            case Button.MIC2:
                                simui.led_status[Button.MIC1.value] = False
                                simui.led_status[Button.MIC2.value] = True
                                simui.led_status[Button.MIC3.value] = False
                            case Button.MIC3:
                                simui.led_status[Button.MIC1.value] = False
                                simui.led_status[Button.MIC2.value] = False
                                simui.led_status[Button.MIC3.value] = True
                            case _:
                                simui.led_status[i.value] = not simui.led_status[
                                    i.value
                                ]

        # renderscreen here
        simui.render()

        simui.clock.tick(60)  # limits FPS to 60


if __name__ == "__main__":
    try:
        ret = main()
        sys.exit(ret)
    except KeyboardInterrupt:
        sys.exit(0)
    except Exception as e:
        from traceback import format_exc

        print(format_exc())
        sys.exit(-1)
