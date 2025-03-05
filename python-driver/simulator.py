import pygame

from enum import Enum

BUTTON_COUNT = 93
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
    PMDF_ENCODER_OUTER_LEFT = 20
    PMDF_ENCODER_OUTER_RIGHT = 21
    PMDF_ENCODER_INNER_LEFT = 22
    PMDF_ENCODER_INNER_RIGHT = 23
    PMDF_ENCODER_PUSH = 24
    MIX_ENCODER_OUTER_LEFT = 25
    MIX_ENCODER_OUTER_RIGHT = 26
    MIX_ENCODER_INNER_LEFT = 27
    MIX_ENCODER_INNER_RIGHT = 28
    MIX_ENCODER_PUSH = 29
    COMM_ENCODER_OUTER_LEFT = 30
    COMM_ENCODER_OUTER_RIGHT = 31
    COMM_ENCODER_INNER_LEFT = 32
    COMM_ENCODER_INNER_RIGHT = 33
    COMM_ENCODER_PUSH = 34
    NAV_ENCODER_OUTER_LEFT = 35
    NAV_ENCODER_OUTER_RIGHT = 36
    NAV_ENCODER_INNER_LEFT = 37
    NAV_ENCODER_INNER_RIGHT = 38
    NAV_ENCODER_PUSH = 39
    INNER_LED = 40
    MIDDLE_LED = 41
    OUTER_LED = 42
    COMM_SWAP = 43
    COMM_MODE = 44
    NAV_SWAP = 45
    NAV_MODE = 46
    DIMM1 = 47
    DIMM2 = 48
    DIMM3 = 49
    HDG_BUG = 50
    APPR = 51
    NAV = 52
    BC = 53
    HDG_BUG_LEFT = 54
    HDG_BUG_RIGHT = 55
    HDG_BUG_PUSH = 56
    CRS1_BUG_LEFT = 57
    CRS1_BUG_RIGHT = 58
    CRS1_BUG_PUSH = 59
    AP = 60
    FD = 61
    BANK = 62
    AUTO_THROTTLE = 63
    YAW_DAMPER = 64
    BARO_DEC = 65
    BARO_INC = 66
    CRS2_BUG_LEFT = 67
    CRS2_BUG_RIGHT = 68
    CRS2_BUG_PUSH = 69
    ALT_OUTER_LEFT = 70
    ALT_OUTER_RIGHT = 71
    ALT_INNER_LEFT = 72
    ALT_INNER_RIGHT = 73
    ALT_BUG_PUSH = 74
    ALT = 75
    VS = 76
    VNV = 77
    VS_BUG_LEFT = 78
    VS_BUG_RIGHT = 79
    VS_BUG_PUSH = 80
    FLC = 81
    SPEED_BUG_LEFT = 82
    SPEED_BUG_RIGHT = 83
    SPEED_BUG_PUSH = 84
    SPEED = 85
    JOYSTICK_LEFT = 86
    JOYSTICK_RIGHT = 87
    JOYSTICK_UP = 88
    JOYSTICK_DOWN = 89
    JOYSTICK_ROTATE_LEFT = 90
    JOYSTICK_ROTATE_RIGHT = 91
    JOYSTICK_PUSH = 92

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

def draw_dual_encoder(x, y, button_item_outer_left, button_item_outer_right, button_item_inner_left, button_item_inner_right, button_item_push, texte):
    global buttons, led_status, screen
    rect = pygame.Rect(x, y, 30, 20)
    pygame.draw.rect(screen, BUTTON_COLOR, rect)
    buttons[button_item_outer_left.value] = rect
    
    font = pygame.font.Font(None, FONT_SIZE)
    text = font.render("<<", True, WHITE)
    text_rect = text.get_rect(center=(x + 30/2, y + 20/2))
    screen.blit(text, text_rect)
    
    rect = pygame.Rect(x + 35, y, 30, 20)
    pygame.draw.rect(screen, BUTTON_COLOR, rect)
    buttons[button_item_outer_right.value] = rect
    
    text = font.render(">>", True, WHITE)
    text_rect = text.get_rect(center=(x + 35 + 30/2, y + 20/2))
    screen.blit(text, text_rect)
    
    rect = pygame.Rect(x, y + 25, 65, 20)
    pygame.draw.rect(screen, BUTTON_COLOR, rect)
    buttons[button_item_push.value] = rect
    
    text = font.render(texte, True, WHITE)
    text_rect = text.get_rect(center=(x + 65/2, y + 25 + 20/2))
    screen.blit(text, text_rect)
    
    rect = pygame.Rect(x, y + 50, 30, 20)
    pygame.draw.rect(screen, BUTTON_COLOR, rect)
    buttons[button_item_inner_left.value] = rect
    
    text = font.render("<", True, WHITE)
    text_rect = text.get_rect(center=(x + 30/2, y + 50 + 20/2))
    screen.blit(text, text_rect)
    
    rect = pygame.Rect(x + 35, y + 50, 30, 20)
    pygame.draw.rect(screen, BUTTON_COLOR, rect)
    buttons[button_item_inner_right.value] = rect
    
    text = font.render(">", True, WHITE)
    text_rect = text.get_rect(center=(x + 35 + 30/2, y + 50 + 20/2))
    screen.blit(text, text_rect)

