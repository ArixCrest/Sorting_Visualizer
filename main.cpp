#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
const int W = 2400;
const int H = 1800;
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
    //Checking the array
    void check(){
        for(int x = 0;x<=size-1;x++){
            if(arr[x]<=arr[x+1]){
                clr[x] = 2;
                if(x==size-2) arr[x+1] = 2;
            }
            DRAW();
        }
    }
    //BUBBLE SORT
    void BUBBLE_SORT(){
        for(int i = size-1;i>0;i--){
            for(int j = 0;j<i;j++){
                if(arr[j]>arr[j+1]){
                    int temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                    DRAW();
                }
            }
        }
    }

    //INSERTIONSORT
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
    }
    //MERGESORT
    void merge(int left,int mid,int right){
        int temp[right-left+1];
        int i = left;
        int j = mid+1;
        int k = 0;
        while(i<=mid && j<=right){
            if(arr[i]>=arr[j]){
                temp[k] = arr[j];
                j++;
                k++;
            }else{
                temp[k] = arr[i];
                i++;
                k++;
            }
        }
        while(i<=mid){
            temp[k] = arr[i];
            i++;
            k++;
        }
        while(j<=right){
            temp[k] = arr[j];
            j++;
            k++;
        }
        for(int x = left;x<=right;x++){
            arr[x] = temp[x-left];
            DRAW();
        }
        DRAW();
        
    }
    void Merge_Sort(int l,int r){
        if(l<r){
            int mid = (l+r)/2;
            Merge_Sort(l,mid);
            Merge_Sort(mid+1,r);
            merge(l,mid,r);
        }
    }
    //QUICKSORT
    int Partition_qs(int l,int h){
        int i = l-1;
        int temp;
        for(int j = l; j<=h-1;j++){
            if(arr[j]<arr[h]){
                i++;
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                DRAW();
            }
        }
        temp = arr[i+1];
        arr[i+1] = arr[h];
        arr[h] = temp;
        DRAW();
        return i+1;
    }
    void QuickSort(int l, int h){
        if(l<h){
            int par = Partition_qs(l,h);
            QuickSort(l,par-1);
            QuickSort(par+1,h);
        }
    }

};
array arr(size);

void DRAW(){
    window.clear();
    for(int i = 0;i<arr.size;i++){
        if(arr.clr[i]==2){
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(i+10,-10),sf::Color::Magenta),
                sf::Vertex(sf::Vector2f(i+10,-arr.arr[i]-10),sf::Color::Red),
                
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
    window.setFramerateLimit(240);
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
        if(!arr.sorted) arr.Merge_Sort(0,size-1);
        //DRAW();
        arr.check();
        
    }

}