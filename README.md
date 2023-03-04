Voici une class qui permet de crée un button intéractif en c++ avec sfml

# Button

c'est une class pour les boutton avec du text

# IButton

c'est une class pour les bouton qui remplace le text par une image

# Function d'event

personnellement j'utilise une class qui gére tout les boutton cela est plus facile pour les event voici la function que j'utilise:

```cpp
#include <vector>
#include <variant>
#include <functional>

vector<variant<Button *, IButton *>> buttons;

void event(RenderWindow &window, Event event)
{
    if (event.type == Event::MouseMoved)
    {
        size_t index = 0;
        for (auto button : buttons)
        {
            visit([&window, &index](auto &&button)
                  {
                      if (button->isMouseOver(window))
                          button->onHover(index);
                      else if (button->isActive)
                          button->outHover(index); },
                  button);
            index++;
        }
    }
    else if (event.type == Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == Mouse::Left)
        {
            size_t index = 0;
            for (auto button : buttons)
            {
                visit([&window, &index](auto &&button)
                        {
                        if (button->isMouseOver(window))
                            button->onClick(index); },
                        button);
                index++;
            }
        }
    }
}

// dans le main:
while (window.isOpen())
{
    while (window.pollEvent(event))
    {
        event(window, event);
    }

    ...
}
```