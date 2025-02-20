# This is a "Snake Water Gun" in which it {PLAYER VS MACHINE}
# The Game uses Tkinter as the deployed system and acting as a LIVE SERVER

# github projects
import pygame

# importing it with the help of python
import random

# python is my favourite language

# Initialize pygame
pygame.init()

# Set up display
WIDTH, HEIGHT = 500, 400
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Snake Water Gun Game")

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GREEN = (0, 200, 0)
RED = (200, 0, 0)
BLUE = (0, 0, 200)
GRAY = (150, 150, 150)
# done it with the help of python

# Fonts
font = pygame.font.Font(None, 36)

# Game Choices
choices = {"Snake": 1, "Water": -1, "Gun": 0}
reverse_choices = {1: "Snake", -1: "Water", 0: "Gun"}
buttons = [("Snake", 50, 300, GREEN), ("Water", 200, 300, BLUE), ("Gun", 350, 300, RED)]

# Game State
user_choice = None
computer_choice = None
result = None


def determine_winner(player, computer):
    """Determine the winner based on the choices."""
    if player == computer:
        return "Game Tied!"
    elif (player - computer) in [-2, 1]:  # Win conditions
        return "You Win!"
    else:
        return "Computer Wins!"

# here are my project


running = True
while running:
    screen.fill(WHITE)

    # Display game title
    title = font.render("Snake-Water-Gun Game", True, BLACK)
    screen.blit(title, (WIDTH // 2 - title.get_width() // 2, 30))

    # Display choices
    if user_choice is not None:
        user_text = font.render(f"You: {reverse_choices[user_choice]}", True, BLACK)
        computer_text = font.render(f"Computer: {reverse_choices[computer_choice]}", True, BLACK)
        result_text = font.render(result, True, RED if "Win" in result else BLUE)
        screen.blit(user_text, (50, 100))
        screen.blit(computer_text, (50, 140))
        screen.blit(result_text, (50, 180))

    # Draw buttons
    for text, x, y, color in buttons:
        pygame.draw.rect(screen, color, (x, y, 100, 50))
        button_text = font.render(text, True, WHITE)
        screen.blit(button_text, (x + 10, y + 15))

# codinnggg
// 

    # Event Handling
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        if event.type == pygame.MOUSEBUTTONDOWN:
            mx, my = pygame.mouse.get_pos()
            for text, x, y, _ in buttons:
                if x <= mx <= x + 100 and y <= my <= y + 50:
                    user_choice = choices[text]
                    computer_choice = random.choice(list(choices.values()))
                    result = determine_winner(user_choice, computer_choice)

    pygame.display.update()

pygame.quit()
