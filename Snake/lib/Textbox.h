#pragma once
#include<bits/stdc++.h>
#include<SFML/Graphics.hpp>
using MessageContainer = std::vector<std::string>;

class TextBox{
    public:
        TextBox();
        TextBox(int l_visible,int l_charSize, int l_width, sf::Vector2f l_screenPos);
        ~TextBox();
        void Setup(int l_visible,int l_charSize, int l_width, sf::Vector2f l_screenPos);
        void Add(std::string l_msg);
        void Clear();
        void Render(sf::RenderWindow& l_wind);
    
    private:
        MessageContainer m_msg;
        int m_numVisible;

        sf::RectangleShape m_backdrop;
        sf::Font m_font;
        sf::Text m_content;
};