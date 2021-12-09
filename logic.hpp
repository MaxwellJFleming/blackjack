#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

enum GameState { WIN, LOSE };

enum Face { NUMBER, JACK, QUEEN, KING };

enum Suit { HEART, DIAMOND, SPADE, CLUB };

struct Card;

struct Deck;

class Player;

bool OpeningBlackjack(Player *p);

GameState Game();

std::string Result(GameState g);