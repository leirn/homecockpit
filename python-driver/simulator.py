import pygame

from enum import Enum

BUTTON_COUNT = 20
class Button(Enum):
    PFD_SELECT = 0
    MFD_SELECT = 1
    DIRECTTO = 2
    MENU = 3
    PROC = 4
    FPL = 5
    CLEAR = 6
    ENTER = 7
    MKR_MUTE = 8
    COMM1 = 9
    COMM2 = 10
    COMM3 = 11
    NAV1 = 12
    NAV2 = 13
    SENS = 14
    MIC1 = 15
    MIC2 = 16
    MIC3 = 17
    DME = 18
    ADF = 19

# pygame setup
pygame.init()
screen = pygame.display.set_mode((720, 960))
clock = pygame.time.Clock()
running = True

pfd_softkey = []
mfd_softkey = []

led_status = []
buttons = []

LED_COLOR = [
    (127, 127 ,127),
    (0, 255, 0)
]
BUTTON_COLOR = (180, 180, 180)
WHITE = (0, 0, 180)
FONT_SIZE = 20
BUTTON_WIDTH = 48
BUTTON_HEIGHT = 30

for i in range(BUTTON_COUNT):
    led_status.append(i%2==0)
    buttons.append(None)

def draw_button(x, y, button_item, text):
    global buttons, led_status, screen
    rect = pygame.Rect(x, y, BUTTON_WIDTH, BUTTON_HEIGHT)
    pygame.draw.rect(screen, BUTTON_COLOR, rect)
    buttons[button_item.value] = rect
    
    font = pygame.font.Font(None, FONT_SIZE)
    text = font.render(text, True, WHITE)
    text_rect = text.get_rect(center=(x + BUTTON_WIDTH/2, y + BUTTON_HEIGHT/2))
    screen.blit(text, text_rect)

def draw_button_and_led(x, y, button_item, text):
    global buttons, led_status, screen
    rect = pygame.Rect(x, y, BUTTON_WIDTH, BUTTON_HEIGHT)
    pygame.draw.rect(screen, BUTTON_COLOR, rect)
    buttons[button_item.value] = rect
    
    font = pygame.font.Font(None, FONT_SIZE)
    text = font.render(text, True, WHITE)
    text_rect = text.get_rect(center=(x + BUTTON_WIDTH/2, y + BUTTON_HEIGHT/2))
    screen.blit(text, text_rect)
    
    rect = pygame.Rect(x + 50, y, 8, BUTTON_HEIGHT)
    pygame.draw.rect(screen, LED_COLOR[led_status[button_item.value]], rect)



while running:
    # poll for events
    # pygame.QUIT event means the user clicked X to close your window
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.MOUSEBUTTONUP:
            pos = pygame.mouse.get_pos()
            for i in range(12):
                if pfd_softkey[i].collidepoint(pos):
                    print(f"clicked PFD Softkey {i+1}")
                if mfd_softkey[i].collidepoint(pos):
                    print(f"clicked MFD Softkey {i+1}")
                    
            for i in Button:
                if  buttons[i.value] is not None and buttons[i.value].collidepoint(pos):
                    print(f"clicked button {i}")
                    match i:
                        case Button.PFD_SELECT:
                            led_status[Button.PFD_SELECT.value] = True
                            led_status[Button.MFD_SELECT.value] = False
                        case Button.MFD_SELECT:
                            led_status[Button.PFD_SELECT.value] = False
                            led_status[Button.MFD_SELECT.value] = True
                        case Button.MIC1:
                            led_status[Button.MIC1.value] = True
                            led_status[Button.MIC2.value] = False
                            led_status[Button.MIC3.value] = False
                        case Button.MIC2:
                            led_status[Button.MIC1.value] = False
                            led_status[Button.MIC2.value] = True
                            led_status[Button.MIC3.value] = False
                        case Button.MIC3:
                            led_status[Button.MIC1.value] = False
                            led_status[Button.MIC2.value] = False
                            led_status[Button.MIC3.value] = True
                        case _:
                            led_status[i.value] = not led_status[i.value]
                    

    # fill the screen with a color to wipe away anything from last frame
    screen.fill("purple")

    # RENDER YOUR GAME HERE
    color = (255,0,0)
    
    # PFD/MFD
    for i in range(12):
        rect = pygame.Rect(52 * i + 50, 20, 48, 30)
        pygame.draw.rect(screen, color, rect)
        pfd_softkey.append(rect)
        
        rect = pygame.Rect(52 * i + 50, 60, 48, 30)
        pygame.draw.rect(screen, color, rect)
        mfd_softkey.append(rect)

    # G1000
    draw_button_and_led(50, 150, Button.PFD_SELECT, "PFD")
    draw_button_and_led(50, 190, Button.MFD_SELECT, "MFD")
    
    
    draw_button(300, 150, Button.DIRECTTO, "GOTO")
    draw_button(360, 150, Button.FPL, "FPL")
    draw_button(420, 150, Button.CLEAR, "CLEAR")
    draw_button(300, 190, Button.MENU, "MENU")
    draw_button(360, 190, Button.PROC, "PROC")
    draw_button(420, 190, Button.ENTER, "ENTER")
    
    # RADIO
    
    # Audio Mix
    draw_button_and_led(100, 350, Button.MKR_MUTE, "MKR_MUTE")
    draw_button_and_led(175, 350, Button.COMM1, "COMM1")
    draw_button_and_led(250, 350, Button.COMM2, "COMM2")
    draw_button_and_led(325, 350, Button.COMM3, "COMM3")
    draw_button_and_led(400, 350, Button.NAV1, "NAV1")
    draw_button_and_led(475, 350, Button.NAV2, "NAV2")
    
    draw_button_and_led(100, 390, Button.SENS, "HI SENS")
    draw_button_and_led(175, 390, Button.MIC1, "MIC1")
    draw_button_and_led(250, 390, Button.MIC2, "MIC2")
    draw_button_and_led(325, 390, Button.MIC3, "MIC3")
    draw_button_and_led(400, 390, Button.DME, "DME")
    draw_button_and_led(475, 390, Button.ADF, "ADF")

    # flip() the display to put your work on screen
    pygame.display.flip()

    clock.tick(60)  # limits FPS to 60

pygame.quit()