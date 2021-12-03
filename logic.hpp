#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

enum GameState { WIN, LOSE };

struct Card;

struct Deck;

class Player;

GameState Game();