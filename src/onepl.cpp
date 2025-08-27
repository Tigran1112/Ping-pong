#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow win(sf::VideoMode({600, 800}), "SFML ping-pong");
    sf::RectangleShape player1;
    sf::RectangleShape ball;
    
    player1.setSize({150, 20});
    player1.setPosition({250, 780});

    ball.setSize({10, 10});
    ball.setPosition({250, 50});
    sf::Vector2f ballspeed(0.05f, 0.05f);

    while (win.isOpen()) {
        while (auto eventOpt = win.pollEvent())
        {
            if (eventOpt->is<sf::Event::Closed>()) win.close();
        }
                

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && player1.getPosition().x > 0) player1.move({-0.1f, 0});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && player1.getPosition().x + player1.getSize().x < win.getSize().x) player1.move({0.1f, 0});

        ball.move(ballspeed);

        if (ball.getPosition().x <= 0 || ball.getPosition().x + ball.getSize().x >= win.getSize().x) {
            ballspeed.x *= -1;
        }

        if (ball.getPosition().y <= 0) {
            ballspeed.y *= -1;
        }
        if (ball.getPosition().y >= 800) {
            std::exit(1);
        }

        if (ball.getPosition().y + ball.getSize().y >= player1.getPosition().y &&
            ball.getPosition().x + ball.getSize().x >= player1.getPosition().x &&
            ball.getPosition().x <= player1.getPosition().x + player1.getSize().x) {
            ballspeed.y *= -1;
        }
        
        win.clear();
        win.draw(player1);
        win.draw(ball);
        win.display();
    }

    return 0;
}