def draw_single_encoder(x, y, button_item_outer_left, button_item_outer_right, button_item_push, texte):
    global buttons, led_status, screen
    rect = pygame.Rect(x, y, 30, 20)
    pygame.draw.rect(screen, BUTTON_COLOR, rect)
    buttons[button_item_outer_left.value] = rect
    
    font = pygame.font.Font(None, FONT_SIZE)
    text = font.render("<<", True, WHITE)
    text_rect = text.get_rect(center=(x + 30/2, y + 20/2))
    screen.blit(text, text_rect)
    
    rect = pygame.Rect(x + 35, y, 30, 20)
    pygame.draw.rect(screen, BUTTON_COLOR, rect)
    buttons[button_item_outer_right.value] = rect
    
    text = font.render(">>", True, WHITE)
    text_rect = text.get_rect(center=(x + 35 + 30/2, y + 20/2))
    screen.blit(text, text_rect)
    
    rect = pygame.Rect(x, y + 25, 65, 20)
    pygame.draw.rect(screen, BUTTON_COLOR, rect)
    buttons[button_item_push.value] = rect
    
    text = font.render(texte, True, WHITE)
    text_rect = text.get_rect(center=(x + 65/2, y + 25 + 20/2))
    screen.blit(text, text_rect)
    
def draw_joystick(x, y, button_left, button_right, button_up, button_down, button_r_left, button_r_right, button_push, text):
    global buttons, led_status, screen
    rect = pygame.Rect(x, y, 20, 20)
    pygame.draw.rect(screen, BUTTON_COLOR, rect)
    buttons[button_r_left.value] = rect
    
    font = pygame.font.Font(None, FONT_SIZE)
    text = font.render("<", True, WHITE)
    text_rect = text.get_rect(center=(x + 20/2, y + 20/2))
    screen.blit(text, text_rect)
    
    rect = pygame.Rect(x + 25, y, 20, 20)
    pygame.draw.rect(screen, BUTTON_COLOR, rect)
    buttons[button_up.value] = rect
    
    font = pygame.font.Font(None, FONT_SIZE)
    text = font.render("N", True, WHITE)
    text_rect = text.get_rect(center=(x + 25 + 20/2, y + 20/2))
    screen.blit(text, text_rect)
    
    rect = pygame.Rect(x + 50, y, 20, 20)
    pygame.draw.rect(screen, BUTTON_COLOR, rect)
    buttons[button_r_right.value] = rect
    
    font = pygame.font.Font(None, FONT_SIZE)
    text = font.render(">", True, WHITE)
    text_rect = text.get_rect(center=(x + 50 + 20/2, y + 20/2))
    screen.blit(text, text_rect)
    
    rect = pygame.Rect(x, y + 25, 20, 20)
    pygame.draw.rect(screen, BUTTON_COLOR, rect)
    buttons[button_left.value] = rect
    
    font = pygame.font.Font(None, FONT_SIZE)
    text = font.render("W", True, WHITE)
    text_rect = text.get_rect(center=(x + 20/2, y + 25 + 20/2))
    screen.blit(text, text_rect)
    
    rect = pygame.Rect(x + 25, y + 25, 20, 20)
    pygame.draw.rect(screen, BUTTON_COLOR, rect)
    buttons[button_push.value] = rect
    
    font = pygame.font.Font(None, FONT_SIZE)
    text = font.render(" ", True, WHITE)
    text_rect = text.get_rect(center=(x + 25 + 20/2, y + 25 + 20/2))
    screen.blit(text, text_rect)
    
    rect = pygame.Rect(x + 50, y + 25, 20, 20)
    pygame.draw.rect(screen, BUTTON_COLOR, rect)
    buttons[button_right.value] = rect
    
    font = pygame.font.Font(None, FONT_SIZE)
    text = font.render("E", True, WHITE)
    text_rect = text.get_rect(center=(x + 50 + 20/2, y + 25 + 20/2))
    screen.blit(text, text_rect)
    
    rect = pygame.Rect(x + 25, y + 50, 20, 20)
    pygame.draw.rect(screen, BUTTON_COLOR, rect)
    buttons[button_down.value] = rect
    
    font = pygame.font.Font(None, FONT_SIZE)
    text = font.render("S", True, WHITE)
    text_rect = text.get_rect(center=(x + 25 + 20/2, y + 50 + 20/2))
    screen.blit(text, text_rect)

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
    screen.fill((45, 45, 45))

    # RENDER YOUR GAME HERE
    
    # PFD/MFD
    font = pygame.font.Font(None, FONT_SIZE)
        
    for i in range(12):
        rect = pygame.Rect(52 * i + 50, 20, BUTTON_WIDTH, BUTTON_HEIGHT)
        pygame.draw.rect(screen, BUTTON_COLOR, rect)
        pfd_softkey.append(rect)
        
        text = font.render(f"{i + 1}", True, WHITE)
        text_rect = text.get_rect(center=(52 * i + 50 + BUTTON_WIDTH/2, 20 + BUTTON_HEIGHT/2))
        screen.blit(text, text_rect)
        
        rect = pygame.Rect(52 * i + 50, 60, BUTTON_WIDTH, BUTTON_HEIGHT)
        pygame.draw.rect(screen, BUTTON_COLOR, rect)
        mfd_softkey.append(rect)
        
        text_rect = text.get_rect(center=(52 * i + 50 + BUTTON_WIDTH/2, 60 + BUTTON_HEIGHT/2))
        screen.blit(text, text_rect)

    # G1000
    draw_button_and_led(50, 150, Button.PFD_SELECT, "PFD")
    draw_button_and_led(50, 190, Button.MFD_SELECT, "MFD")
    
    draw_dual_encoder(
        150, 
        150, 
        Button.PMDF_ENCODER_OUTER_LEFT, 
        Button.PMDF_ENCODER_OUTER_RIGHT, 
        Button.PMDF_ENCODER_INNER_LEFT, 
        Button.PMDF_ENCODER_INNER_RIGHT, 
        Button.PMDF_ENCODER_PUSH, 
        "PMFD"
        )
    
    draw_button(300, 150, Button.DIRECTTO, "GOTO")
    draw_button(360, 150, Button.FPL, "FPL")
    draw_button(420, 150, Button.CLEAR, "CLEAR")
    draw_button(300, 190, Button.MENU, "MENU")
    draw_button(360, 190, Button.PROC, "PROC")
    draw_button(420, 190, Button.ENTER, "ENTER")
    
    draw_joystick(
        500, 
        150, 
        Button.JOYSTICK_LEFT,
        Button.JOYSTICK_RIGHT,
        Button.JOYSTICK_UP,
        Button.JOYSTICK_DOWN,
        Button.JOYSTICK_ROTATE_LEFT,
        Button.JOYSTICK_ROTATE_RIGHT,
        Button.JOYSTICK_PUSH,
        "JOY")
    
    draw_single_encoder(600, 150, Button.DIMM1, Button.DIMM2, Button.DIMM3, "Dimm")
    
    # RADIO
    draw_dual_encoder(
        100, 
        250, 
        Button.COMM_ENCODER_OUTER_LEFT, 
        Button.COMM_ENCODER_OUTER_RIGHT, 
        Button.COMM_ENCODER_INNER_LEFT, 
        Button.COMM_ENCODER_INNER_RIGHT, 
        Button.COMM_ENCODER_PUSH, 
        "COMM"
        )
    
    draw_button(175, 250, Button.COMM_SWAP, "SWAP")
    draw_button(175, 290, Button.COMM_MODE, "MODE")
    draw_button(490, 250, Button.NAV_SWAP, "SWAP")
    draw_button(490, 290, Button.NAV_MODE, "MODE")
    
    draw_dual_encoder(
        550, 
        250, 
        Button.NAV_ENCODER_OUTER_LEFT, 
        Button.NAV_ENCODER_OUTER_RIGHT, 
        Button.NAV_ENCODER_INNER_LEFT, 
        Button.NAV_ENCODER_INNER_RIGHT, 
        Button.NAV_ENCODER_PUSH, 
        "NAV"
        )
    
    # Audio Mix
    color = (0, 0, 255) if led_status[Button.OUTER_LED.value] else (180, 180, 180)
    rect = pygame.Rect(50, 350, 20, 20)
    pygame.draw.rect(screen, color, rect)
    buttons[Button.OUTER_LED.value] = rect
    
    color = (255, 0xbf, 0) if led_status[Button.MIDDLE_LED.value] else (180, 180, 180)
    rect = pygame.Rect(50, 375, 20, 20)
    pygame.draw.rect(screen, color, rect)
    buttons[Button.MIDDLE_LED.value] = rect
    
    color = (255, 255, 255) if led_status[Button.INNER_LED.value] else (180, 180, 180)
    rect = pygame.Rect(50, 400, 20, 20)
    pygame.draw.rect(screen, color, rect)
    buttons[Button.INNER_LED.value] = rect
    
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
    
    draw_dual_encoder(
        550, 
        350, 
        Button.MIX_ENCODER_OUTER_LEFT, 
        Button.MIX_ENCODER_OUTER_RIGHT, 
        Button.MIX_ENCODER_INNER_LEFT, 
        Button.MIX_ENCODER_INNER_RIGHT, 
        Button.MIX_ENCODER_PUSH, 
        "MAN/SQ"
        )

    # AP
    draw_button_and_led(100, 450, Button.HDG_BUG, "HDG")
    draw_button_and_led(175, 450, Button.APPR, "APPR")
    draw_button_and_led(175, 490, Button.BC, "BC")
    draw_button_and_led(250, 450, Button.NAV, "NAV")
    
    draw_single_encoder(
        100, 
        490, 
        Button.HDG_BUG_LEFT, 
        Button.HDG_BUG_RIGHT, 
        Button.HDG_BUG_PUSH, 
        "HDG_BUG"
        )
    
    draw_single_encoder(
        250, 
        490, 
        Button.CRS1_BUG_LEFT, 
        Button.CRS1_BUG_RIGHT, 
        Button.CRS1_BUG_PUSH, 
        "CRS1_BUG"
        )
    
    draw_button_and_led(350, 450, Button.AP, "AP")
    draw_button_and_led(350, 490, Button.BANK, "BANK")
    draw_button_and_led(425, 450, Button.FD, "FD")
    draw_button_and_led(425, 490, Button.AUTO_THROTTLE, "AUTO_T")
    
    draw_button_and_led(525, 450, Button.YAW_DAMPER, "YD")
    draw_dual_encoder(
        525, 
        490, 
        Button.BARO_DEC,
        Button.BARO_INC,
        Button.CRS2_BUG_LEFT, 
        Button.CRS2_BUG_RIGHT, 
        Button.CRS2_BUG_PUSH, 
        "CRS2_BUG"
        )

    draw_dual_encoder(
        100, 
        580, 
        Button.ALT_OUTER_LEFT,
        Button.ALT_OUTER_RIGHT,
        Button.ALT_INNER_LEFT, 
        Button.ALT_INNER_RIGHT, 
        Button.ALT_BUG_PUSH, 
        "ALT"
        )

    draw_button_and_led(175, 605, Button.ALT, "ALT")

    draw_button_and_led(275, 580, Button.VS, "VS")
    draw_button_and_led(275, 620, Button.VNV, "VNV")
    
    draw_single_encoder(
        350, 
        580, 
        Button.VS_BUG_LEFT, 
        Button.VS_BUG_RIGHT, 
        Button.VS_BUG_PUSH, 
        "VS/FLC"
        )
    

    draw_button_and_led(425, 605, Button.FLC, "FLC")
    
    draw_single_encoder(
        525, 
        580, 
        Button.SPEED_BUG_LEFT, 
        Button.SPEED_BUG_RIGHT, 
        Button.SPEED_BUG_PUSH, 
        "SPEED"
        )
    draw_button_and_led(600, 605, Button.SPEED, "SPEED")


    # flip() the display to put your work on screen
    pygame.display.flip()

    clock.tick(60)  # limits FPS to 60

pygame.quit()