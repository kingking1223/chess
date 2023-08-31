#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>

sf::Vector2f getClosestGridPosition(const sf::Vector2f& position)
{
    int xIndex = static_cast<int>((position.x - 1000) / 100);
    int yIndex = static_cast<int>((position.y - 100) / 100);

    float newX = 1000 + xIndex * 100;
    float newY = 100 + yIndex * 100;

    return sf::Vector2f(newX, newY);
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Chess & Algorithms");
    
    sf::RectangleShape a8(sf::Vector2f(100, 100));
    a8.setFillColor(sf::Color(255, 206, 158));
    a8.setPosition(1000,100);

    sf::RectangleShape b8(sf::Vector2f(100, 100));
    b8.setFillColor(sf::Color(209, 137, 71));
    b8.setPosition(1100,100);

    sf::RectangleShape c8(sf::Vector2f(100, 100));
    c8.setFillColor(sf::Color(255, 206, 158));
    c8.setPosition(1200,100);

    sf::RectangleShape d8(sf::Vector2f(100, 100));
    d8.setFillColor(sf::Color(209, 137, 71));
    d8.setPosition(1300,100);

    sf::RectangleShape e8(sf::Vector2f(100, 100));
    e8.setFillColor(sf::Color(255, 206, 158));
    e8.setPosition(1400,100);

    sf::RectangleShape f8(sf::Vector2f(100, 100));
    f8.setFillColor(sf::Color(209, 137, 71));
    f8.setPosition(1500,100);

    sf::RectangleShape g8(sf::Vector2f(100, 100));
    g8.setFillColor(sf::Color(255, 206, 158));
    g8.setPosition(1600,100);

    sf::RectangleShape h8(sf::Vector2f(100, 100));
    h8.setFillColor(sf::Color(209, 137, 71));
    h8.setPosition(1700,100);

    sf::RectangleShape a7(sf::Vector2f(100, 100));
    a7.setFillColor(sf::Color(209, 137, 71));
    a7.setPosition(1000,200);

    sf::RectangleShape b7(sf::Vector2f(100, 100));
    b7.setFillColor(sf::Color(255, 206, 158));
    b7.setPosition(1100,200);

    sf::RectangleShape c7(sf::Vector2f(100, 100));
    c7.setFillColor(sf::Color(209, 137, 71));
    c7.setPosition(1200,200);

    sf::RectangleShape d7(sf::Vector2f(100, 100));
    d7.setFillColor(sf::Color(255, 206, 158));
    d7.setPosition(1300,200);

    sf::RectangleShape e7(sf::Vector2f(100, 100));
    e7.setFillColor(sf::Color(209, 137, 71));
    e7.setPosition(1400,200);

    sf::RectangleShape f7(sf::Vector2f(100, 100));
    f7.setFillColor(sf::Color(255, 206, 158));
    f7.setPosition(1500,200);

    sf::RectangleShape g7(sf::Vector2f(100, 100));
    g7.setFillColor(sf::Color(209, 137, 71));
    g7.setPosition(1600,200);

    sf::RectangleShape h7(sf::Vector2f(100, 100));
    h7.setFillColor(sf::Color(255, 206, 158));
    h7.setPosition(1700,200);

    sf::RectangleShape a6(sf::Vector2f(100, 100));
    a6.setFillColor(sf::Color(255, 206, 158));
    a6.setPosition(1000,300);

    sf::RectangleShape b6(sf::Vector2f(100, 100));
    b6.setFillColor(sf::Color(209, 137, 71));
    b6.setPosition(1100,300);

    sf::RectangleShape c6(sf::Vector2f(100, 100));
    c6.setFillColor(sf::Color(255, 206, 158));
    c6.setPosition(1200,300);

    sf::RectangleShape d6(sf::Vector2f(100, 100));
    d6.setFillColor(sf::Color(209, 137, 71));
    d6.setPosition(1300,300);

    sf::RectangleShape e6(sf::Vector2f(100, 100));
    e6.setFillColor(sf::Color(255, 206, 158));
    e6.setPosition(1400,300);

    sf::RectangleShape f6(sf::Vector2f(100, 100));
    f6.setFillColor(sf::Color(209, 137, 71));
    f6.setPosition(1500,300);

    sf::RectangleShape g6(sf::Vector2f(100, 100));
    g6.setFillColor(sf::Color(255, 206, 158));
    g6.setPosition(1600,300);

    sf::RectangleShape h6(sf::Vector2f(100, 100));
    h6.setFillColor(sf::Color(209, 137, 71));
    h6.setPosition(1700,300);

    sf::RectangleShape a5(sf::Vector2f(100, 100));
    a5.setFillColor(sf::Color(209, 137, 71));
    a5.setPosition(1000,400);

    sf::RectangleShape b5(sf::Vector2f(100, 100));
    b5.setFillColor(sf::Color(255, 206, 158));
    b5.setPosition(1100,400);

    sf::RectangleShape c5(sf::Vector2f(100, 100));
    c5.setFillColor(sf::Color(209, 137, 71));
    c5.setPosition(1200,400);

    sf::RectangleShape d5(sf::Vector2f(100, 100));
    d5.setFillColor(sf::Color(255, 206, 158));
    d5.setPosition(1300,400);

    sf::RectangleShape e5(sf::Vector2f(100, 100));
    e5.setFillColor(sf::Color(209, 137, 71));
    e5.setPosition(1400,400);

    sf::RectangleShape f5(sf::Vector2f(100, 100));
    f5.setFillColor(sf::Color(255, 206, 158));
    f5.setPosition(1500,400);

    sf::RectangleShape g5(sf::Vector2f(100, 100));
    g5.setFillColor(sf::Color(209, 137, 71));
    g5.setPosition(1600,400);

    sf::RectangleShape h5(sf::Vector2f(100, 100));
    h5.setFillColor(sf::Color(255, 206, 158));
    h5.setPosition(1700,400);

    sf::RectangleShape a4(sf::Vector2f(100, 100));
    a4.setFillColor(sf::Color(255, 206, 158));
    a4.setPosition(1000,500);

    sf::RectangleShape b4(sf::Vector2f(100, 100));
    b4.setFillColor(sf::Color(209, 137, 71));
    b4.setPosition(1100,500);

    sf::RectangleShape c4(sf::Vector2f(100, 100));
    c4.setFillColor(sf::Color(255, 206, 158));
    c4.setPosition(1200,500);

    sf::RectangleShape d4(sf::Vector2f(100, 100));
    d4.setFillColor(sf::Color(209, 137, 71));
    d4.setPosition(1300,500);

    sf::RectangleShape e4(sf::Vector2f(100, 100));
    e4.setFillColor(sf::Color(255, 206, 158));
    e4.setPosition(1400,500);

    sf::RectangleShape f4(sf::Vector2f(100, 100));
    f4.setFillColor(sf::Color(209, 137, 71));
    f4.setPosition(1500,500);

    sf::RectangleShape g4(sf::Vector2f(100, 100));
    g4.setFillColor(sf::Color(255, 206, 158));
    g4.setPosition(1600,500);

    sf::RectangleShape h4(sf::Vector2f(100, 100));
    h4.setFillColor(sf::Color(209, 137, 71));
    h4.setPosition(1700,500);

    sf::RectangleShape a3(sf::Vector2f(100, 100));
    a3.setFillColor(sf::Color(209, 137, 71));
    a3.setPosition(1000,600);

    sf::RectangleShape b3(sf::Vector2f(100, 100));
    b3.setFillColor(sf::Color(255, 206, 158));
    b3.setPosition(1100,600);

    sf::RectangleShape c3(sf::Vector2f(100, 100));
    c3.setFillColor(sf::Color(209, 137, 71));
    c3.setPosition(1200,600);

    sf::RectangleShape d3(sf::Vector2f(100, 100));
    d3.setFillColor(sf::Color(255, 206, 158));
    d3.setPosition(1300,600);

    sf::RectangleShape e3(sf::Vector2f(100, 100));
    e3.setFillColor(sf::Color(209, 137, 71));
    e3.setPosition(1400,600);

    sf::RectangleShape f3(sf::Vector2f(100, 100));
    f3.setFillColor(sf::Color(255, 206, 158));
    f3.setPosition(1500,600);

    sf::RectangleShape g3(sf::Vector2f(100, 100));
    g3.setFillColor(sf::Color(209, 137, 71));
    g3.setPosition(1600,600);

    sf::RectangleShape h3(sf::Vector2f(100, 100));
    h3.setFillColor(sf::Color(255, 206, 158));
    h3.setPosition(1700,600);

    sf::RectangleShape a2(sf::Vector2f(100, 100));
    a2.setFillColor(sf::Color(255, 206, 158));
    a2.setPosition(1000,700);

    sf::RectangleShape b2(sf::Vector2f(100, 100));
    b2.setFillColor(sf::Color(209, 137, 71));
    b2.setPosition(1100,700);

    sf::RectangleShape c2(sf::Vector2f(100, 100));
    c2.setFillColor(sf::Color(255, 206, 158));
    c2.setPosition(1200,700);

    sf::RectangleShape d2(sf::Vector2f(100, 100));
    d2.setFillColor(sf::Color(209, 137, 71));
    d2.setPosition(1300,700);

    sf::RectangleShape e2(sf::Vector2f(100, 100));
    e2.setFillColor(sf::Color(255, 206, 158));
    e2.setPosition(1400,700);

    sf::RectangleShape f2(sf::Vector2f(100, 100));
    f2.setFillColor(sf::Color(209, 137, 71));
    f2.setPosition(1500,700);

    sf::RectangleShape g2(sf::Vector2f(100, 100));
    g2.setFillColor(sf::Color(255, 206, 158));
    g2.setPosition(1600,700);

    sf::RectangleShape h2(sf::Vector2f(100, 100));
    h2.setFillColor(sf::Color(209, 137, 71));
    h2.setPosition(1700,700);

    sf::RectangleShape a1(sf::Vector2f(100, 100));
    a1.setFillColor(sf::Color(209, 137, 71));
    a1.setPosition(1000,800);

    sf::RectangleShape b1(sf::Vector2f(100, 100));
    b1.setFillColor(sf::Color(255, 206, 158));
    b1.setPosition(1100,800);

    sf::RectangleShape c1(sf::Vector2f(100, 100));
    c1.setFillColor(sf::Color(209, 137, 71));
    c1.setPosition(1200,800);

    sf::RectangleShape d1(sf::Vector2f(100, 100));
    d1.setFillColor(sf::Color(255, 206, 158));
    d1.setPosition(1300,800);

    sf::RectangleShape e1(sf::Vector2f(100, 100));
    e1.setFillColor(sf::Color(209, 137, 71));
    e1.setPosition(1400,800);

    sf::RectangleShape f1(sf::Vector2f(100, 100));
    f1.setFillColor(sf::Color(255, 206, 158));
    f1.setPosition(1500,800);

    sf::RectangleShape g1(sf::Vector2f(100, 100));
    g1.setFillColor(sf::Color(209, 137, 71));
    g1.setPosition(1600,800);

    sf::RectangleShape h1(sf::Vector2f(100, 100));
    h1.setFillColor(sf::Color(255, 206, 158));
    h1.setPosition(1700,800);

    sf::Texture B, b, K, k, N, n, P, p, Q, q, R, r;

    B.loadFromFile("../assets/pieces/B.png");
    b.loadFromFile("../assets/pieces/b.png");
    K.loadFromFile("../assets/pieces/K.png");
    k.loadFromFile("../assets/pieces/k.png");
    N.loadFromFile("../assets/pieces/N.png");
    n.loadFromFile("../assets/pieces/n.png");
    P.loadFromFile("../assets/pieces/P.png");
    p.loadFromFile("../assets/pieces/p.png");
    Q.loadFromFile("../assets/pieces/Q.png");
    q.loadFromFile("../assets/pieces/q.png");
    R.loadFromFile("../assets/pieces/R.png");
    r.loadFromFile("../assets/pieces/r.png");


    sf::Sprite a8s(r);
    sf::Sprite b8s(n);
    sf::Sprite c8s(b);
    sf::Sprite d8s(q);
    sf::Sprite e8s(k);
    sf::Sprite f8s(b);
    sf::Sprite g8s(n);
    sf::Sprite h8s(r);
    sf::Sprite a7s(p);
    sf::Sprite b7s(p);
    sf::Sprite c7s(p);
    sf::Sprite d7s(p);
    sf::Sprite e7s(p);
    sf::Sprite f7s(p);
    sf::Sprite g7s(p);
    sf::Sprite h7s(p);
    sf::Sprite a2s(P);
    sf::Sprite b2s(P);
    sf::Sprite c2s(P);
    sf::Sprite d2s(P);
    sf::Sprite e2s(P);
    sf::Sprite f2s(P);
    sf::Sprite g2s(P);
    sf::Sprite h2s(P);
    sf::Sprite a1s(R);
    sf::Sprite b1s(N);
    sf::Sprite c1s(B);
    sf::Sprite d1s(Q);
    sf::Sprite e1s(K);
    sf::Sprite f1s(B);
    sf::Sprite g1s(N);
    sf::Sprite h1s(R);

    a8s.setPosition(1005, 105);
    b8s.setPosition(1105, 105);
    c8s.setPosition(1205, 105);
    d8s.setPosition(1305, 105);
    e8s.setPosition(1405, 105);
    f8s.setPosition(1505, 105);
    g8s.setPosition(1605, 105);
    h8s.setPosition(1705, 105);
    a7s.setPosition(1005, 205);
    b7s.setPosition(1105, 205);
    c7s.setPosition(1205, 205);
    d7s.setPosition(1305, 205);
    e7s.setPosition(1405, 205);
    f7s.setPosition(1505, 205);
    g7s.setPosition(1605, 205);
    h7s.setPosition(1705, 205);

    a2s.setPosition(1005, 705);
    b2s.setPosition(1105, 705);
    c2s.setPosition(1205, 705);
    d2s.setPosition(1305, 705);
    e2s.setPosition(1405, 705);
    f2s.setPosition(1505, 705);
    g2s.setPosition(1605, 705);
    h2s.setPosition(1705, 705);
    a1s.setPosition(1005, 805);
    b1s.setPosition(1105, 805);
    c1s.setPosition(1205, 805);
    d1s.setPosition(1305, 805);
    e1s.setPosition(1405, 805);
    f1s.setPosition(1505, 805);
    g1s.setPosition(1605, 805);
    h1s.setPosition(1705, 805);
    
    bool isPieceSelected = false;
    sf::Sprite* selectedPiece = nullptr;
    sf::Vector2f originalPosition;




    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                
                if (!isPieceSelected)
                {
                    if (a8s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &a8s;
                        originalPosition = a8s.getPosition();
                    }
                    if (b8s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &b8s;
                        originalPosition = b8s.getPosition();
                    }
                    if (c8s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &c8s;
                        originalPosition = c8s.getPosition();
                    }
                    if (d8s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &d8s;
                        originalPosition = d8s.getPosition();
                    }
                    if (e8s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &e8s;
                        originalPosition = e8s.getPosition();
                    }
                    if (f8s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &f8s;
                        originalPosition = f8s.getPosition();
                    }
                    if (g8s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &g8s;
                        originalPosition = g8s.getPosition();
                    }
                    if (h8s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &h8s;
                        originalPosition = h8s.getPosition();
                    }
                    if (a7s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &a7s;
                        originalPosition = a7s.getPosition();
                    }
                    if (b7s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &b7s;
                        originalPosition = b7s.getPosition();
                    }
                    if (c7s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &c7s;
                        originalPosition = c7s.getPosition();
                    }
                    if (d7s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &d7s;
                        originalPosition = d7s.getPosition();
                    }
                    if (e7s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &e7s;
                        originalPosition = e7s.getPosition();
                    }
                    if (f7s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &f7s;
                        originalPosition = f7s.getPosition();
                    }
                    if (g7s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &g7s;
                        originalPosition = g7s.getPosition();
                    }
                    if (h7s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &h7s;
                        originalPosition = h7s.getPosition();
                    }
                    if (a2s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &a2s;
                        originalPosition = a2s.getPosition();
                    }
                    if (b2s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &b2s;
                        originalPosition = b2s.getPosition();
                    }
                    if (c2s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &c2s;
                        originalPosition = c2s.getPosition();
                    }
                    if (d2s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &d2s;
                        originalPosition = d2s.getPosition();
                    }
                    if (e2s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &e2s;
                        originalPosition = e2s.getPosition();
                    }
                    if (f2s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &f2s;
                        originalPosition = f2s.getPosition();
                    }
                    if (g2s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &g2s;
                        originalPosition = g2s.getPosition();
                    }
                    if (h2s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &h2s;
                        originalPosition = h2s.getPosition();
                    }
                    if (a1s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &a1s;
                        originalPosition = a1s.getPosition();
                    }
                    if (b1s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &b1s;
                        originalPosition = b1s.getPosition();
                    }
                    if (c1s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &c1s;
                        originalPosition = c1s.getPosition();
                    }
                    if (d1s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &d1s;
                        originalPosition = d1s.getPosition();
                    }
                    if (e1s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &e1s;
                        originalPosition = e1s.getPosition();
                    }
                    if (f1s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &f1s;
                        originalPosition = f1s.getPosition();
                    }
                    if (g1s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &g1s;
                        originalPosition = g1s.getPosition();
                    }
                    if (h2s.getGlobalBounds().contains(mousePosition))
                    {
                        isPieceSelected = true;
                        selectedPiece = &h2s;
                        originalPosition = h2s.getPosition();
                    }
                
                }
                else
                {
                    sf::Vector2f newPosition = getClosestGridPosition(mousePosition);
                    selectedPiece->setPosition(newPosition);
                    isPieceSelected = false;
                    selectedPiece = nullptr;
                }
            }
        }

        window.clear();

        if (isPieceSelected && selectedPiece)
        {
            sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            selectedPiece->setPosition(mousePosition.x - selectedPiece->getGlobalBounds().width / 2,
                                    mousePosition.y - selectedPiece->getGlobalBounds().height / 2);
            window.draw(*selectedPiece);
        }
        
        window.draw(a1);
        window.draw(a2);
        window.draw(a3);
        window.draw(a4);
        window.draw(a5);
        window.draw(a6);
        window.draw(a7);
        window.draw(a8);
        window.draw(b1);
        window.draw(b2);
        window.draw(b3);
        window.draw(b4);
        window.draw(b5);
        window.draw(b6);
        window.draw(b7);
        window.draw(b8);
        window.draw(c1);
        window.draw(c2);
        window.draw(c3);
        window.draw(c4);
        window.draw(c5);
        window.draw(c6);
        window.draw(c7);
        window.draw(c8);
        window.draw(d1);
        window.draw(d2);
        window.draw(d3);
        window.draw(d4);
        window.draw(d5);
        window.draw(d6);
        window.draw(d7);
        window.draw(d8);
        window.draw(e1);
        window.draw(e2);
        window.draw(e3);
        window.draw(e4);
        window.draw(e5);
        window.draw(e6);
        window.draw(e7);
        window.draw(e8);
        window.draw(f1);
        window.draw(f2);
        window.draw(f3);
        window.draw(f4);
        window.draw(f5);
        window.draw(f6);
        window.draw(f7);
        window.draw(f8);
        window.draw(g1);
        window.draw(g2);
        window.draw(g3);
        window.draw(g4);
        window.draw(g5);
        window.draw(g6);
        window.draw(g7);
        window.draw(g8);
        window.draw(h1);
        window.draw(h2);
        window.draw(h3);
        window.draw(h4);
        window.draw(h5);
        window.draw(h6);
        window.draw(h7);
        window.draw(h8);
        window.draw(a8s);
        window.draw(b8s);
        window.draw(c8s);
        window.draw(d8s);
        window.draw(e8s);
        window.draw(f8s);
        window.draw(g8s);
        window.draw(h8s);
        window.draw(a7s);
        window.draw(b7s);
        window.draw(c7s);
        window.draw(d7s);
        window.draw(e7s);
        window.draw(f7s);
        window.draw(g7s);
        window.draw(h7s);

        window.draw(a2s);
        window.draw(b2s);
        window.draw(c2s);
        window.draw(d2s);
        window.draw(e2s);
        window.draw(f2s);
        window.draw(g2s);
        window.draw(h2s);
        window.draw(a1s);
        window.draw(b1s);
        window.draw(c1s);
        window.draw(d1s);
        window.draw(e1s);
        window.draw(f1s);
        window.draw(g1s);
        window.draw(h1s);
        window.display();
    }

    return 0;
}
