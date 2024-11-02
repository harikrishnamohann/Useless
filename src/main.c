// welcome to c programing
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct id_value {
    char* id;
    char* value;
} id_value;

id_value test[] = {
  {"sun_color", "rgb(0, 0, 0)"},
  {"greeting", "Good night boy"},
};

int main() {
    char *test_svg = "<?xml version=\"1.0\" encoding=\"utf-8\"?><svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 1920 1080\" preserveAspectRatio=\"xMidYMid slice\"><rect x=\"-0.272\" y=\"-1.493\" width=\"1923.244\" height=\"1081.065\" style=\"fill: $sun_color$;\"/><ellipse style=\"fill: rgb(241, 234, 151);\" cx=\"466.112\" cy=\"269.946\" rx=\"174.149\" ry=\"174.149\"/><text style=\"fill: rgb(51, 51, 51); font-family: Arial, sans-serif; font-size: 48px; white-space: pre;\" x=\"833.25\" y=\"507.897\">$greeting$</text></svg>";
    return 0;
}
