import pygame
from pygame.locals import *

def rgb565_to_rgb888(color):
    r = int(color[0] * 255/31)
    g = int(color[1] * 255/63)
    b = int(color[2] * 255/31)
    return (r, g, b)

WHITE = rgb565_to_rgb888((31, 63, 31))
FONT = "../../experiements/fonts/B612Mono-Regular.ttf"
SMALL_FONT_SIZE = 14
MEDIUM_FONT_SIZE = 20

pygame.init()

def array_to_chunk_array(array, chunk_size):
    return [array[i:i + chunk_size] for i in range(0, len(array), chunk_size)]

def surface_to_bitmap(surface):
    THRESHOLD = 127
    bitmap = []
    for j in range(surface.get_height()):
        for i in range(surface.get_width()):
            # bitmap.append(surface.get_at((i, j))[3])
            bitmap.append(1 if surface.get_at((i, j))[3] > THRESHOLD else 0)
    return array_to_chunk_array(bitmap, surface.get_width())

def create_bitmap_table(font, alphabet, color):
    table = {}
    for char in alphabet:
        table[char] = surface_to_bitmap(font.render(char, 1, color))
    return table

def generate_c_code():
    alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.°⇔"
    font = pygame.font.Font(FONT, SMALL_FONT_SIZE)
    table = create_bitmap_table(font, alphabet, WHITE)
    for i in table:
        print(f"CHAR_SMALL_{i} = {table[i]};")
    font = pygame.font.Font(FONT, MEDIUM_FONT_SIZE)
    table = create_bitmap_table(font, alphabet, WHITE)
    for i in table:
        print(f"CHAR_MEDIUM_{i} = {table[i]};")

generate_c_code()