#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
const int W = 1600;
const int H = 900;
const int size = 1000;
sf::RenderWindow window(sf::VideoMode(W,H), "Sorting", sf::Style::Default);
void DRAW();
struct array{
    std::vector<int> arr;
    int size;
    std::vector<int> clr;
    bool sorted = false;
    array(int n){
        this->size = n;
        arr.resize(n,0);
        clr.resize(n,0);
        for(int i = 1;i<=n;i++){
            arr[i-1] = i;
        }
    }
    void randomize(){
        srand (time(NULL));
        for (int i = size - 1; i > 0; i--){
            int j = rand() % (i + 1);
            //swap(&arr[i], &arr[j]);
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp; 
        }
        sorted = false;
    }
    void insertion_sort(){
        int i,j,key;
        for(i = 1;i<size;i++){
            key = arr[i];
            j = i-1;
            while(j>=0 && arr[j]>key){
                arr[j+1] = arr[j];
                j--;
            }
            clr[i] = 1;
            clr[j+1] = 1;
            arr[j+1] = key;
            DRAW();
            clr[i] = 0;
            clr[j+1] = 0;
        }
        sorted = true;
        if(sorted){
            for(int i = 0;i<size;i++){
                clr[i] = 2;
                DRAW();
            }
        }
        DRAW();

    }
};
array arr(size);

void DRAW(){
    window.clear();
    for(int i = 0;i<arr.size;i++){
        if(arr.clr[i]==2){
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(i+10,-10),sf::Color::Magenta),
                
            };
            window.draw(line,2,sf::Lines);
        }
        else if(arr.clr[i]==1){
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(i+10,-10),sf::Color::Red),
                sf::Vertex(sf::Vector2f(i+10,-arr.arr[i]-10),sf::Color::Red),
                
            };
            window.draw(line,2,sf::Lines);

        }
        else{
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(i+10,-10),sf::Color::White),
                sf::Vertex(sf::Vector2f(i+10,-arr.arr[i]-10),sf::Color::White),
                
            };
            window.draw(line,2,sf::Lines);
        }
        //line->color = sf::Color::Red;
        
    }
    
    window.display();
}

int main(){
    window.setFramerateLimit(120);
    sf::View view;
    view.setSize(sf::Vector2f(1100.f,1100.f));
    view.setCenter(sf::Vector2f(550,-550));
    window.setView(view);

    arr.randomize();
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        if(!arr.sorted) arr.insertion_sort();
        //DRAW();
        
    }

}