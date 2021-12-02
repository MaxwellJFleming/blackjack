#pragma once
#include <stack>
#include <vector>
#include <iostream>

enum GameState { PLAYING, WIN, LOSE };

struct Card;

struct Deck;

class Player;

// GameState Game(Deck d, Player player, Player dealer);