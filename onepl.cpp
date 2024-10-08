#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow win(sf::VideoMode(600, 800), "SFML ping-pong");
    sf::RectangleShape player1;
    sf::RectangleShape ball;
    
    player1.setSize(sf::Vector2f(150, 20));
    player1.setPosition(250, 780);

    ball.setSize(sf::Vector2f(10, 10));
    ball.setPosition(250, 50);
    sf::Vector2f ballspeed(0.05f, 0.05f);

    while (win.isOpen()) {
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                win.close();
        }

        // Движение первого игрока
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player1.getPosition().x > 0) {
            player1.move(-0.1f, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player1.getPosition().x + player1.getSize().x < win.getSize().x) {
            player1.move(0.1f, 0);
        }

        // Движение мяча
        ball.move(ballspeed);

        // Отражение от левой и правой границ
        if (ball.getPosition().x <= 0 || ball.getPosition().x + ball.getSize().x >= win.getSize().x) {
            ballspeed.x *= -1;
        }

        // Отражение от верхней границы
        if (ball.getPosition().y <= 0) {
            ballspeed.y *= -1;
        }
        // Если мяч касается нижней границы, игра останавливается
        if (ball.getPosition().y >= 800) {
            std::exit(1);
        }

        // Проверка на касание первого игрока (внизу)
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