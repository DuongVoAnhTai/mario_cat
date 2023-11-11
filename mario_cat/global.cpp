#include"global.h"

bool globalFunc::CheckCollision(const sf::FloatRect& object1, const sf::FloatRect& object2)
{
    // Sử dụng sf::FloatRect để kiểm tra va chạm giữa hai đối tượng

    // Kiểm tra va chạm theo chiều ngang và chiều dọc
    if (object1.intersects(object2)) {
        return true;
    }

    // Nếu không có va chạm
    return false;
}