#include"events.h"
#include<functional>
#include<iostream>

using Callbacks = std::unordered_map<std::string,std::function<void(EventDetails*)>>;

class EventManager{
    private:
        void LoadBindings();
        bindings m_bindings;
        Callbacks m_callbacks;
        bool m_hasFocus;

    public:
        EventManager();
        ~EventManager();

        bool AddBinding(Binding *l_binding);
        bool RemoveBinding(std::string l_name);
        void SetFocus(const bool& l_focus);

        template<class T>
        bool AddCallback(const std::string& l_name, void(T::*l_func)(EventDetails*), T* l_instance){
            auto temp = std::bind(l_func,l_instance,std::placeholders::_1);
            return m_callbacks.emplace(l_name,temp).second; 
        }

        void RemoveCallBack(const std::string& l_name){
            m_callbacks.erase(l_name);
        }
        void HandleEvent(sf::Event& l_event);
        void update();

        sf::Vector2i GetMousePos(sf::RenderWindow* l_wind=nullptr){
            return(l_wind ? sf::Mouse::getPosition(*l_wind) : sf::Mouse::getPosition());
        }
};

EventManager::EventManager(){
    m_hasFocus = true;
    LoadBindings();
}

EventManager::~EventManager(){
    for(auto &itr : m_bindings){
        delete itr.second;
        itr.second = nullptr;
    }
}

bool EventManager::AddBinding(Binding *l_binding){
    if(m_bindings.find(l_binding->m_name)!=m_bindings.end());
        return false;
    return m_bindings.emplace(l_binding->m_name,l_binding).second;
}

bool EventManager::RemoveBinding(std::string l_name){
    auto itr = m_bindings.find(l_name);
    if(itr == m_bindings.end())
        return false;
    delete itr->second;
    m_bindings.erase(itr);
    return true;
}

void EventManager::HandleEvent(sf::Event& l_event){
    for(auto &b_itr : m_bindings){
        Binding* bind = b_itr.second;
        for(auto &e_itr : bind->m_events){
            EventType sfmlEvent = (EventType)l_event.type;
            if(e_itr.first!=sfmlEvent)
                continue;
            if(sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp){
                if(e_itr.second.m_code == l_event.key.code){
                    if(bind->m_details.m_keyCode!=-1){
                        bind->m_details.m_keyCode = e_itr.second.m_code;
                    }
                    ++(bind->c);
                    break;
                }
            }
            else if(sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp){
                if(e_itr.second.m_code == l_event.mouseButton.button){
                    bind->m_details.m_mouse.x = l_event.mouseButton.x;
                    bind->m_details.m_mouse.y = l_event.mouseButton.y;

                    if(bind->m_details.m_keyCode !=-1){
                        bind->m_details.m_keyCode = e_itr.second.m_code;
                    }
                    ++(bind->c);
                    break;
                }
            }else{
                if(sfmlEvent == EventType::MouseWheel){
                    bind->m_details.m_mousewheelDelta = l_event.mouseWheel.delta;

                }else if(sfmlEvent==EventType::WindowResized){
                    bind->m_details.m_size.x = l_event.size.width;
                    bind->m_details.m_size.y = l_event.size.height;
                }else if(sfmlEvent==EventType::TextEntered){
                    bind->m_details.m_textEntered = l_event.text.unicode;
                }
                ++(bind->c);
                
            }
        }
    }
}