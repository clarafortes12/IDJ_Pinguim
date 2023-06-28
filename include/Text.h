#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "Component.h"
#include "GameObject.h"
#include "Timer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string.h>
using namespace std;

#define BLINK_PERIOD 0.6

class Text : public Component{
    public:
        enum TextStyle {SOLID, SHADED, BLENDED};
        
        Text(GameObject& associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color, bool blink = false);
        ~Text();

        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;
        
        void SetText(string text);
        void SetColor(SDL_Color color);
        void SetStyle(TextStyle style);
        void SetFontFile(string fontFile);
        void SetFontSize(int fontSize);
    
    private:
        shared_ptr<TTF_Font> font;
        shared_ptr<SDL_Texture> texture;

        string text;
        TextStyle style;
        string fontFile;
        int fontSize;
        SDL_Color color;

        Timer* blinkTimer;
        bool blink;
        bool display;

        void RemakeTexture();
};


#endif