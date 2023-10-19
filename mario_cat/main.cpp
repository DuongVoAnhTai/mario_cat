#include <SFML/Graphics.hpp>

int main()
{
    // Tạo một cửa sổ SFML.
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Example");

    // Tải hình ảnh nền.
    sf::Sprite BackGr;
    sf::Texture BackGrText;
    if (!BackGrText.loadFromFile("PNG_file/dirt.png"))
    {
        // Xử lý lỗi.
        return EXIT_FAILURE;
    }

    BackGr.setTexture(BackGrText);
    BackGr.setPosition(10, 10);


    // Vẽ nhân vật lên cửa sổ.
    while (window.isOpen())
    {
        // Xử lý các sự kiện từ người dùng.
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Di chuyển nhân vật theo hướng con trỏ chuột.
        sf::Vector2f direction = window.mapPixelToCoords(sf::Mouse::getPosition(), window.getView());
        BackGr.move(direction);

        // Cập nhật tâm của nhân vật.
        sf::Vector2f center = BackGr.getPosition() + BackGr.getOrigin();
        center.x = window.getSize().x / 2;
        center.y = window.getSize().y / 2;
        BackGr.setCenter(center);

        // Vẽ nhân vật lên cửa sổ.
        window.clear();
        window.draw(BackGr);
        window.display();
    }

    return EXIT_SUCCESS;
}
