#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <cmath>
using namespace std;
float gravity = 50;
class Balls
{
    public:
        Balls(int N, float dispersao = 0.5)
        {
            srand(time(0));
            for(int i = 0; i < N; i++)
            {
                int x = rand() % 700;
                int y = rand() % 500;
                int m1 = 55+rand() % 200;
                sf::Vector2f vel(rand() % 100, rand() % 100);
                sf::CircleShape c(10);
                c.setPosition(x,y);
                c.setFillColor(sf::Color(m1,0,0) );
                circle.push_back(c);
                m.push_back(m1);
                velocidade.push_back(vel);
            }
            this->dispersao = dispersao;
        }

        void update(double seconds)
        {
            collision_walls(seconds);
            collision_balls(seconds);
        }
        void draw(sf::RenderWindow& window)
        {
            for(int i = 0; i < (int)circle.size();i++)
                window.draw(circle[i]);
        }
        void collision_walls(double dt)
        {
            for(int i = 0; i < (int)circle.size(); i++)
            {
                sf::Vector2f& vel = velocidade[i];
                sf::Vector2f pos = circle[i].getPosition();
                if( pos.x < 0 ){
                    vel.x *= -1;
                    pos.x = 0;
                } else
                if( pos.x > 780){
                    vel.x *= -1;
                    pos.x = 780;
                }

                if( pos.y < 0) {
                    vel.y *= -1;
                    pos.y = 0;
                } else
                if( pos.y > 580) {
                    vel.y *= -1;
                    pos.y = 580;
                }
                vel.y += gravity*dt;
                pos.x += vel.x*dt;
                pos.y += vel.y*dt;
                circle[i].setPosition(pos);
            }
        }
        void collision_balls(double dt)
        {
            for(int i = 0; i < (int)circle.size(); i++)
            {
                for(int j = i; j < (int) circle.size(); j++)
                {
                    sf::Vector2f pos1 = circle[i].getPosition();
                    sf::Vector2f pos2 = circle[j].getPosition();
                    sf::Vector2f& vel1 = velocidade[i];
                    sf::Vector2f& vel2 = velocidade[j];
                    if( pow(pos1.x-pos2.x,2) + pow(pos1.y-pos2.y,2) <= 400 )
                    {
                        if(dispersao == 0)
                        {
                            float p1x = m[i] * vel1.x;
                            float p1y = m[i] * vel1.y;
                            float p2x = m[j] * vel2.x;
                            float p2y = m[j] * vel2.y;

                            float ptotalX = p1x+p2x;
                            float ptotalY = p1y+p2y;
                            float mtotal = m[i] + m[j];
                            vel1.x = ptotalX/mtotal;
                            vel1.y = ptotalY/mtotal;
                        }else
                        {
                            float vcmx = (m[i]*vel1.x + m[j]*vel2.x) / ( m[i]+m[j] );
                            float vcmy = (m[i]*vel1.y + m[j]*vel2.y) / ( m[i]+m[j] );
                            float vrelx = vel1.x - vel2.x;
                            float vrely = vel1.y - vel2.y;
                            //float vrel_mod = sqrt( projection(verel) );
                            //float aux = vrel_mod * dispercao / (m[i]+m[j]);
                            //float u1_ = m[j]*aux;
                            //float u2_ = m[i]*aux;
                        }

                    }
                    /*

                    vrel = v1 - v2
                    vrel_mod = np.sqrt(np.dot(vrel, vrel) )
                    aux = vrel_mod * self.cor / (m1+m2)
                    u1_ = m2*aux
                    u2_ = m1*aux

                    theta = np.random.uniform(0, 2*np.pi)
                    delta = vrel / vrel_mod
                    delta[:] = [np.cos(theta) * delta[0] + np.sin(theta) * delta[1],
                                -np.sin(theta) * delta[0] + np.cos(theta) * delta[1] ]
                    u1_ = u1_*delta
                    u2_ = -u2_*delta
                    self.vel[i] = vrel + u1_
                    self.vel[j] = vrel + u2_
                    */
                }
            }
        }

    vector<sf::CircleShape> circle;
    vector<sf::Vector2f> velocidade;
    vector<int> m;
    float dispersao;
};

int main(int argc, char* args[]){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hello", sf::Style::Close);
    window.setFramerateLimit(60);

    Balls balls(100);
    sf::Clock tempoDecorrido;
    sf::CircleShape circle(10);
    circle.setPosition(50,50);
    circle.setOutlineColor(sf::Color::Red);
    while(window.isOpen())
    {
        window.clear(sf::Color(255,255,255));
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        float dt = tempoDecorrido.getElapsedTime().asSeconds();
        tempoDecorrido.restart();

        balls.update(dt);

        balls.draw(window);

        window.display();

    };
    return 0;
}
