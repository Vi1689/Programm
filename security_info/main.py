import pygame
import random
import sys
from enum import Enum

# Инициализация Pygame
pygame.init()

# Константы
SCREEN_WIDTH = 1200
SCREEN_HEIGHT = 800
CARD_WIDTH = 80
CARD_HEIGHT = 120
PLAYER_CARD_OFFSET = 30

# Цвета
GREEN = (0, 128, 0)
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
BLUE = (0, 0, 255)
GRAY = (128, 128, 128)
DARK_GRAY = (64, 64, 64)
LIGHT_BLUE = (100, 100, 255)
DARK_BLUE = (0, 0, 150)

class GameState(Enum):
    PLAYER_SELECT = "player_select"
    PLAYING = "playing"

class Button:
    def __init__(self, x, y, width, height, text, color=LIGHT_BLUE, hover_color=DARK_BLUE):
        self.rect = pygame.Rect(x, y, width, height)
        self.text = text
        self.color = color
        self.hover_color = hover_color
        self.is_hovered = False
        self.font = pygame.font.SysFont('arial', 24)
    
    def draw(self, screen):
        color = self.hover_color if self.is_hovered else self.color
        pygame.draw.rect(screen, color, self.rect, 0, 10)
        pygame.draw.rect(screen, WHITE, self.rect, 2, 10)
        
        text_surface = self.font.render(self.text, True, WHITE)
        text_rect = text_surface.get_rect(center=self.rect.center)
        screen.blit(text_surface, text_rect)
    
    def check_hover(self, pos):
        self.is_hovered = self.rect.collidepoint(pos)
        return self.is_hovered
    
    def is_clicked(self, pos, event):
        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            return self.rect.collidepoint(pos)
        return False

