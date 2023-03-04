#ifndef BUTTON
#define BUTTON

#include <functional> // pour les functions d'event
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Button
{
public:
    Button(string txt, int charSize, Color bgColor, Color fgColor, Vector2f size, Vector2f pos, bool show)
    {
        text.setString(txt);
        text.setCharacterSize(charSize); // taille de la police
        text.setFillColor(fgColor);
        text.setFont(defaultFont);

        button.setFillColor(bgColor);
        button.setSize(size);

        setPosition(pos);

        if (show)
            this->show(true);
    }

    // setter
    void setContent(string txt) // a test
    {
        text.setString(txt);
        if (isActive)
            updateForDraw();
    }
    void setFont(Font &font)
    {
        text.setFont(font);
        if (isActive)
            updateForDraw();
    }
    void setBgColor(Color color)
    {
        button.setFillColor(color);
        if (isActive)
            updateForDraw();
    }
    void setFgColor(Color color)
    {
        text.setFillColor(color);
        if (isActive)
            updateForDraw();
    }
    void setPosition(Vector2f pos)
    {
        button.setPosition(pos);

        // pour que les text soit centrer
        float xPos = (pos.x + button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2);
        float yPos = (pos.y + button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2);
        text.setPosition({xPos, yPos});
        if (isActive)
            updateForDraw();
    }

    // getter
    const string getContent() { return text.getString(); }
    const Font *getFont() { return text.getFont(); }
    Color getBgColor() const { return button.getFillColor(); }
    Color getFgColor() const { return text.getFillColor(); }
    Vector2f getPos() const { return button.getPosition(); }

    bool isMouseOver(RenderWindow &window)
    {
        if (isActive) // si il n'est pas actif ou la souris est forcément pas dessus
        {
            Vector2i mouseP = Mouse::getPosition(window);

            int btnMX = button.getPosition().x + button.getLocalBounds().width;  // max btn X
            int btnMY = button.getPosition().y + button.getLocalBounds().height; // max btn Y

            if (mouseP.x > button.getPosition().x && mouseP.y > button.getPosition().y && mouseP.x < btnMX && mouseP.y < btnMY)
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
            DIdBtn = Draw::addDrawable(button);
            DIdTxt = Draw::addDrawable(text);
            isActive = true;
        }
        else if (!show)
        {
            Draw::removeDrawable(DIdBtn);
            Draw::removeDrawable(DIdTxt);
            isActive = false;
        }
    }
    void updateForDraw()
    {
        Draw::updateDrawable(DIdBtn, button);
        Draw::updateDrawable(DIdTxt, text);
    }

    bool isActive = false; // si il est afficher a l'ecran

    // Fonction d'event
    function<void(int)> onHover = [](int id) {};
    function<void(int)> outHover = [](int id) {};
    function<void(int)> onClick = [](int id) {};

private:
    RectangleShape button;
    Text text;
    int DIdBtn;
    int DIdTxt;
};

#endif // BUTTON