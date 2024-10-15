import pygame
from pygame.locals import *

# Define some colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
LIGHT_GREY = (220, 220, 220)
MAGENTA = (255, 0, 255)
CYAN = (0, 255, 255)
GREEN = (0, 255, 0)
FONT = "fonts/B612Mono-Regular.ttf"
SMALL_FONT_SIZE = 14
MEDIUM_FONT_SIZE = 20

LEFT_PADDING = 4
RIGHT_PADDING = 156

class CommNavData:
    def __init__(self, name, activ_freq, stby_freq, id, bearing, distance, selected):
        self.name = name
        self.activ_freq = activ_freq
        self.stby_freq = stby_freq
        self.id = id
        self.bearing = bearing
        self.distance = distance
        self.selected = selected


comms = [
    CommNavData("NAV1", "114,70", "115.65", "RBT", 150, 21, True),
    CommNavData("NAV2", "115.65", "123.45", "EPR", 132, 15, False),
    CommNavData("COM1", "120.750", "119.700", "LFPN TWR", 13, 3, False),
    CommNavData("COM2", "127.480", "123.450", "LFPN ATIS", 52, 2, True),
]

def display_block_nav(data: CommNavData):

    # Create a 160x95 px buffer
    rectangle = pygame.Surface((160, 85))


    # Add a text to the screen
    font = pygame.font.Font(FONT, SMALL_FONT_SIZE)
    text = font.render(data.name, 1, MAGENTA)
    rectangle.blit(text, (LEFT_PADDING, 10))

    font = pygame.font.Font(FONT, MEDIUM_FONT_SIZE)
    text = font.render(f"{data.activ_freq}", 1, GREEN)
    rectangle.blit(text, (RIGHT_PADDING-text.get_width(), 5))
    text = font.render(f"⇔ {data.stby_freq}", 1, WHITE)
    rectangle.blit(text, (RIGHT_PADDING-text.get_width(), 32))
    if data.selected:
        pygame.draw.rect(rectangle, GREEN , (72, 28, 84, 30), 1, 0)

    font = pygame.font.Font(FONT, SMALL_FONT_SIZE)
    text = font.render(data.id, 1, WHITE)
    rectangle.blit(text, (RIGHT_PADDING-text.get_width(), 60))

    font = pygame.font.Font(FONT, SMALL_FONT_SIZE)
    text = font.render(f"{data.bearing}° {data.distance}NM", 1, MAGENTA)
    rectangle.blit(text, (LEFT_PADDING, 60))

    # Add rounded squre to the screen
    pygame.draw.rect(rectangle, GREEN if data.selected else LIGHT_GREY, (1, 1, 158, 83), 1, 5)

    return rectangle

def display_block_com(data: CommNavData):

    # Create a 160x95 px buffer
    rectangle = pygame.Surface((160, 85))


    # Add a text to the screen
    font = pygame.font.Font(FONT, SMALL_FONT_SIZE)
    text = font.render(data.name, 1, MAGENTA)
    rectangle.blit(text, (RIGHT_PADDING-text.get_width(), 10))

    font = pygame.font.Font(FONT, MEDIUM_FONT_SIZE)
    text = font.render(f"{data.activ_freq}", 1, WHITE)
    rectangle.blit(text, (LEFT_PADDING, 5))
    text = font.render(f"{data.stby_freq} ⇔", 1, WHITE)
    rectangle.blit(text, (LEFT_PADDING, 32))
    if data.selected:
        pygame.draw.rect(rectangle, GREEN , (3, 28, 95, 30), 1, 0)

    font = pygame.font.Font(FONT, SMALL_FONT_SIZE)
    text = font.render(data.id, 1, WHITE)
    rectangle.blit(text, (LEFT_PADDING, 60))

    font = pygame.font.Font(FONT, SMALL_FONT_SIZE)
    text = font.render(f"{data.bearing}° {data.distance}NM", 1, MAGENTA)
    rectangle.blit(text, (RIGHT_PADDING-text.get_width(), 60))

    # Add rounded squre to the screen
    pygame.draw.rect(rectangle, GREEN if data.selected else LIGHT_GREY, (1, 1, 158, 83), 1, 5)

    return rectangle

pygame.init()

# Set up the screen
screen = pygame.display.set_mode((320, 170))

# Fill the screen with black
screen.fill(BLACK)
rectangle = display_block_nav(comms[0])
screen.blit(rectangle, (0, 0))
rectangle = display_block_nav(comms[1])
screen.blit(rectangle, (0, 85))
rectangle = display_block_com(comms[2])
screen.blit(rectangle, (160, 0))
rectangle = display_block_com(comms[3])
screen.blit(rectangle, (160, 85))



continuer = True
while continuer:
    pygame.display.flip()
    for event in pygame.event.get():
        if event.type == QUIT:
            continuer = False

pygame.quit()