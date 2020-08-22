#include<Textbox.h>

TextBox::TextBox(){
    Setup(5,9,200,sf::Vector2f(0,0));
}

TextBox::TextBox(int l_visible,int l_charSize, int l_width, sf::Vector2f l_screenPos){
    Setup( l_visible,l_charSize,l_width,l_screenPos);
}

void TextBox::Setup(int l_visible,int l_charSize, int l_width, sf::Vector2f l_screenPos){
    m_numVisible = l_visible;
    sf::Vector2f l_offset(2.0f,2.0f);
    /*
    m_font.loadFromFile("Kust.ttf");
    m_content.setFont(m_font);
    m_content.setString("");
    m_content.setCharacterSize(l_charSize);
    m_content.setColor(sf::Color::White);
    m_content.setPosition(l_screenPos+l_offset);
    */
    m_font.loadFromFile("Kust.ttf");
    m_content.setFont(m_font);
    m_content.setString("");
    m_content.setCharacterSize(l_charSize);
    //m_content.setFillColor(sf::Color::White);
    m_content.setColor(sf::Color::White);
    m_content.setPosition(l_screenPos + l_offset);

    m_backdrop.setSize(sf::Vector2f(
        l_width,(l_visible*(l_charSize*1.2f))
    ));
    m_backdrop.setFillColor(sf::Color(90,90,90,90));
    m_backdrop.setPosition(l_screenPos);
}

void TextBox::Add(std::string l_msg){
    m_msg.push_back(l_msg);
    if(m_msg.size()<6)
        return;
    m_msg.erase(m_msg.begin());
}

void TextBox::Clear(){
    m_msg.clear();
}

void TextBox::Render(sf::RenderWindow& l_window){
    std::string l_content;

    for(auto &itr : m_msg){
        l_content.append(itr+"\n");
    }
    if(l_content!=""){
        m_content.setString(l_content);
        l_window.draw(m_backdrop);
        l_window.draw(m_content);
    }
}

TextBox::~TextBox(){}