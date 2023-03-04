#ifndef IBUTTON
#define IBUTTON

#include <functional>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class IButton
{
public:
    IButton(string name, Vector2f pos, bool show)
    {
        img = Utils::textureToSprite(name, Utils::loadTexture(name));

        img->setPosition(pos);

        if (show)
            this->show(true);
    }
    IButton(string name, Vector2f pos, Vector2f size, Color bgColor, bool show)
    {
        img = Utils::textureToSprite(name, Utils::loadTexture(name));

        button.setFillColor(bgColor);
        button.setSize(size);

        setPosition(pos);

        if (show)
            this->show(true);
    }

    // setter
    void setContent(string name)
    {
        Vector2f pos = img->getPosition();
        img = Utils::textureToSprite(name, Utils::loadTexture(name), pos);
        if (isActive)
            updateForDraw();
    }
    void setBgColor(Color color)
    {
        button.setFillColor(color);
        if (isActive)
            updateForDraw();
    }
    void setPosition(Vector2f pos)
    {
        button.setPosition(pos);
        float xPos = pos.x;
        float yPos = pos.y;
        if (button.getSize().x > 0 && button.getSize().y > 0)
        {
            xPos = (pos.x + button.getLocalBounds().width / 2) - (img->getLocalBounds().width / 2);
            yPos = (pos.y + button.getLocalBounds().height / 2) - (img->getLocalBounds().height / 2);
        }
        img->setPosition({xPos, yPos});
        if (isActive)
            updateForDraw();
    }

    // getter
    Color getBgColor() const { return button.getFillColor(); }
    Vector2f getPos() const { return button.getPosition(); }

    bool isMouseOver(RenderWindow &window)
    {
        if (isActive)
        {
            Vector2i mouseP = Mouse::getPosition(window);

            int btnMX;
            int btnMY;

            if (button.getSize().x > 0 && button.getSize().y > 0)
            {
                btnMX = button.getPosition().x + button.getLocalBounds().width;  // max btn X
                btnMY = button.getPosition().y + button.getLocalBounds().height; // max btn Y
            }
            else
            {
                btnMX = img->getPosition().x + img->getLocalBounds().width;  // max btn X
                btnMY = img->getPosition().y + img->getLocalBounds().height; // max btn Y
            }

            if (mouseP.x > img->getPosition().x && mouseP.y > img->getPosition().y && mouseP.x < btnMX && mouseP.y < btnMY)
            {
                return true;
            }
        }
        return false; // si il n'est pas actif ou la souris n'est pas dessus
    }
    void show(bool show)
    {
        if (show)
        {
            DIdBtn = Draw::addDrawable(button);
            DIdImg = Draw::addDrawable(*img);
            isActive = true;
        }
        else if (!show)
        {
            Draw::removeDrawable(DIdBtn);
            Draw::removeDrawable(DIdImg);
            isActive = false;
        }
    }
    void updateForDraw()
    {
        Draw::updateDrawable(DIdBtn, button);
        Draw::updateDrawable(DIdImg, *img);
    }

    bool isActive = false;

    // Fonction d'event
    function<void(int)> onHover = [](int id) {};
    function<void(int)> outHover = [](int id) {};
    function<void(int)> onClick = [](int id) {};

private:
    Sprite *img;
    RectangleShape button;

    int DIdImg;
    int DIdBtn;
};

#endif // IBUTTON