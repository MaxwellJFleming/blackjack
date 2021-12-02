#include "logic.hpp"

int randGen(int i) { return std::rand() % i; }

struct Card
{
    int value;
    
    Card(int i)
    {
        value = i;
    }
};

struct Deck
{
    std::vector<Card> cardStack = std::vector<Card>();
    
    Deck()
    {
        int valCount = 0;
        int val = 1;
        while (cardStack.size() < 52)
        {
            cardStack.push_back(std::move(Card(val)));
            valCount++;
            if (valCount == 4)
            {
                if (val != 10)
                {
                    val++;
                    valCount = 0;
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
        cardStack.erase(cardStack.end()-1);
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

GameState Game()
{   
    Deck d = Deck();
    d.Shuffle();
    Player player = Player();
    Player dealer = Player();
    
    player.hand.push_back(d.Deal());
    player.hand.push_back(d.Deal());
    std::cout << "Player hand: " << player.CheckHand() << std::endl;

    dealer.hand.push_back(d.Deal());
    dealer.hand.push_back(d.Deal());
    std::cout << "Dealer hand: " << dealer.CheckHand() << std::endl;

    while (player.CheckHand() < 17)
    {
        player.hand.push_back(d.Deal());
        std::cout << "Player hand: " << player.CheckHand() << std::endl;
        if (player.CheckHand() == 21)
        {
            return WIN;
        }
        else if (player.CheckHand() > 21)
        {
            return LOSE;
        }
    }
    while (dealer.CheckHand() < 17)
    {
        dealer.hand.push_back(d.Deal());
        std::cout << "Dealer hand: " << dealer.CheckHand() << std::endl;
        if (dealer.CheckHand() == 21)
        {
            return LOSE;
        }
        else if (dealer.CheckHand() > 21)
        {
            return WIN;
        }
    }

    if (player.CheckHand() == 21)
    {
        return WIN;
    }
    else if (dealer.CheckHand() == 21)
    {
        return LOSE;
    }
    else if (player.CheckHand() > dealer.CheckHand())
    {
        return WIN;
    }

    return LOSE;
}

int main()
{
    for (int i = 0; i < 100; i++)
    {
        std::cout << Game() << std::endl;
    }
}