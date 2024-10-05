/*
300171459
Jordan Takefman

Notes for Corector:
I interpreted this question to mean that each child with higher rating needed to have
a total amount of candy greater than it's immmediate neighbours with no regard for
how the child ranked globally.
*/
#include <iostream>
#include <vector>
using namespace std;

class Color{
    public:


        struct Red {
            float r = 0;
        };
        struct Green {
            float g = 0;
        };
        struct Blue {
            float b = 0;
        };

        Red r;
        Green g;
        Blue b;

        Color(Red r_in, Green g_in, Blue b_in) {
            r = r_in;
            g = g_in;
            b = b_in;
        }

        static void blend_color(Color c1, Color c2) {
            float new_r = (c1.r.r + c2.r.r) / 2;
            float new_g = (c1.g.g + c2.g.g) / 2;
            float new_b = (c1.b.b + c2.b.b) / 2;

            cout << "New blended RGB values are: " << new_r << ", " << new_g << ", " << new_b << endl;

        }
    
};

int main() {
    Color::Red r = {255};
    Color::Green g = {66};
    Color::Blue b = {140};

    Color::Red r2 = {75};
    Color::Green g2 = {100};
    Color::Blue b2 = {80};

    Color c1 = Color(r,g,b);
    Color c2 = Color(r2,g2,b2);

    Color::blend_color(c1, c2);
    

}