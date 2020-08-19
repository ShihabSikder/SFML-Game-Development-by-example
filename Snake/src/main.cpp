#include <SFML/Graphics.hpp>
#include<bits/stdc++.h>
using namespace std;

int main()
{  
    sf::RenderWindow window(sf::VideoMode(600,480),"Hi, Cmake");

    cout<<"Hello World"<<endl;
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
                break;
            }
        }
        window.display();
    }
}