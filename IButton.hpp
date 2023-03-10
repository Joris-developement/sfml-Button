#ifndef IBUTTON
#define IBUTTON

#include <functional> // pour les functions d'event
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class IButton
{
public:
    IButton(string name, Vector2f pos, bool show) // si vous ne voulez juste une image qui réagit comme un bouton
    {
        img = Utils::textureToSprite(name, Utils::loadTexture(name));

        img->setPosition(pos);

        if (show)
            this->show(true);
    }
    IButton(string name, Vector2f pos, Vector2f size, Color bgColor, bool show) // si vous voulez une image entourer d'un carré de couleur
    {
        img = Utils::textureToSprite(name, Utils::loadTexture(name));

        button.setFillColor(bgColor);
        button.setSize(size);

        setPosition(pos);

        if (show)
            this->show(true);
    }

    // setter
    void setContent(string name) // a test
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
        if (button.getSize().x > 0 && button.getSize().y > 0) // si vous avez mis un button
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
        if (isActive) // si il n'est pas actif ou la souris est forcément pas dessus
        {
            Vector2i mouseP = Mouse::getPosition(window);

            int btnMX;
            int btnMY;

            if (button.getSize().x > 0 && button.getSize().y > 0) // si vous avez mis un button
            {
                btnMX = button.getPosition().x + button.getLocalBounds().width;  // max btn X
                btnMY = button.getPosition().y + button.getLocalBounds().height; // max btn Y
            }
            else // si vous avez juste mis une image
            {
                btnMX = img->getPosition().x + img->getLocalBounds().width;  // max btn X
                btnMY = img->getPosition().y + img->getLocalBounds().height; // max btn Y
            }

            if (mouseP.x > img->getPosition().x && mouseP.y > img->getPosition().y && mouseP.x < btnMX && mouseP.y < btnMY)
            {
                return true;
            }
        }
        return false;
    }
    void show(bool show)
    {
        if (show)
        {
            DIdBtn = Draw::addDrawable(button); // regarder sur mon github le repo sfml-Draw (https://github.com/Joris-developement/sfml-Draw)
            DIdImg = Draw::addDrawable(*img);   // regarder sur mon github le repo sfml-Draw (https://github.com/Joris-developement/sfml-Draw)
            isActive = true;
        }
        else if (!show)
        {
            Draw::removeDrawable(DIdBtn); // regarder sur mon github le repo sfml-Draw (https://github.com/Joris-developement/sfml-Draw)
            Draw::removeDrawable(DIdImg); // regarder sur mon github le repo sfml-Draw (https://github.com/Joris-developement/sfml-Draw)
            isActive = false;
        }
    }
    void updateForDraw()
    {
        Draw::updateDrawable(DIdBtn, button); // regarder sur mon github le repo sfml-Draw (https://github.com/Joris-developement/sfml-Draw)
        Draw::updateDrawable(DIdImg, *img);   // regarder sur mon github le repo sfml-Draw (https://github.com/Joris-developement/sfml-Draw)
    }

    bool isActive = false; // si il est afficher a l'ecran

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