class PlayerSelectionScreen:
    def __init__(self, screen):
        self.screen = screen
        self.buttons = []
        self.title_font = pygame.font.SysFont('arial', 48)
        self.instruction_font = pygame.font.SysFont('arial', 24)
        
        # Создаем кнопки для выбора количества игроков (2-8)
        button_width = 200
        button_height = 60
        start_x = SCREEN_WIDTH // 2 - button_width // 2
        start_y = 300
        
        for i in range(2, 9):  # От 2 до 8 игроков
            y_pos = start_y + (i - 2) * (button_height + 20)
            button = Button(start_x, y_pos, button_width, button_height, f"{i} игроков")
            self.buttons.append((i, button))
    
    def draw(self):
        # Фон
        self.screen.fill((0, 50, 0))
        
        # Заголовок
        title_text = self.title_font.render("МЕНТАЛЬНЫЙ ПОКЕР", True, WHITE)
        title_rect = title_text.get_rect(center=(SCREEN_WIDTH // 2, 150))
        self.screen.blit(title_text, title_rect)
        
        # Инструкция
        instruction_text = self.instruction_font.render("Выберите количество игроков:", True, WHITE)
        instruction_rect = instruction_text.get_rect(center=(SCREEN_WIDTH // 2, 230))
        self.screen.blit(instruction_text, instruction_rect)
        
        # Рисуем кнопки
        for num_players, button in self.buttons:
            button.draw(self.screen)
    
    def handle_events(self):
        mouse_pos = pygame.mouse.get_pos()
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                return None
            
            # Проверяем наведение на кнопки
            for num_players, button in self.buttons:
                button.check_hover(mouse_pos)
                
                # Проверяем клик
                if button.is_clicked(mouse_pos, event):
                    return num_players
        
        return "continue"

class Card:
    def __init__(self, suit, value):
        self.suit = suit
        self.value = value
        self.face_up = False
        self.rect = pygame.Rect(0, 0, CARD_WIDTH, CARD_HEIGHT)
    
    def draw(self, screen, x, y):
        self.rect.topleft = (x, y)
        
        if self.face_up:
            # Рисуем открытую карту
            pygame.draw.rect(screen, WHITE, self.rect, 0, 10)
            pygame.draw.rect(screen, BLACK, self.rect, 2, 10)
            
            # Цвет масти
            color = RED if self.suit in ["♥", "♦"] else BLACK
            
            # Создаем шрифт
            font = pygame.font.SysFont('arial', 20)
            
            # Отображаем значение и масть
            text = font.render(f"{self.value}{self.suit}", True, color)
            screen.blit(text, (x + 10, y + 10))
        else:
            # Рисуем рубашку карты
            pygame.draw.rect(screen, BLUE, self.rect, 0, 10)
            pygame.draw.rect(screen, WHITE, self.rect, 2, 10)
            
            # Простой узор на рубашке
            pattern_color = (30, 30, 150)
            pygame.draw.rect(screen, pattern_color, 
                           (x + 10, y + 10, CARD_WIDTH - 20, CARD_HEIGHT - 20), 2, 5)

class Player:
    def __init__(self, name, x, y, is_human=False):
        self.name = name
        self.x = x
        self.y = y
        self.cards = []
        self.is_human = is_human
        self.rect = pygame.Rect(x - 50, y - 30, 200, 160)
    
    def add_card(self, card):
        if len(self.cards) < 2:
            self.cards.append(card)
            # Карты человека сразу открыты, остальных - закрыты
            if self.is_human:
                card.face_up = True
    
    def draw(self, screen):
        # Рисуем область игрока
        if self.is_human:
            pygame.draw.rect(screen, (0, 100, 0), self.rect, 0, 15)
        else:
            pygame.draw.rect(screen, DARK_GRAY, self.rect, 0, 15)
        
        pygame.draw.rect(screen, WHITE, self.rect, 2, 15)
        
        # Отображаем имя
        font = pygame.font.SysFont('arial', 16)
        name_text = font.render(self.name, True, WHITE)
        screen.blit(name_text, (self.x - 40, self.y - 25))
        
        # Рисуем карты
        for i, card in enumerate(self.cards):
            card_x = self.x + (i * PLAYER_CARD_OFFSET)
            card.draw(screen, card_x, self.y)
        
        # Для компьютерных игроков рисуем темный силуэт поверх карт
        if not self.is_human and self.cards:
            overlay = pygame.Surface((CARD_WIDTH + PLAYER_CARD_OFFSET, CARD_HEIGHT), pygame.SRCALPHA)
            overlay.fill((0, 0, 0, 180))  # Полупрозрачный черный
            screen.blit(overlay, (self.x, self.y))

class PokerTable:
    def __init__(self, num_players):
        self.screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
        pygame.display.set_caption(f"Ментальный Покер - {num_players} игроков")
        self.clock = pygame.time.Clock()
        self.font = pygame.font.SysFont('arial', 24)
        self.num_players = num_players
        
        # Создаем колоду
        self.deck = self.create_deck()
        
        # Создаем игроков
        self.players = self.create_players(num_players)
        
        # Карты на столе
        self.table_cards = []
        
        # Состояние игры
        self.game_state = "DEALING"  # DEALING, FLOP, TURN, RIVER, SHOWDOWN
        
    def create_players(self, num_players):
        players = []
        
        # Позиции для игроков в зависимости от их количества
        positions = self.calculate_player_positions(num_players)
        
        for i in range(num_players):
            x, y = positions[i]
            is_human = (i == 0)  # Первый игрок - человек
            name = "Вы" if is_human else f"Игрок {i+1}"
            players.append(Player(name, x, y, is_human))
        
        return players
    
    def calculate_player_positions(self, num_players):
        """Рассчитывает позиции игроков вокруг стола в зависимости от их количества"""
        center_x, center_y = SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2
        radius = 300
        
        positions = []
        for i in range(num_players):
            angle = 2 * 3.14159 * i / num_players  # Равномерное распределение
            x = center_x + radius * pygame.math.Vector2(pygame.math.Vector2(1, 0).rotate(360 * i / num_players)).x
            y = center_y + radius * pygame.math.Vector2(pygame.math.Vector2(1, 0).rotate(360 * i / num_players)).y
            
            # Корректируем позиции для лучшего отображения
            if x < center_x - 200:  # Левая сторона
                x -= 50
            elif x > center_x + 200:  # Правая сторона
                x += 50
                
            if y < center_y - 150:  # Верхняя сторона
                y -= 30
            elif y > center_y + 150:  # Нижняя сторона
                y += 30
                
            positions.append((int(x), int(y)))
        
        return positions
    
    def create_deck(self):
        suits = ["♥", "♦", "♣", "♠"]
        values = ["2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"]
        deck = [Card(suit, value) for suit in suits for value in values]
        random.shuffle(deck)
        return deck
    
    def deal_cards(self):
        # Раздаем по 2 карты каждому игроку
        for _ in range(2):
            for player in self.players:
                if self.deck:
                    player.add_card(self.deck.pop())
    
    def deal_table_cards(self, count):
        # Выкладываем карты на стол
        for _ in range(count):
            if self.deck:
                card = self.deck.pop()
                card.face_up = True  # Карты на столе всегда открыты
                self.table_cards.append(card)
    
    def draw_table(self):
        # Рисуем фон стола
        self.screen.fill(GREEN)
        
        # Рисуем центральный круг стола
        pygame.draw.circle(self.screen, (0, 100, 0), 
                         (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2), 200)
        pygame.draw.circle(self.screen, (0, 150, 0), 
                         (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2), 200, 5)
        
        # Рисуем карты на столе
        table_x = SCREEN_WIDTH // 2 - (len(self.table_cards) * (CARD_WIDTH + 10)) // 2
        for i, card in enumerate(self.table_cards):
            card.draw(self.screen, table_x + i * (CARD_WIDTH + 10), SCREEN_HEIGHT // 2 - CARD_HEIGHT // 2)
        
        # Рисуем игроков
        for player in self.players:
            player.draw(self.screen)
        
        # Отображаем состояние игры
        state_text = self.font.render(f"Фаза: {self.game_state} | Игроков: {self.num_players}", True, WHITE)
        self.screen.blit(state_text, (20, 20))
        
        # Инструкция
        instruction_font = pygame.font.SysFont('arial', 18)
        instructions = [
            "ПРОБЕЛ - следующая фаза игры",
            "R - перезапуск игры",
            "ESC - выбор количества игроков"
        ]
        
        for i, instruction in enumerate(instructions):
            text = instruction_font.render(instruction, True, WHITE)
            self.screen.blit(text, (20, SCREEN_HEIGHT - 40 - i * 25))
    
    def handle_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                return False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    self.next_phase()
                elif event.key == pygame.K_r:
                    self.reset_game()
                elif event.key == pygame.K_ESCAPE:
                    return "player_select"  # Возврат к выбору игроков
        
        return True
    
    def next_phase(self):
        if self.game_state == "DEALING":
            self.deal_cards()
            self.game_state = "FLOP"
        elif self.game_state == "FLOP":
            self.deal_table_cards(3)
            self.game_state = "TURN"
        elif self.game_state == "TURN":
            self.deal_table_cards(1)
            self.game_state = "RIVER"
        elif self.game_state == "RIVER":
            self.deal_table_cards(1)
            self.game_state = "SHOWDOWN"
        elif self.game_state == "SHOWDOWN":
            # В showdown все карты открываются
            for player in self.players:
                for card in player.cards:
                    card.face_up = True
    
    def reset_game(self):
        # Перезапускаем игру
        self.deck = self.create_deck()
        self.table_cards = []
        self.game_state = "DEALING"
        for player in self.players:
            player.cards = []
            # При сбросе снова скрываем карты компьютеров
            if not player.is_human:
                for card in player.cards:
                    card.face_up = False
    
    def run(self):
        running = True
        while running:
            running = self.handle_events()
            
            if running == "player_select":
                return "player_select"
            
            self.draw_table()
            pygame.display.flip()
            self.clock.tick(60)
        
        return "quit"

class Game:
    def __init__(self):
        self.screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
        self.clock = pygame.time.Clock()
        self.state = GameState.PLAYER_SELECT
        self.player_selection = PlayerSelectionScreen(self.screen)
        self.poker_table = None
        self.num_players = 6  # Значение по умолчанию
    
    def run(self):
        running = True
        while running:
            if self.state == GameState.PLAYER_SELECT:
                result = self.player_selection.handle_events()
                
                if result is None:
                    running = False
                elif isinstance(result, int):
                    self.num_players = result
                    self.state = GameState.PLAYING
                    self.poker_table = PokerTable(self.num_players)
                
                self.player_selection.draw()
                
            elif self.state == GameState.PLAYING:
                result = self.poker_table.run()
                
                if result == "player_select":
                    self.state = GameState.PLAYER_SELECT
                    self.player_selection = PlayerSelectionScreen(self.screen)
                elif result == "quit":
                    running = False
            
            pygame.display.flip()
            self.clock.tick(60)
        
        pygame.quit()
        sys.exit()

# Запуск игры
if __name__ == "__main__":
    game = Game()
    game.run()