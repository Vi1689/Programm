import pygame
import random
import sys
import math  # Добавил импорт math
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
GOLD = (255, 215, 0)

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
        
        # Создаем кнопки для выбора количества игроков (2-8) в две колонки
        button_width = 180
        button_height = 50
        start_x = SCREEN_WIDTH // 2 - button_width - 10
        start_y = 250
        
        # Первая колонка: 2, 3, 4, 5 игроков
        for i in range(2, 6):
            y_pos = start_y + (i - 2) * (button_height + 15)
            button = Button(start_x, y_pos, button_width, button_height, f"{i} игроков")
            self.buttons.append((i, button))
        
        # Вторая колонка: 6, 7, 8 игроков
        start_x2 = SCREEN_WIDTH // 2 + 10
        for i in range(6, 9):
            y_pos = start_y + (i - 6) * (button_height + 15)
            button = Button(start_x2, y_pos, button_width, button_height, f"{i} игроков")
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
        instruction_rect = instruction_text.get_rect(center=(SCREEN_WIDTH // 2, 200))
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
        self.show_on_hover = False
        self.hovered = False
        
        # Генерируем уникальный шум для каждой карты
        self.noise_pattern = self.generate_noise_pattern()
    
    def generate_noise_pattern(self):
        """Генерирует уникальный случайный шум для карты"""
        pattern = []
        for i in range(8):  # 8 строк шума (меньше, чтобы влезало)
            line = ''.join(random.choice(['#', '*', '+', '.', '~', '-', '=']) for _ in range(6))  # Меньше символов
            pattern.append(line)
        return pattern
    
    def draw_noise(self, screen, x, y):
        """Рисует шум вместо карты"""
        # Рисуем серый фон с закругленными углами
        pygame.draw.rect(screen, GRAY, (x, y, CARD_WIDTH, CARD_HEIGHT), 0, 10)
        pygame.draw.rect(screen, DARK_GRAY, (x, y, CARD_WIDTH, CARD_HEIGHT), 2, 10)
        
        # Рисуем случайный шум (в пределах карты)
        noise_font = pygame.font.SysFont('courier', 12)
        for i, line in enumerate(self.noise_pattern):
            text = noise_font.render(line, True, BLACK)
            # Центрируем текст внутри карты с отступами
            text_x = x + (CARD_WIDTH - text.get_width()) // 2
            text_y = y + 20 + i * 15
            screen.blit(text, (text_x, text_y))
    
    def draw(self, screen, x, y):
        self.rect.topleft = (x, y)
        
        # Проверяем наведение мыши
        mouse_pos = pygame.mouse.get_pos()
        self.hovered = self.rect.collidepoint(mouse_pos)
        
        # Если карта должна показываться при наведении И мышь над картой
        if self.show_on_hover and self.hovered:
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
            
        elif self.face_up:
            # Рисуем открытую карту (для карт на столе и в шоудауне)
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
            # Рисуем шум вместо стандартной рубашки
            self.draw_noise(screen, x, y)

class Player:
    def __init__(self, name, x, y, is_human=False):
        self.name = name
        self.x = x
        self.y = y
        self.cards = []
        self.is_human = is_human
        self.rect = pygame.Rect(x - 40, y - 25, 180, 140)
        self.is_winner = False
    
    def add_card(self, card):
        if len(self.cards) < 2:
            self.cards.append(card)
            # Для человеческого игрока включаем показ при наведении
            if self.is_human:
                card.show_on_hover = True
                card.face_up = False  # Начинаем с закрытыми картами
    
    def draw(self, screen):
        # Рисуем область игрока (подсвечиваем если победитель)
        if self.is_winner:
            pygame.draw.rect(screen, GOLD, self.rect, 0, 10)
            pygame.draw.rect(screen, WHITE, self.rect, 3, 10)  # Более толстая рамка для победителя
        elif self.is_human:
            pygame.draw.rect(screen, (0, 100, 0), self.rect, 0, 10)
            pygame.draw.rect(screen, WHITE, self.rect, 2, 10)
        else:
            pygame.draw.rect(screen, DARK_GRAY, self.rect, 0, 10)
            pygame.draw.rect(screen, WHITE, self.rect, 2, 10)
        
        # Отображаем имя (уменьшаем шрифт)
        font = pygame.font.SysFont('arial', 14)
        name_color = BLACK if self.is_winner else WHITE
        name_text = font.render(self.name, True, name_color)
        screen.blit(name_text, (self.x - 35, self.y - 20))
        
        # Рисуем карты
        for i, card in enumerate(self.cards):
            card_x = self.x + (i * PLAYER_CARD_OFFSET)
            card.draw(screen, card_x, self.y)

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
        self.winner = None
        
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
        """Рассчитывает позиции игроков вокруг стола с учетом границ экрана"""
        center_x, center_y = SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2
        table_radius = 180  # Радиус стола
        
        # Определяем безопасную зону вокруг стола
        safe_zone_padding = 100  # Отступ от края стола
        
        positions = []
        for i in range(num_players):
            # Правильно рассчитываем угол для равномерного распределения
            angle = 2 * math.pi * i / num_players - math.pi / 2  # Начинаем сверху
            
            # Радиус для игроков (стол + отступ + место для карт)
            player_radius = table_radius + safe_zone_padding + 80
            
            # Вычисляем позицию
            x = center_x + player_radius * math.cos(angle)
            y = center_y + player_radius * math.sin(angle)
            
            # Корректируем позиции для конкретных случаев
            if num_players == 2:
                # Для 2 игроков - сверху и снизу
                if i == 0:  # Верхний игрок
                    y = center_y - player_radius
                else:  # Нижний игрок (Вы)
                    y = center_y + player_radius
                    
            elif num_players == 3:
                # Для 3 игроков - сверху, справа-снизу, слева-снизу
                if i == 0:  # Верхний
                    y = center_y - player_radius
                elif i == 1:  # Правый-нижний
                    x = center_x + player_radius * 0.7
                    y = center_y + player_radius * 0.7
                else:  # Левый-нижний
                    x = center_x - player_radius * 0.7
                    y = center_y + player_radius * 0.7
                    
            elif num_players == 4:
                # Для 4 игроков - сверху, справа, снизу, слева
                if i == 0:  # Верхний
                    y = center_y - player_radius
                elif i == 1:  # Правый
                    x = center_x + player_radius
                elif i == 2:  # Нижний (Вы)
                    y = center_y + player_radius
                else:  # Левый
                    x = center_x - player_radius
                    
            elif num_players == 5:
                # Для 5 игроков
                angle_offset = math.pi / 5  # Смещаем чтобы нижний игрок был точно снизу
                angle = 2 * math.pi * i / num_players - math.pi / 2 + angle_offset
                x = center_x + player_radius * math.cos(angle)
                y = center_y + player_radius * math.sin(angle)
                
            elif num_players == 6:
                # Для 6 игроков
                if i == 0:  # Верхний-левый
                    x = center_x - player_radius * 0.7
                    y = center_y - player_radius * 0.7
                elif i == 1:  # Верхний
                    y = center_y - player_radius
                elif i == 2:  # Верхний-правый
                    x = center_x + player_radius * 0.7
                    y = center_y - player_radius * 0.7
                elif i == 3:  # Нижний-правый
                    x = center_x + player_radius * 0.7
                    y = center_y + player_radius * 0.7
                elif i == 4:  # Нижний (Вы)
                    y = center_y + player_radius
                else:  # Нижний-левый
                    x = center_x - player_radius * 0.7
                    y = center_y + player_radius * 0.7
                    
            elif num_players >= 7:
                # Для 7-8 игроков используем равномерное распределение
                angle = 2 * math.pi * i / num_players - math.pi / 2
                x = center_x + player_radius * math.cos(angle)
                y = center_y + player_radius * math.sin(angle)
            
            # Гарантируем что игроки не выйдут за границы экрана
            margin = 60
            x = max(margin, min(SCREEN_WIDTH - margin, x))
            y = max(margin + 40, min(SCREEN_HEIGHT - margin - 60, y))
            
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
    
    def determine_winner(self):
        """Простая логика определения победителя (для демонстрации)"""
        # В реальной игре здесь была бы сложная логика определения комбинаций
        # Для демонстрации просто выбираем случайного игрока
        if self.game_state == "SHOWDOWN" and not self.winner:
            # Открываем все карты
            for player in self.players:
                for card in player.cards:
                    card.face_up = True
                    card.show_on_hover = False
            
            # Выбираем случайного победителя
            self.winner = random.choice(self.players)
            self.winner.is_winner = True
            
            # Даем всем игрокам случайные комбинации для реалистичности
            combinations = [
                "Старшая карта", "Пара", "Две пары", "Сет", 
                "Стрит", "Флеш", "Фулл-хаус", "Каре", "Стрит-флеш"
            ]
            self.winner_combination = random.choice(combinations)
    
    def draw_table(self):
        # Рисуем фон стола
        self.screen.fill(GREEN)
        
        # Рисуем центральный круг стола
        table_radius = 180
        pygame.draw.circle(self.screen, (0, 100, 0), 
                         (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2), table_radius)
        pygame.draw.circle(self.screen, (0, 150, 0), 
                         (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2), table_radius, 5)
        
        # Рисуем карты на столе
        table_x = SCREEN_WIDTH // 2 - (len(self.table_cards) * (CARD_WIDTH + 10)) // 2
        table_y = SCREEN_HEIGHT // 2 - CARD_HEIGHT // 2
        for i, card in enumerate(self.table_cards):
            card.draw(self.screen, table_x + i * (CARD_WIDTH + 10), table_y)
        
        # Рисуем игроков
        for player in self.players:
            player.draw(self.screen)
        
        # Отображаем состояние игры
        state_text = self.font.render(f"Фаза: {self.game_state} | Игроков: {self.num_players}", True, WHITE)
        self.screen.blit(state_text, (20, 20))
        
        # Отображаем победителя
        if self.winner:
            winner_font = pygame.font.SysFont('arial', 32)
            winner_text = winner_font.render(f"ПОБЕДИТЕЛЬ: {self.winner.name}!", True, GOLD)
            combination_text = self.font.render(f"Комбинация: {self.winner_combination}", True, WHITE)
            
            winner_rect = winner_text.get_rect(center=(SCREEN_WIDTH // 2, 60))
            combination_rect = combination_text.get_rect(center=(SCREEN_WIDTH // 2, 100))
            
            self.screen.blit(winner_text, winner_rect)
            self.screen.blit(combination_text, combination_rect)
        
        # Инструкция
        instruction_font = pygame.font.SysFont('arial', 18)
        instructions = [
            "ПРОБЕЛ - следующая фаза игры",
            "R - перезапуск игры", 
            "ESC - выбор количества игроков",
            "Наведите мышь на свои карты чтобы увидеть их"
        ]
        
        for i, instruction in enumerate(instructions):
            text = instruction_font.render(instruction, True, WHITE)
            self.screen.blit(text, (20, SCREEN_HEIGHT - 80 - i * 25))
    
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
            self.determine_winner()
    
    def reset_game(self):
        # Перезапускаем игру
        self.deck = self.create_deck()
        self.table_cards = []
        self.game_state = "DEALING"
        self.winner = None
        for player in self.players:
            player.cards = []
            player.is_winner = False
    
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