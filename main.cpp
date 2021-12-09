#include "logic.hpp"

struct Card
{
public:
    int value;

    Suit suit;

    Face face;

    Card(int i, Suit s)
    {
        value = i;
        suit = s;
    }

    Card(int i, Suit s, Face f)
    {
        value = i;
        suit = s;
        face = f;
    }
};

struct Deck
{
public:
    std::vector<Card> cardStack = std::vector<Card>();
    
    Deck()
    {
        for (int suitCount = 0; suitCount < 4; suitCount++)
        {
            int val = 1;
            int face = 0;
            for (int cardsInSuit = 0; cardsInSuit < 13; cardsInSuit++)
            {
                cardStack.push_back(std::move(Card(val, (Suit)suitCount, (Face)face)));
                if (val != 10)
                    val++;
                else
                {
                    face++;
                }
            }
        }
    }

    void Shuffle()
    {
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(cardStack.begin(), cardStack.end(), std::default_random_engine(seed));
    }

    Card Deal()
    {
        Card ret = cardStack.back();
        cardStack.erase(cardStack.end());
        return std::move(ret);
    }
};

class Player
{
public:
    std::vector<Card> hand;

    Player()
    {
        hand = std::vector<Card>();
    }

    int CheckHand()
    {
        int total = 0;
        for (std::vector<Card>::iterator it = hand.begin(); it != hand.end(); it++)
        {
            total += it->value;
        }
        return total;
    }
};

// checks for an ace-10 blackjack
bool OpeningBlackjack(Player *p)
{
    if (p->CheckHand() == 11 && (p->hand[0].value == 1 || p->hand[1].value == 1))
        return true;
    return false;
}

GameState Game()
{   
    Deck d = Deck();
    d.Shuffle();
    Player *player = new Player();
    Player *dealer = new Player();
    
    player->hand.push_back(d.Deal());
    player->hand.push_back(d.Deal());

    std::cout << "Player hand: " << player->CheckHand() << std::endl;

    if (OpeningBlackjack(player))
        return WIN;
    
    std::cout << "Player hand: " << player->CheckHand() << std::endl;

    dealer->hand.push_back(d.Deal());
    dealer->hand.push_back(d.Deal());

    if (OpeningBlackjack(dealer))
        return LOSE;

    while (player->CheckHand() < 17)
    {
        player->hand.push_back(d.Deal());
        if (player->CheckHand() == 21)
            return WIN;
        else if (player->CheckHand() > 21)
            return LOSE;
    }
    while (dealer->CheckHand() < 17)
    {
        dealer->hand.push_back(d.Deal());
        if (dealer->CheckHand() == 21)

            return LOSE;
        else if (dealer->CheckHand() > 21)
            return WIN;
    }

    if (player->CheckHand() == 21)
    {
        return WIN;
    }
    else if (dealer->CheckHand() == 21)
    {
        return LOSE;
    }
    else if (player->CheckHand() > dealer->CheckHand())
    {
        return WIN;
    }

    return LOSE;
}

std::string Result(GameState g)
{
    if(g)
        return std::move("House wins");
    return std::move("Player wins!");
}

int main()
{
    for (int i = 0; i < 100; i++)
    {
        
        std::cout << Result(Game()) << std::endl;
    }
}