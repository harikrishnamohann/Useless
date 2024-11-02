// welcome to c programing
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    color,
    quote,
    position,
} identifier_type;

typedef struct hash {
    char* id;
    char* value;
    identifier_type type;
} hash;

typedef struct {
    char* svg_dat;
    hash hash_map;
    size_t length;
} wrapper;

char test_svg[] = "<?xml version=\"1.0\" encoding=\"utf-8\"?><svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 1920 1080\" preserveAspectRatio=\"xMidYMid slice\"><rect x=\"-0.272\" y=\"-1.493\" width=\"1923.244\" height=\"1081.065\" style=\"fill: $sun_color$;\"/><ellipse style=\"fill: rgb(241, 234, 151);\" cx=\"466.112\" cy=\"269.946\" rx=\"174.149\" ry=\"174.149\"/><text style=\"fill: rgb(51, 51, 51); font-family: Arial, sans-serif; font-size: 48px; white-space: pre;\" x=\"833.25\" y=\"507.897\">$greet_day$</text></svg>";
hash test[] = {
  {"sun_color", "rgb(0, 0, 0)", color},
  {"greet_day", "Good night boy", quote},
};

void clear_buffer(char* buffer) {
    for (size_t i = 0; buffer[i] != '\0'; i++) {
        buffer[i] = '\0';
    }
}

wrapper wrapper_init(char svg_dat[], hash mappings) {
    return (wrapper) {
        .svg_dat = strdup(svg_dat),
        .hash_map = mappings,
        .length = strlen(svg_dat),
    };
}

char* replace_identifier(char svg[]) {
    char modified_svg[strlen(svg)];
    char buffer[20];
    int j = 0;
    int k;
    bool is_dollar = false;
    for (int i = 0; svg[i] != '\0'; i++) {
        if (svg[i] != '\\' && svg[i] != '$') {
            modified_svg[j++] = svg[i];
        }
        if (svg[i] == '$') {
            i++;
            clear_buffer(buffer);
            k = 0;
            while (svg[i] != '$') {
                buffer[k++] = svg[i++];
            }
            for (k = 0; k < 2; k++) { // limit of k should be decided.
                if (strcmp(buffer, test[k].id) == 0) {
                    for (int l = 0; l < strlen(test[k].value); l++) {
                        modified_svg[j++] = test[k].value[l];
                    }
                }
            }
        }
    }
    return (char*)strdup(modified_svg);
}

int main() {
    // replace_identifier(test_svg);
    printf("%s\n", replace_identifier(test_svg));
    return 0;
}
