import pygame
import sys
import numpy as np

# Initialize Pygame
pygame.init()

# Constants
width, height = 600, 600
red = (255, 0, 0)
speed = 5

# Set up the screen
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Brownian Motion")

# Set up the red dot
dot_radius = 10
dot_x, dot_y = width // 2, height // 2
dot_velocity = np.array([speed, 0], dtype=float)
dot_color = red

# Main game loop
clock = pygame.time.Clock()

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    # Move the red dot
    dot_x += dot_velocity[0]
    dot_y += dot_velocity[1]

    # Check for collisions with walls
    if dot_x - dot_radius < 0 or dot_x + dot_radius > width:
        dot_velocity[0] *= -1
        dot_velocity[1] = np.random.uniform(-speed, speed)
    if dot_y - dot_radius < 0 or dot_y + dot_radius > height:
        dot_velocity[1] *= -1
        dot_velocity[0] = np.random.uniform(-speed, speed)

    # Clear the screen
    screen.fill((255, 255, 255))

    # Draw the red dot
    pygame.draw.circle(screen, dot_color, (int(dot_x), int(dot_y)), dot_radius)

    # Update the display
    pygame.display.flip()

    # Control the frame rate
    clock.tick(60)
