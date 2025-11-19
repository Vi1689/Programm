# main.py
import pygame
import random
import sys
import math
from enum import Enum

# ---------------------------
# Настройки / константы
# ---------------------------
pygame.init()

SCREEN_WIDTH = 1200
SCREEN_HEIGHT = 800
CARD_WIDTH = 80
CARD_HEIGHT = 120
PLAYER_CARD_OFFSET = 36  # отступ между картами игрока
TABLE_CARD_SPACING = CARD_WIDTH + 14

GREEN = (0, 120, 0)
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (220, 50, 50)
GRAY = (140, 140, 140)
DARK_GRAY = (60, 60, 60)
LIGHT_BLUE = (100, 150, 255)
DARK_BLUE = (0, 70, 140)
GOLD = (255, 200, 0)
SHADOW = (10, 10, 10, 90)

class GameState(Enum):
    PLAYER_SELECT = 1
    PLAYING = 2

# ---------------------------
# Криптосистема ментального покера
# ---------------------------
class MentalPokerCrypto:
    def __init__(self, num_players):
        self.num_players = num_players
        self.prime = 2**127 - 1

        self.player_keys = []
        self.player_inv_keys = []
        self._gen_keys()

        self.card_base_map = {}
        self.base_to_card_index = {}
        self._prepare_card_base_values()

        self.encrypted_deck = []

    def _gen_keys(self):
        for _ in range(self.num_players):
            while True:
                k = random.randint(2, self.prime - 2)
                if math.gcd(k, self.prime - 1) == 1:
                    break
            k_inv = pow(k, -1, self.prime - 1)
            self.player_keys.append(k)
            self.player_inv_keys.append(k_inv)

    def _prepare_card_base_values(self):
        used = set()
        for card_index in range(1, 53):
            while True:
                val = random.randint(2, self.prime - 2)
                if val not in used:
                    used.add(val)
                    break
            self.card_base_map[card_index] = val
            self.base_to_card_index[val] = card_index

    def prepare_deck(self):
        deck_bases = [self.card_base_map[i] for i in range(1, 53)]
        random.shuffle(deck_bases)

        encrypted = deck_bases
        for k in self.player_keys:
            encrypted = [pow(x, k, self.prime) for x in encrypted]
            random.shuffle(encrypted)

        self.encrypted_deck = encrypted.copy()
        return self.encrypted_deck

    def remove_other_layers(self, encrypted_card, player_index):
        val = encrypted_card
        for i, inv in enumerate(self.player_inv_keys):
            if i != player_index:
                val = pow(val, inv, self.prime)
        return val

    def owner_remove_own_layer(self, partially_decrypted_card, player_index):
        return pow(partially_decrypted_card, self.player_inv_keys[player_index], self.prime)

    def fully_decrypt(self, encrypted_card):
        val = encrypted_card
        for inv in self.player_inv_keys:
            val = pow(val, inv, self.prime)
        return val

    def base_to_card(self, base_value):
        return self.base_to_card_index.get(base_value, None)

