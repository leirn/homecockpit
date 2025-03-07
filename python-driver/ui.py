import pygame
from data import Button, BUTTON_COUNT

LED_COLOR = [(127, 127, 127), (0, 255, 0)]
BUTTON_COLOR = (180, 180, 180)
WHITE = (0, 0, 180)
FONT_SIZE = 20
BUTTON_WIDTH = 48
BUTTON_HEIGHT = 30


class Ui:

    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode((720, 960))
        self.clock = pygame.time.Clock()
        
        self.pfd_softkey = []
        self.mfd_softkey = []

        self.led_status = []
        self.buttons = []

        for i in range(BUTTON_COUNT):
            self.led_status.append(i % 2 == 0)
            self.buttons.append(None)

    def draw_button(self,x, y, button_item, text):
        rect = pygame.Rect(x, y, BUTTON_WIDTH, BUTTON_HEIGHT)
        pygame.draw.rect(self.screen, BUTTON_COLOR, rect)
        self.buttons[button_item.value] = rect

        font = pygame.font.Font(None, FONT_SIZE)
        text = font.render(text, True, WHITE)
        text_rect = text.get_rect(center=(x + BUTTON_WIDTH / 2, y + BUTTON_HEIGHT / 2))
        self.screen.blit(text, text_rect)

    def draw_button_and_led(self, x, y, button_item, text):
        self.draw_button(x, y, button_item, text)

        rect = pygame.Rect(x + 50, y, 8, BUTTON_HEIGHT)
        pygame.draw.rect(self.screen, LED_COLOR[self.led_status[button_item.value]], rect)

    def draw_dual_encoder(
        self,
        x,
        y,
        button_item_outer_left,
        button_item_outer_right,
        button_item_inner_left,
        button_item_inner_right,
        button_item_push,
        texte,
    ):
        rect = pygame.Rect(x, y, 30, 20)
        pygame.draw.rect(self.screen, BUTTON_COLOR, rect)
        self.buttons[button_item_outer_left.value] = rect

        font = pygame.font.Font(None, FONT_SIZE)
        text = font.render("<<", True, WHITE)
        text_rect = text.get_rect(center=(x + 30 / 2, y + 20 / 2))
        self.screen.blit(text, text_rect)

        rect = pygame.Rect(x + 35, y, 30, 20)
        pygame.draw.rect(self.screen, BUTTON_COLOR, rect)
        self.buttons[button_item_outer_right.value] = rect

        text = font.render(">>", True, WHITE)
        text_rect = text.get_rect(center=(x + 35 + 30 / 2, y + 20 / 2))
        self.screen.blit(text, text_rect)

        rect = pygame.Rect(x, y + 25, 65, 20)
        pygame.draw.rect(self.screen, BUTTON_COLOR, rect)
        self.buttons[button_item_push.value] = rect

        text = font.render(texte, True, WHITE)
        text_rect = text.get_rect(center=(x + 65 / 2, y + 25 + 20 / 2))
        self.screen.blit(text, text_rect)

        rect = pygame.Rect(x, y + 50, 30, 20)
        pygame.draw.rect(self.screen, BUTTON_COLOR, rect)
        self.buttons[button_item_inner_left.value] = rect

        text = font.render("<", True, WHITE)
        text_rect = text.get_rect(center=(x + 30 / 2, y + 50 + 20 / 2))
        self.screen.blit(text, text_rect)

        rect = pygame.Rect(x + 35, y + 50, 30, 20)
        pygame.draw.rect(self.screen, BUTTON_COLOR, rect)
        self.buttons[button_item_inner_right.value] = rect

        text = font.render(">", True, WHITE)
        text_rect = text.get_rect(center=(x + 35 + 30 / 2, y + 50 + 20 / 2))
        self.screen.blit(text, text_rect)

    def draw_single_encoder(
        self,
        x,
        y,
        button_item_outer_left,
        button_item_outer_right,
        button_item_push,
        texte,
    ):
        rect = pygame.Rect(x, y, 30, 20)
        pygame.draw.rect(self.screen, BUTTON_COLOR, rect)
        self.buttons[button_item_outer_left.value] = rect

        font = pygame.font.Font(None, FONT_SIZE)
        text = font.render("<<", True, WHITE)
        text_rect = text.get_rect(center=(x + 30 / 2, y + 20 / 2))
        self.screen.blit(text, text_rect)

        rect = pygame.Rect(x + 35, y, 30, 20)
        pygame.draw.rect(self.screen, BUTTON_COLOR, rect)
        self.buttons[button_item_outer_right.value] = rect

        text = font.render(">>", True, WHITE)
        text_rect = text.get_rect(center=(x + 35 + 30 / 2, y + 20 / 2))
        self.screen.blit(text, text_rect)

        rect = pygame.Rect(x, y + 25, 65, 20)
        pygame.draw.rect(self.screen, BUTTON_COLOR, rect)
        self.buttons[button_item_push.value] = rect

        text = font.render(texte, True, WHITE)
        text_rect = text.get_rect(center=(x + 65 / 2, y + 25 + 20 / 2))
        self.screen.blit(text, text_rect)

    def draw_joystick(
        self,
        x,
        y,
        button_left,
        button_right,
        button_up,
        button_down,
        button_r_left,
        button_r_right,
        button_push,
    ):
        rect = pygame.Rect(x, y, 20, 20)
        pygame.draw.rect(self.screen, BUTTON_COLOR, rect)
        self.buttons[button_r_left.value] = rect

        font = pygame.font.Font(None, FONT_SIZE)
        text = font.render("<", True, WHITE)
        text_rect = text.get_rect(center=(x + 20 / 2, y + 20 / 2))
        self.screen.blit(text, text_rect)

        rect = pygame.Rect(x + 25, y, 20, 20)
        pygame.draw.rect(self.screen, BUTTON_COLOR, rect)
        self.buttons[button_up.value] = rect

        font = pygame.font.Font(None, FONT_SIZE)
        text = font.render("N", True, WHITE)
        text_rect = text.get_rect(center=(x + 25 + 20 / 2, y + 20 / 2))
        self.screen.blit(text, text_rect)

        rect = pygame.Rect(x + 50, y, 20, 20)
        pygame.draw.rect(self.screen, BUTTON_COLOR, rect)
        self.buttons[button_r_right.value] = rect

        font = pygame.font.Font(None, FONT_SIZE)
        text = font.render(">", True, WHITE)
        text_rect = text.get_rect(center=(x + 50 + 20 / 2, y + 20 / 2))
        self.screen.blit(text, text_rect)

        rect = pygame.Rect(x, y + 25, 20, 20)
        pygame.draw.rect(self.screen, BUTTON_COLOR, rect)
        self.buttons[button_left.value] = rect

        font = pygame.font.Font(None, FONT_SIZE)
        text = font.render("W", True, WHITE)
        text_rect = text.get_rect(center=(x + 20 / 2, y + 25 + 20 / 2))
        self.screen.blit(text, text_rect)

        rect = pygame.Rect(x + 25, y + 25, 20, 20)
        pygame.draw.rect(self.screen, BUTTON_COLOR, rect)
        self.buttons[button_push.value] = rect

        font = pygame.font.Font(None, FONT_SIZE)
        text = font.render(" ", True, WHITE)
        text_rect = text.get_rect(center=(x + 25 + 20 / 2, y + 25 + 20 / 2))
        self.screen.blit(text, text_rect)

        rect = pygame.Rect(x + 50, y + 25, 20, 20)
        pygame.draw.rect(self.screen, BUTTON_COLOR, rect)
        self.buttons[button_right.value] = rect

        font = pygame.font.Font(None, FONT_SIZE)
        text = font.render("E", True, WHITE)
        text_rect = text.get_rect(center=(x + 50 + 20 / 2, y + 25 + 20 / 2))
        self.screen.blit(text, text_rect)

        rect = pygame.Rect(x + 25, y + 50, 20, 20)
        pygame.draw.rect(self.screen, BUTTON_COLOR, rect)
        self.buttons[button_down.value] = rect

        font = pygame.font.Font(None, FONT_SIZE)
        text = font.render("S", True, WHITE)
        text_rect = text.get_rect(center=(x + 25 + 20 / 2, y + 50 + 20 / 2))
        self.screen.blit(text, text_rect)
        
    def render(self):
        self.screen.fill((45, 45, 45))
        self.draw_softkeys()
        self.draw_gdu_utils()
        self.draw_radio()
        self.draw_audio_mix()
        # flip() the display to put your work on screen
        pygame.display.flip()
            
        
    def draw_softkeys(self):# PFD/MFD
        font = pygame.font.Font(None, FONT_SIZE)

        for i in range(12):
            rect = pygame.Rect(52 * i + 50, 20, BUTTON_WIDTH, BUTTON_HEIGHT)
            pygame.draw.rect(self.screen, BUTTON_COLOR, rect)
            self.pfd_softkey.append(rect)

            text = font.render(f"{i + 1}", True, WHITE)
            text_rect = text.get_rect(
                center=(52 * i + 50 + BUTTON_WIDTH / 2, 20 + BUTTON_HEIGHT / 2)
            )
            self.screen.blit(text, text_rect)

            rect = pygame.Rect(52 * i + 50, 60, BUTTON_WIDTH, BUTTON_HEIGHT)
            pygame.draw.rect(self.screen, BUTTON_COLOR, rect)
            self.mfd_softkey.append(rect)

            text_rect = text.get_rect(
                center=(52 * i + 50 + BUTTON_WIDTH / 2, 60 + BUTTON_HEIGHT / 2)
            )
            self.screen.blit(text, text_rect)
        
    def draw_gdu_utils(self):
        # G1000
        self.draw_button_and_led(50, 150, Button.PFD_SELECT, "PFD")
        self.draw_button_and_led(50, 190, Button.MFD_SELECT, "MFD")

        self.draw_dual_encoder(
            150,
            150,
            Button.PMDF_ENCODER_OUTER_LEFT,
            Button.PMDF_ENCODER_OUTER_RIGHT,
            Button.PMDF_ENCODER_INNER_LEFT,
            Button.PMDF_ENCODER_INNER_RIGHT,
            Button.PMDF_ENCODER_PUSH,
            "PMFD",
        )

        self.draw_button(300, 150, Button.DIRECTTO, "GOTO")
        self.draw_button(360, 150, Button.FPL, "FPL")
        self.draw_button(420, 150, Button.CLEAR, "CLEAR")
        self.draw_button(300, 190, Button.MENU, "MENU")
        self.draw_button(360, 190, Button.PROC, "PROC")
        self.draw_button(420, 190, Button.ENTER, "ENTER")

        self.draw_joystick(
            500,
            150,
            Button.JOYSTICK_LEFT,
            Button.JOYSTICK_RIGHT,
            Button.JOYSTICK_UP,
            Button.JOYSTICK_DOWN,
            Button.JOYSTICK_ROTATE_LEFT,
            Button.JOYSTICK_ROTATE_RIGHT,
            Button.JOYSTICK_PUSH,
        )

        self.draw_single_encoder(600, 150, Button.DIMM1, Button.DIMM2, Button.DIMM3, "Dimm")

    def draw_radio(self):
        # RADIO
        self.draw_dual_encoder(
            100,
            250,
            Button.COMM_ENCODER_OUTER_LEFT,
            Button.COMM_ENCODER_OUTER_RIGHT,
            Button.COMM_ENCODER_INNER_LEFT,
            Button.COMM_ENCODER_INNER_RIGHT,
            Button.COMM_ENCODER_PUSH,
            "COMM",
        )

        self.draw_button(175, 250, Button.COMM_SWAP, "SWAP")
        self.draw_button(175, 290, Button.COMM_MODE, "MODE")
        self.draw_button(490, 250, Button.NAV_SWAP, "SWAP")
        self.draw_button(490, 290, Button.NAV_MODE, "MODE")

        self.draw_dual_encoder(
            550,
            250,
            Button.NAV_ENCODER_OUTER_LEFT,
            Button.NAV_ENCODER_OUTER_RIGHT,
            Button.NAV_ENCODER_INNER_LEFT,
            Button.NAV_ENCODER_INNER_RIGHT,
            Button.NAV_ENCODER_PUSH,
            "NAV",
        )
        
    def draw_audio_mix(self):
        # Audio Mix
        color = (0, 0, 255) if self.led_status[Button.OUTER_LED.value] else (180, 180, 180)
        rect = pygame.Rect(50, 350, 20, 20)
        pygame.draw.rect(self.screen, color, rect)
        self.buttons[Button.OUTER_LED.value] = rect

        color = (255, 0xBF, 0) if self.led_status[Button.MIDDLE_LED.value] else (180, 180, 180)
        rect = pygame.Rect(50, 375, 20, 20)
        pygame.draw.rect(self.screen, color, rect)
        self.buttons[Button.MIDDLE_LED.value] = rect

        color = (255, 255, 255) if self.led_status[Button.INNER_LED.value] else (180, 180, 180)
        rect = pygame.Rect(50, 400, 20, 20)
        pygame.draw.rect(self.screen, color, rect)
        self.buttons[Button.INNER_LED.value] = rect

        self.draw_button_and_led(100, 350, Button.MKR_MUTE, "MKR_MUTE")
        self.draw_button_and_led(175, 350, Button.COMM1, "COMM1")
        self.draw_button_and_led(250, 350, Button.COMM2, "COMM2")
        self.draw_button_and_led(325, 350, Button.COMM3, "COMM3")
        self.draw_button_and_led(400, 350, Button.NAV1, "NAV1")
        self.draw_button_and_led(475, 350, Button.NAV2, "NAV2")

        self.draw_button_and_led(100, 390, Button.SENS, "HI SENS")
        self.draw_button_and_led(175, 390, Button.MIC1, "MIC1")
        self.draw_button_and_led(250, 390, Button.MIC2, "MIC2")
        self.draw_button_and_led(325, 390, Button.MIC3, "MIC3")
        self.draw_button_and_led(400, 390, Button.DME, "DME")
        self.draw_button_and_led(475, 390, Button.ADF, "ADF")

        self.draw_dual_encoder(
            550,
            350,
            Button.MIX_ENCODER_OUTER_LEFT,
            Button.MIX_ENCODER_OUTER_RIGHT,
            Button.MIX_ENCODER_INNER_LEFT,
            Button.MIX_ENCODER_INNER_RIGHT,
            Button.MIX_ENCODER_PUSH,
            "MAN/SQ",
        )
        
    def draw_ap(self): 
        # AP
        self.draw_button_and_led(100, 450, Button.HDG_BUG, "HDG")
        self.draw_button_and_led(175, 450, Button.APPR, "APPR")
        self.draw_button_and_led(175, 490, Button.BC, "BC")
        self.draw_button_and_led(250, 450, Button.NAV, "NAV")

        self.draw_single_encoder(
            100,
            490,
            Button.HDG_BUG_LEFT,
            Button.HDG_BUG_RIGHT,
            Button.HDG_BUG_PUSH,
            "HDG_BUG",
        )

        self.draw_single_encoder(
            250,
            490,
            Button.CRS1_BUG_LEFT,
            Button.CRS1_BUG_RIGHT,
            Button.CRS1_BUG_PUSH,
            "CRS1_BUG",
        )

        self.draw_button_and_led(350, 450, Button.AP, "AP")
        self.draw_button_and_led(350, 490, Button.BANK, "BANK")
        self.draw_button_and_led(425, 450, Button.FD, "FD")
        self.draw_button_and_led(425, 490, Button.AUTO_THROTTLE, "AUTO_T")

        self.draw_button_and_led(525, 450, Button.YAW_DAMPER, "YD")
        self.draw_dual_encoder(
            525,
            490,
            Button.BARO_DEC,
            Button.BARO_INC,
            Button.CRS2_BUG_LEFT,
            Button.CRS2_BUG_RIGHT,
            Button.CRS2_BUG_PUSH,
            "CRS2_BUG",
        )

        self.draw_dual_encoder(
            100,
            580,
            Button.ALT_OUTER_LEFT,
            Button.ALT_OUTER_RIGHT,
            Button.ALT_INNER_LEFT,
            Button.ALT_INNER_RIGHT,
            Button.ALT_BUG_PUSH,
            "ALT",
        )

        self.draw_button_and_led(175, 605, Button.ALT, "ALT")

        self.draw_button_and_led(275, 580, Button.VS, "VS")
        self.draw_button_and_led(275, 620, Button.VNV, "VNV")

        self.draw_single_encoder(
            350, 580, Button.VS_BUG_LEFT, Button.VS_BUG_RIGHT, Button.VS_BUG_PUSH, "VS/FLC"
        )

        self.draw_button_and_led(425, 605, Button.FLC, "FLC")

        self.draw_single_encoder(
            525,
            580,
            Button.SPEED_BUG_LEFT,
            Button.SPEED_BUG_RIGHT,
            Button.SPEED_BUG_PUSH,
            "SPEED",
        )
        self.draw_button_and_led(600, 605, Button.SPEED, "SPEED")
