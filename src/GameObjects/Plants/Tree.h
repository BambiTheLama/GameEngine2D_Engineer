#pragma once
#include "Plant.h"

class Tree :
    public Plant, public Collider
{
    int age = 0;
    int maxAge = 0;
    int timer = 60;
    Tree(Tree& tree);
public:
    Tree(Rectangle pos,std::string name);

    ~Tree();

    void start();

    void incrementAge();

    void update();

    void draw();

    virtual Tree* clone() { return new Tree(*this); }

    bool isColliding() { return true; }
};