# ---------------------------
# UI: Button
# ---------------------------
class Button:
    def __init__(self, x, y, w, h, text, color=LIGHT_BLUE, hover_color=DARK_BLUE):
        self.rect = pygame.Rect(x, y, w, h)
        self.text = text
        self.color = color
        self.hover_color = hover_color
        self.font = pygame.font.SysFont('arial', 22)
        self.is_hovered = False

    def draw(self, surf):
        color = self.hover_color if self.is_hovered else self.color
        pygame.draw.rect(surf, color, self.rect, border_radius=8)
        pygame.draw.rect(surf, WHITE, self.rect, 2, border_radius=8)
        txt = self.font.render(self.text, True, WHITE)
        surf.blit(txt, txt.get_rect(center=self.rect.center))

    def update(self, mouse_pos):
        self.is_hovered = self.rect.collidepoint(mouse_pos)

    def clicked(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            return self.rect.collidepoint(event.pos)
        return False

# ---------------------------
# Card & Player
# ---------------------------
class Card:
    def __init__(self, suit=None, value=None, numeric_value=None):
        self.suit = suit
        self.value = value
        self.numeric_value = numeric_value
        self.face_up = False
        self.rect = pygame.Rect(0, 0, CARD_WIDTH, CARD_HEIGHT)
        self.noise = self._generate_noise()

    def _generate_noise(self):
        pattern = []
        for _ in range(6):
            line = ''.join(random.choice(['#', '*', '+', '.', '~', '-', '=']) for _ in range(6))
            pattern.append(line)
        return pattern

    def draw(self, surf, x, y, show_value_on_hover=False):
        self.rect.topleft = (int(x), int(y))
        mouse_pos = pygame.mouse.get_pos()
        hovered = self.rect.collidepoint(mouse_pos)

        # shadow
        shadow_rect = pygame.Rect(self.rect.left + 6, self.rect.top + 6, CARD_WIDTH, CARD_HEIGHT)
        s = pygame.Surface((CARD_WIDTH, CARD_HEIGHT), pygame.SRCALPHA)
        s.fill((0, 0, 0, 60))
        surf.blit(s, (shadow_rect.left, shadow_rect.top))

        if self.face_up or (show_value_on_hover and hovered):
            pygame.draw.rect(surf, WHITE, self.rect, border_radius=8)
            pygame.draw.rect(surf, BLACK, self.rect, 2, border_radius=8)
            color = RED if self.suit in ["♥", "♦"] else BLACK
            font = pygame.font.SysFont('arial', 20)
            txt = font.render(f"{self.value}{self.suit}", True, color)
            surf.blit(txt, (self.rect.left + 8, self.rect.top + 8))
        else:
            pygame.draw.rect(surf, GRAY, self.rect, border_radius=8)
            pygame.draw.rect(surf, DARK_GRAY, self.rect, 2, border_radius=8)
            noise_font = pygame.font.SysFont('courier', 12)
            for i, line in enumerate(self.noise):
                txt = noise_font.render(line, True, BLACK)
                surf.blit(txt, (self.rect.left + 6, self.rect.top + 14 + i * 14))

class Player:
    def __init__(self, name, x, y, is_human=False, index=0):
        self.name = name
        self.x = int(x)
        self.y = int(y)
        self.index = index
        self.is_human = is_human
        self.encrypted_cards = []
        self.cards = []
        self.is_winner = False

    def add_encrypted_card(self, enc):
        if len(self.encrypted_cards) < 2:
            self.encrypted_cards.append(enc)

    def decrypt_own_cards_if_allowed(self, crypto: MentalPokerCrypto):
        self.cards = []
        for enc in self.encrypted_cards:
            partial = crypto.remove_other_layers(enc, self.index)
            if self.is_human:
                base = crypto.owner_remove_own_layer(partial, self.index)
                card_index = crypto.base_to_card(base)
                if card_index:
                    self.cards.append(self.numeric_to_card(card_index))
                else:
                    self.cards.append(Card(None, "?", None))
            else:
                self.cards.append(Card(None, "?", None))

    def reveal_cards(self, crypto: MentalPokerCrypto):
        self.cards = []
        for enc in self.encrypted_cards:
            base = crypto.fully_decrypt(enc)
            card_index = crypto.base_to_card(base)
            if card_index:
                self.cards.append(self.numeric_to_card(card_index))
            else:
                self.cards.append(Card(None, "?", None))
        for c in self.cards:
            c.face_up = True

    @staticmethod
    def numeric_to_card(numeric_value):
        suits = ["♥", "♦", "♣", "♠"]
        values = ["2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"]
        if 1 <= numeric_value <= 52:
            suit_index = (numeric_value - 1) // 13
            value_index = (numeric_value - 1) % 13
            return Card(suits[suit_index], values[value_index], numeric_value)
        return Card(None, "?", None)

    def draw(self, surf, show_human_hover=True):
        area = pygame.Rect(self.x - 40, self.y - 20, 180, 140)
        if self.is_winner:
            pygame.draw.rect(surf, GOLD, area, border_radius=10)
            pygame.draw.rect(surf, WHITE, area, 3, border_radius=10)
        elif self.is_human:
            pygame.draw.rect(surf, (0, 90, 0), area, border_radius=10)
            pygame.draw.rect(surf, WHITE, area, 2, border_radius=10)
        else:
            pygame.draw.rect(surf, DARK_GRAY, area, border_radius=10)
            pygame.draw.rect(surf, WHITE, area, 2, border_radius=10)

        font = pygame.font.SysFont('arial', 14)
        name_col = BLACK if self.is_winner else WHITE
        name_txt = font.render(self.name, True, name_col)
        surf.blit(name_txt, (self.x - 32, self.y - 18))

        for i, card in enumerate(self.cards):
            card_x = self.x + i * PLAYER_CARD_OFFSET
            card_y = self.y
            show_on_hover = show_human_hover and self.is_human
            card.draw(surf, card_x, card_y, show_value_on_hover=show_on_hover)

# ---------------------------
# PokerTable: логика и отрисовка
# ---------------------------
class PokerTable:
    def __init__(self, num_players):
        self.screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
        pygame.display.set_caption(f"Ментальный Покер - {num_players} игроков")
        self.clock = pygame.time.Clock()
        self.font = pygame.font.SysFont('arial', 22)
        self.num_players = num_players

        self.crypto = MentalPokerCrypto(num_players)
        self.players = self.create_players(num_players)
        self.encrypted_deck = self.crypto.prepare_deck()

        self.table_cards = []
        self.encrypted_table_cards = []

        self.game_state = "DEALING"
        self.winner = None
        self.winner_combination = ""
        self.info_message = "Колода зашифрована и перемешана всеми игроками"

    def create_players(self, n):
        positions = self.calculate_player_positions(n)
        players = []
        for i in range(n):
            x, y = positions[i]
            is_human = (i == 0)
            name = "Вы" if is_human else f"Игрок {i+1}"
            players.append(Player(name, x, y, is_human, i))
        return players

    def calculate_player_positions(self, num_players):
        center_x, center_y = SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2
        table_radius = 180

        # safe distance: учитываем размер карты + запас
        card_diameter = max(CARD_WIDTH, CARD_HEIGHT)
        safe_distance = 160 + int(card_diameter / 4)

        # простой адаптивный радиус
        radius = table_radius + safe_distance + num_players * 6

        # дополнительно обеспечить отсутствие наложения карт друг на друга:
        # минимальный радиус, чтобы дуга между соседними позициями была шире, чем CARD_WIDTH + margin
        margin = 40
        try:
            angle_between = 2 * math.pi / num_players
            min_radius_for_spacing = (CARD_WIDTH + margin) / (2 * math.sin(angle_between / 2))
            radius = max(radius, int(min_radius_for_spacing) + 20)
        except Exception:
            pass

        # не превышать экран
        radius = min(radius, min(center_x, center_y) - 120)

        positions = []
        for i in range(num_players):
            angle = 2 * math.pi * i / num_players - math.pi / 2
            x = center_x + radius * math.cos(angle)
            y = center_y + radius * math.sin(angle)

            # лёгкие вертикальные смещения, чтобы верх/низ не залазили на стол
            # если игрок сверху (угол в верхней полусфере) — смещаем выше, если снизу — ниже
            if -math.pi/2 < angle < math.pi/2:
                y += 30  # нижние немного ниже
            else:
                y -= 30  # верхние немного выше

            # ограничения экрана
            x = max(80, min(SCREEN_WIDTH - 80, x))
            y = max(90, min(SCREEN_HEIGHT - 140, y))

            positions.append((int(x), int(y)))
        return positions

    def deal_cards(self):
        self.info_message = "Раздаём зашифрованные карты игрокам..."
        for _ in range(2):
            for player in self.players:
                if not self.encrypted_deck:
                    break
                enc = self.encrypted_deck.pop()
                player.add_encrypted_card(enc)

        for player in self.players:
            player.decrypt_own_cards_if_allowed(self.crypto)

        self.info_message = "Карты разданы. Только ваши карты видны вам."
        self.game_state = "FLOP"

    def deal_table_cards(self, count):
        self.info_message = f"Выкладываем {count} карт на стол..."
        for _ in range(count):
            if not self.encrypted_deck:
                break
            enc = self.encrypted_deck.pop()
            self.encrypted_table_cards.append(enc)
            base = self.crypto.fully_decrypt(enc)
            card_index = self.crypto.base_to_card(base)
            if card_index:
                card = Player.numeric_to_card(card_index)
                card.face_up = True
                self.table_cards.append(card)

    def determine_winner(self):
        if self.game_state == "SHOWDOWN" and not self.winner:
            for player in self.players:
                player.reveal_cards(self.crypto)

            self.winner = random.choice(self.players)
            self.winner.is_winner = True

            combos = [
                "Старшая карта", "Пара", "Две пары", "Сет",
                "Стрит", "Флеш", "Фулл-хаус", "Каре", "Стрит-флеш"
            ]
            self.winner_combination = random.choice(combos)
            self.info_message = f"Победитель: {self.winner.name}"

    def draw_table(self):
        # фон
        self.screen.fill(GREEN)

        # мягкий градиент круга стола (несколько концентрических кругов)
        center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)
        base_radius = 180
        for i in range(6):
            r = base_radius + i * 6
            col = (0, 100 + i*8, 0)
            pygame.draw.circle(self.screen, col, center, r)
        pygame.draw.circle(self.screen, (0, 150, 0), center, base_radius, 6)

        # карты на столе (центрируем)
        total_width = len(self.table_cards) * TABLE_CARD_SPACING - (TABLE_CARD_SPACING - CARD_WIDTH)
        start_x = SCREEN_WIDTH // 2 - total_width // 2
        table_y = SCREEN_HEIGHT // 2 - CARD_HEIGHT // 2
        for i, card in enumerate(self.table_cards):
            x = start_x + i * TABLE_CARD_SPACING
            card.draw(self.screen, x, table_y, show_value_on_hover=False)

        # игроки
        for player in self.players:
            player.draw(self.screen)

        # статус
        state_text = self.font.render(f"Фаза: {self.game_state} | Игроков: {self.num_players}", True, WHITE)
        self.screen.blit(state_text, (18, 18))

        info_font = pygame.font.SysFont('arial', 16)
        info_text = info_font.render(self.info_message, True, WHITE)
        self.screen.blit(info_text, (18, 50))

        # победитель
        if self.winner:
            win_font = pygame.font.SysFont('arial', 28)
            wtxt = win_font.render(f"ПОБЕДИТЕЛЬ: {self.winner.name}!", True, GOLD)
            comb = self.font.render(f"Комбинация: {self.winner_combination}", True, WHITE)
            self.screen.blit(wtxt, wtxt.get_rect(center=(SCREEN_WIDTH // 2, 90)))
            self.screen.blit(comb, comb.get_rect(center=(SCREEN_WIDTH // 2, 130)))

        # инструкции
        instrs = [
            "ПРОБЕЛ - перейти к следующей фазе",
            "R - перезапуск игры",
            "ESC - вернуться к выбору игроков",
            "Наведите мышь на свои карты чтоб увидеть их"
        ]
        for i, t in enumerate(instrs):
            txt = info_font.render(t, True, WHITE)
            self.screen.blit(txt, (18, SCREEN_HEIGHT - 100 + i * 20))

        # крипто-инфо
        crypto_lines = [
            "МЕНТАЛЬНЫЙ ПОКЕР:",
            "- Колода кодируется всеми игроками",
            "- Каждый видит только свои карты (пока не шоудаун)",
            "- Коммутативное шифрование (возведение в степень) обеспечивает честность"
        ]
        for i, line in enumerate(crypto_lines):
            txt = info_font.render(line, True, LIGHT_BLUE)
            self.screen.blit(txt, (SCREEN_WIDTH - 460, 18 + i * 20))

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
                    return "player_select"
        return True

    def next_phase(self):
        if self.game_state == "DEALING":
            self.deal_cards()
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
        self.crypto = MentalPokerCrypto(self.num_players)
        self.encrypted_deck = self.crypto.prepare_deck()
        self.table_cards = []
        self.encrypted_table_cards = []
        self.game_state = "DEALING"
        self.winner = None
        self.winner_combination = ""
        self.info_message = "Новая игра — колода зашифрована и перемешана"

        for p in self.players:
            p.encrypted_cards = []
            p.cards = []
            p.is_winner = False

    def run(self):
        running = True
        while running:
            rv = self.handle_events()
            if rv == "player_select":
                return "player_select"
            elif rv is False:
                return "quit"

            self.draw_table()
            pygame.display.flip()
            self.clock.tick(60)
        return "quit"

# ---------------------------
# PlayerSelectionScreen
# ---------------------------
class PlayerSelectionScreen:
    def __init__(self, screen):
        self.screen = screen
        self.title_font = pygame.font.SysFont('arial', 44)
        self.instr_font = pygame.font.SysFont('arial', 22)
        self.buttons = []
        self._create_buttons()

    def _create_buttons(self):
        button_w = 160
        button_h = 46
        center_x = SCREEN_WIDTH // 2
        start_y = 240
        left_x = center_x - button_w - 12
        right_x = center_x + 12

        left_nums = [2, 3, 4, 5]
        right_nums = [6, 7, 8]
        for idx, num in enumerate(left_nums):
            b = Button(left_x, start_y + idx * (button_h + 12), button_w, button_h, f"{num} игроков")
            self.buttons.append((num, b))
        for idx, num in enumerate(right_nums):
            b = Button(right_x, start_y + idx * (button_h + 12), button_w, button_h, f"{num} игроков")
            self.buttons.append((num, b))

    def draw(self):
        self.screen.fill((10, 60, 10))
        title = self.title_font.render("МЕНТАЛЬНЫЙ ПОКЕР", True, WHITE)
        self.screen.blit(title, title.get_rect(center=(SCREEN_WIDTH // 2, 140)))
        instr = self.instr_font.render("Выберите количество игроков:", True, WHITE)
        self.screen.blit(instr, instr.get_rect(center=(SCREEN_WIDTH // 2, 200)))

        mouse_pos = pygame.mouse.get_pos()
        for num, btn in self.buttons:
            btn.update(mouse_pos)
            btn.draw(self.screen)

    def handle_events(self):
        mouse_pos = pygame.mouse.get_pos()
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                return None
            for num, btn in self.buttons:
                btn.update(mouse_pos)
                if btn.clicked(event):
                    return num
        return "continue"

# ---------------------------
# Game manager
# ---------------------------
class Game:
    def __init__(self):
        self.screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
        pygame.display.set_caption("Mental Poker")
        self.clock = pygame.time.Clock()
        self.state = GameState.PLAYER_SELECT
        self.player_selection = PlayerSelectionScreen(self.screen)
        self.poker_table = None
        self.num_players = 6

    def run(self):
        running = True
        while running:
            if self.state == GameState.PLAYER_SELECT:
                result = self.player_selection.handle_events()
                if result is None:
                    running = False
                elif isinstance(result, int):
                    self.num_players = result
                    self.poker_table = PokerTable(self.num_players)
                    self.state = GameState.PLAYING
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

# ---------------------------
# Запуск
# ---------------------------
if __name__ == "__main__":
    game = Game()
    game.run()
