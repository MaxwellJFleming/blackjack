#include "logic.hpp"

struct Card
{
    int value;
    
    Card(int i)
    {
        std::cout << i << std::endl;    //debug. remove before turning in
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
    
    std::vector<Card> Shuffle()
    {
        return std::move(cardStack);   //TODO
    }

    Card Deal()
    {
        Card ret = cardStack.back();
        cardStack.pop_back();
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
        std::cout << total << std::endl;
        return total;
    }
};

// GameState Game(Deck d, Player player, Player dealer)
// {
//     return WIN; //TODO
// }

int main()
{
    Deck d = Deck();
    Player player = Player();
    Player dealer = Player();
    
    player.hand.push_back(d.Deal());
    player.hand.push_back(d.Deal());

    player.CheckHand()

    // player.Hit(std::move(d));
    // player.Hit(std::move(d));

    // dealer.Hit(std::move(d));
    // dealer.Hit(std::move(d));

    // player.CheckHand();

    // for (int i = 0; i < 100; i++)
    // {
    //     std::cout << Game(d, player, dealer) << std::endl;
    // }
}