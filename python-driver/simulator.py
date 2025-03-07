import pygame

# import wasimconnect as wa

from data import Button
from ui import Ui

# pygame setup

running = True
simui = Ui()


# sim = wa.WASimConnect()
# sim.connect()

while running:
    # poll for events
    # pygame.QUIT event means the user clicked X to close your window
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.MOUSEBUTTONUP:
            pos = pygame.mouse.get_pos()
            for i in range(12):
                if simui.pfd_softkey[i].collidepoint(pos):
                    print(f"clicked PFD Softkey {i+1}")
                if simui.mfd_softkey[i].collidepoint(pos):
                    print(f"clicked MFD Softkey {i+1}")

            for i in Button:
                if simui.buttons[i.value] is not None and simui.buttons[i.value].collidepoint(pos):
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
                            simui.led_status[i.value] = not simui.led_status[i.value]

    # renderscreen here
    simui.render()

    simui.clock.tick(60)  # limits FPS to 60

pygame.quit()
