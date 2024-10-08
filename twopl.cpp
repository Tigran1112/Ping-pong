#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow win(sf::VideoMode(600, 800), "SFML ping-pong");
    sf::RectangleShape player1;
    sf::RectangleShape player2;
    sf::RectangleShape ball;
    
    player1.setSize(sf::Vector2f(150, 20));
    player1.setPosition(250, 780);

    player2.setSize(sf::Vector2f(150, 20));
    player2.setPosition(250, 0);

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

        // Движение второго игрока
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player2.getPosition().x > 0) {
            player2.move(-0.1f, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player2.getPosition().x + player2.getSize().x < win.getSize().x) {
            player2.move(0.1f, 0);
        }

        // Движение мяча
        ball.move(ballspeed);

        // Отражение от левой и правой границ
        if (ball.getPosition().x <= 0 || ball.getPosition().x + ball.getSize().x >= win.getSize().x) {
            ballspeed.x *= -1;
        }

        // Отражение от верхней границы
        if (ball.getPosition().y <= 0) {
            std::exit(1);
        }
        // Если мяч касается нижней границы, мяч останавливается
        if (ball.getPosition().y >= 800) {
            std::exit(1);
        }

        // Проверка на касание первого игрока (внизу)
        if (ball.getPosition().y + ball.getSize().y >= player1.getPosition().y &&
            ball.getPosition().x + ball.getSize().x >= player1.getPosition().x &&
            ball.getPosition().x <= player1.getPosition().x + player1.getSize().x) {
            ballspeed.y *= -1;
        }
        
        // Проверка на касание второго игрока (вверху)
        if (ball.getPosition().y <= player2.getPosition().y + player2.getSize().y &&
            ball.getPosition().x + ball.getSize().x >= player2.getPosition().x &&
            ball.getPosition().x <= player2.getPosition().x + player2.getSize().x) {
            ballspeed.y *= -1;
        }

        win.clear();
        win.draw(player1);
        win.draw(player2);
        win.draw(ball);
        win.display();
    }

    return 0;
}