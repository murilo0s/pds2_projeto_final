#include "doctest.h"
#include "pipe.hpp"
#include "GameObject.hpp"

class Objeto1 : public GameObject {
public:
    Objeto1(float x, float y, float w, float h)
        : GameObject(x, y, w, h) {}

    void update(float) override {}
    void render() override {}
    bool checkCollision(const GameObject& other) override {
        return (this->x == other.getX() && this->y == other.getY());
    }
};

TEST_CASE("GameObject::Construtor") {
    Objeto1 obj(10, 20, 30, 40);
    CHECK(obj.getX() == 10);
    CHECK(obj.getY() == 20);
    CHECK(obj.getWidth() == 30);
    CHECK(obj.getHeight() == 40);
    CHECK(obj.getSpeedX() == doctest::Approx(0.0f));
    CHECK(obj.getSpeedY() == doctest::Approx(0.0f));
}

TEST_CASE("GameObject::setPosition") {
    Objeto1 obj(0, 0, 10, 10);
    obj.setPosition(100, 200);
    CHECK(obj.getX() == 100);
    CHECK(obj.getY() == 200);
}

TEST_CASE("GameObject::setSpeed") {
    Objeto1 obj(0, 0, 10, 10);
    obj.setSpeed(3.5f, -1.2f);
    CHECK(obj.getSpeedX() == doctest::Approx(3.5f));
    CHECK(obj.getSpeedY() == doctest::Approx(-1.2f));
}

TEST_CASE("GameObject::isOffScreen") {
    Objeto1 obj(0, 0, 10, 10);

    SUBCASE("Dentro da tela") {
        obj.setPosition(100, 100);
        CHECK(obj.isOffScreen() == false);
    }

    SUBCASE("Saindo pela esquerda") {
        obj.setPosition(-1, 100);
        CHECK(obj.isOffScreen() == true);
    }

    SUBCASE("Saindo pela direita") {
        obj.setPosition(800 - obj.getWidth() + 1, 100);
        CHECK(obj.isOffScreen() == true);
    }

    SUBCASE("Saindo pelo topo") {
        obj.setPosition(100, -1);
        CHECK(obj.isOffScreen() == true);
    }

    SUBCASE("Saindo pela base") {
        obj.setPosition(100, 600 - obj.getHeight() + 1);
        CHECK(obj.isOffScreen() == true);
    }
}

TEST_CASE("GameObject::move") {
    Objeto1 obj(0, 0, 10, 10);
    obj.setSpeed(5.0f, -3.0f);
    obj.move();
    CHECK(obj.getX() == doctest::Approx(5.0f));
    CHECK(obj.getY() == doctest::Approx(-3.0f));
}

TEST_CASE("GameObject::checkCollision") {
    Objeto1 obj1(10, 20, 10, 10);
    Objeto1 obj2(10, 20, 10, 10);
    Objeto1 obj3(15, 25, 10, 10);

    CHECK(obj1.checkCollision(obj2) == true);
    CHECK(obj1.checkCollision(obj3) == false);
}
