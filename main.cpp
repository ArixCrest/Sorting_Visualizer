#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
const int W = 2400;
const int H = 1800;
const int size = 1000;
sf::RenderWindow window(sf::VideoMode(W,H), "Sorting", sf::Style::Default);
sf::RectangleShape rect_btn(sf::Vector2f(90.f,40.f));
sf::RectangleShape sort_btn(sf::Vector2f(90.f,40.f));
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
            clr[i] = 0;
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
        sorted = true;
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
    void heapify(int root,int n){
        if(root<n){
            int left = root*2+1;
            int right = root*2+2;
            int k;
            if(left<n && right<n){
                if(arr[left]>arr[right]){
                    k = left;
                }else{
                    k = right;
                }

            }
            else if (left<n){
                k = left;
            }else{
                return;
            }
            if(arr[root]<arr[k]){
                int temp = arr[root];
                arr[root] = arr[k];
                arr[k] = temp;
                DRAW();
                heapify(k,n);
            }
        }
    }
    void Heap_sort(){
        for(int i = size/2-1;i>0;i--){
            heapify(i,size);
            DRAW();
        }
        for(int i = size-1;i>0;i--){
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            heapify(0,i);
            DRAW();
        }
    }
    
    void Shell_Sort(){
        //original sequence n/2,n/4 ....
        /*
        for(int dist = size/2; dist >0;dist = dist/2){
            for(int i = dist;i<size;i++){
                int temp = arr[i];
                int j = i;
                while(j>=dist && arr[j-dist]>temp){
                    arr[j] =  arr[j-dist];
                    DRAW();
                    j-=dist;
                }
                arr[j] = temp;
                DRAW();
            }

        }*/
        // using Knuth Increments (3^k-1)/2
        int k = 1;
        while((((k*2+1)*3-1)/2)<size){
            k = ((k*2+1)*3-1)/2;
        }
        for(int dist = k; dist > 0;dist = (((dist*2+1)/3)-1)/2){
            for(int i = dist;i<size;i++){
                int temp = arr[i];
                int j = i;
                while(j>=dist && arr[j-dist]>temp){
                    arr[j] =  arr[j-dist];
                    DRAW();
                    j-=dist;
                }
                arr[j] = temp;
                DRAW();
            }

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
    window.draw(rect_btn);
    window.draw(sort_btn);
    window.display();
}

int main(){
    window.setFramerateLimit(600);
    sf::View view;
    view.setSize(sf::Vector2f(1100.f,1100.f));
    view.setCenter(sf::Vector2f(550,-550));
    window.setView(view);
    arr.randomize();
    rect_btn.setFillColor(sf::Color(255,0,0));
    rect_btn.setPosition(1011.f,-1010.f);
    sort_btn.setFillColor(sf::Color(0,255,0));
    sort_btn.setPosition(1011.f,-960.f);
    while(window.isOpen()){
        sf::Event event;
        window.clear();
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            if(event.type == sf::Event::Resized){
                std::cout<<"New Width:"<<event.size.width<<std::endl;
                std::cout<<"New Height:"<<event.size.height<<std::endl;
            }
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::R){
                    arr.randomize();
                    std::cout<<"Randomizing the array! "<< std::endl;
                }
                if(event.key.code == sf::Keyboard::S){
                    std::cout<<"Sorting the array!"<< std::endl;
                    arr.QuickSort(0,size-1);
                    arr.check();
                }
            }
            if(event.type == sf::Event::MouseButtonPressed){
                auto mousepos = sf::Mouse::getPosition(window);
                //std::cout<<mousepos.x<<" "<<mousepos.y<<std::endl;
                auto mousecoords = window.mapPixelToCoords(mousepos);
                if(rect_btn.getGlobalBounds().contains(mousecoords)){
                    arr.randomize();
                }
                if(sort_btn.getGlobalBounds().contains(mousecoords)){
                    arr.QuickSort(0,size-1);
                    arr.check();
                }
                
            }
        }
        DRAW();
        
    }

}